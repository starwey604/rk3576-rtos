/**
  * Copyright (c) 2024 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cec.c
  * @version V0.1
  * @brief   cec driver
  *
  * Change Logs:
  * Date           Author          Notes
  * 2024-08-21     Algea Cao   first implementation
  *
  ******************************************************************************
  */

#include <rtdevice.h>
#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_CEC

#include "hal_base.h"
#include "drv_cec.h"

#define DBG_TAG "cec"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define CEC_LOG_D LOG_D
#define CEC_LOG_I LOG_I
#define CEC_LOG_E LOG_E

#define POLLING_RETRY_TIMES 2
#define EDID_BLOCK_LEN 128
#define CEC_PHYS_ADDR_INVALID 0xffff

#define CEC_EVENT_HPD           (0x01UL << 0)
#define CEC_EVENT_MSG_RECEIVE   (0x01UL << 1)

/* cec device */
struct rt_cec
{
    struct rt_device dev;
    struct CEC_MSG cec_msg;
    uint16_t phy_addr;
    uint8_t la;
    bool standby;

    uint8_t *raw_edid;

    /* irq handler */
    rt_isr_handler_t irq_handler;
    struct rt_work hpd_work;
    struct rt_work cec_irq_work;
    struct rt_workqueue *isr_workqueue;

    struct rt_completion done;
    struct rt_event *event;
    struct rt_i2c_client *i2c_client;

    struct clk_gate *clk_cec_ctrl_en;
    struct clk_gate *pclk_cec_ctrl_en;

    /* HAL */
    struct CEC_REG *hw_base;
};

struct rt_cec *g_cec;

static rt_err_t rt_cec_ddc_read(struct rt_i2c_client *i2c_client,
                                uint8_t reg, uint8_t *buf, uint8_t len)
{
    struct rt_i2c_msg msgs[2];
    rt_err_t ret = RT_EOK;

    msgs[0].addr = i2c_client->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = &reg;
    msgs[0].len = sizeof(reg);

    msgs[1].addr = i2c_client->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = (void *)buf;
    msgs[1].len = len;

    ret = rt_i2c_transfer(i2c_client->bus, msgs, 2);
    if (ret != 2)
    {
        CEC_LOG_E("ERR: %s: failed: (%d)\n", __func__, ret);
        return ret;
    }

    return RT_EOK;
}

static rt_err_t rt_cec_get_edid(struct rt_cec *cec)
{
    uint8_t ext_block_num;
    rt_err_t ret = RT_EOK;

    cec->raw_edid = rt_calloc(1, EDID_BLOCK_LEN);

    if (!cec->raw_edid)
    {
        CEC_LOG_E("alloc raw edid failed\n");
        return -RT_ENOMEM;
    }

    ret = rt_cec_ddc_read(cec->i2c_client, 0x00, cec->raw_edid, EDID_BLOCK_LEN);
    if (ret != RT_EOK)
    {
        CEC_LOG_E("read edid failed\n");
        return ret;
    }

    ext_block_num = cec->raw_edid[126];
    if (ext_block_num)
        cec->raw_edid = rt_realloc(cec->raw_edid, (ext_block_num + 1) * EDID_BLOCK_LEN);

    if (cec->raw_edid == RT_NULL)
    {
        CEC_LOG_E("realloc raw edid failed\n");
        return -RT_ENOMEM;
    }

    ret = rt_cec_ddc_read(cec->i2c_client, 0x80, &cec->raw_edid[128], EDID_BLOCK_LEN);
    if (ret != RT_EOK)
    {
        CEC_LOG_D("read ext edid failed\n");
        return ret;
    }

    return ret;
}

static uint32_t rt_cec_get_edid_spa_location(uint8_t *edid)
{
    uint32_t blocks;
    uint32_t block;
    uint8_t d;

    /*
     * If there are fewer extension blocks than the size, then update
     * 'blocks'. It is allowed to have more extension blocks than the size,
     * since some hardware can only read e.g. 256 bytes of the EDID, even
     * though more blocks are present. The first CEA-861 extension block
     * should normally be in block 1 anyway.
     */
    blocks = edid[0x7e] + 1;

    for (block = 1; block < blocks; block++)
    {
        uint32_t offset = block * 128;

        /* Skip any non-CEA-861 extension blocks */
        if (edid[offset] != 0x02 || edid[offset + 1] != 0x03)
            continue;

        /* search Vendor Specific Data Block (tag 3) */
        d = edid[offset + 2] & 0x7f;
        /* Check if there are Data Blocks */
        if (d <= 4)
            continue;
        if (d > 4)
        {
            uint32_t i = offset + 4;
            uint32_t end = offset + d;

            /* Note: 'end' is always < 'size' */
            do
            {
                uint8_t tag = edid[i] >> 5;
                uint8_t len = edid[i] & 0x1f;

                if (tag == 3 && len >= 5 && i + len <= end &&
                        edid[i + 1] == 0x03 &&
                        edid[i + 2] == 0x0c &&
                        edid[i + 3] == 0x00)
                    return i + 4;

                i += len + 1;
            }
            while (i < end);
        }
    }

    return 0;
}

static uint16_t rt_cec_get_edid_phys_addr(uint8_t *edid, uint32_t *offset)
{
    uint32_t loc = rt_cec_get_edid_spa_location(edid);

    if (offset)
        *offset = loc;

    if (loc == 0)
        return CEC_PHYS_ADDR_INVALID;

    return (edid[loc] << 8) | edid[loc + 1];
}

static rt_err_t rt_cec_transmit(struct rt_cec *cec, struct CEC_MSG *cec_msg)
{
    int timeout = 0;

    HAL_CEC_SendMsg(cec->hw_base, cec_msg);

    timeout = rt_completion_wait(&cec->done, rt_tick_from_millisecond(RT_TICK_PER_SECOND));
    if (timeout)
    {
        CEC_LOG_E("cec transmit timed out\n");
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static void rt_cec_irq_handler(int irq, void *args)
{
    struct rt_cec *cec = g_cec;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_CEC_IrqHandler(cec->hw_base, &cec->cec_msg);

    if (cec->cec_msg.tx_status)
        rt_completion_done(&cec->done);

    /* leave interrupt */
    rt_interrupt_leave();

    if (cec->cec_msg.rx_status)
    {
        CEC_LOG_D("%s rt_event_send CEC_EVENT_MSG_RECEIVE\n", __func__);
        rt_event_send(cec->event, CEC_EVENT_MSG_RECEIVE);
    }
}

static void rt_cec_wake_irq_handler(int irq, void *args)
{
    struct rt_cec *cec = g_cec;

    /* enter interrupt */
    rt_interrupt_enter();
    cec->standby = false;
    HAL_CEC_Wake(cec->hw_base);

    if (cec->cec_msg.tx_status)
        rt_completion_done(&cec->done);

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief  Call by rt_cec_hpd_irq_callback to read edid.
 * @param  work: work point.
 * @param  work_data: work info.
 */
static void rt_cec_hpd_work(struct rt_work *work, void *work_data)
{
    struct rt_cec *cec = (struct rt_cec *)work_data;

    if (rt_pin_read(CEC_HPD_IRQ_PIN) == PIN_HIGH)
    {
        rt_cec_get_edid(cec);
        cec->phy_addr = rt_cec_get_edid_phys_addr(cec->raw_edid, NULL);
        CEC_LOG_I("%s phy_addr:0x%x\n", __func__, cec->phy_addr);
    }
    else
    {
        cec->phy_addr = CEC_PHYS_ADDR_INVALID;
    }

    rt_event_send(cec->event, CEC_EVENT_HPD);
}

static void rt_cec_hpd_irq_callback(void *args)
{
    struct rt_cec *cec = g_cec;

    rt_work_init(&cec->hpd_work, rt_cec_hpd_work, (void *)cec);

    if (rt_workqueue_dowork(cec->isr_workqueue, &cec->hpd_work) == -RT_EBUSY)
        CEC_LOG_E("hpd work is busy\n");
}

/**
 * @brief  Init cec device.
 * @param  dev: rt_device_t for cec.
 * return rt_err_t.
 */
static rt_err_t rt_cec_init(rt_device_t dev)
{
    return RT_EOK;
}

/**
 * @brief  Open cec device.
 * @param  dev: rt_device_t for cec.
 * @oflag  oflag: open flag.
 * return rt_err_t.
 */
static rt_err_t rt_cec_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

/**
 * @brief  Close cec device.
 * @param  dev: rt_device_t for cec.
 * return rt_err_t.
 */
static rt_err_t rt_cec_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_cec_poll_logical_addr(struct rt_cec *cec, uint8_t prefer_la)
{
    uint8_t i;
    rt_err_t ret = RT_EOK;

    cec->cec_msg.signal_free_time = CEC_SIGNAL_FREE_TIME_RETRY;
    cec->cec_msg.msg[0] = (prefer_la & 0xf) | ((prefer_la & 0xf) << 4);
    cec->cec_msg.len = 1;

    for (i = 0; i <= POLLING_RETRY_TIMES; i++)
    {
        ret = rt_cec_transmit(cec, &cec->cec_msg);
        if (ret != RT_EOK)
        {
            CEC_LOG_E("%s: send cec msg:0x%02x 0x%02x failed ret:%d\n",
                      __func__, cec->cec_msg.msg[0], cec->cec_msg.msg[1], ret);
            break;
        }
        CEC_LOG_D("%s tx_status:%d\n", __func__, cec->cec_msg.tx_status);
        /* this logical addr is occupied, poll next one */
        if (cec->cec_msg.tx_status == CEC_TRANS_STATUS_DONE)
        {
            ret = -RT_EBUSY;
            break;
            /* cec transmit error */
        }
        else if (cec->cec_msg.tx_status != CEC_TRANS_STATUS_NACK)
        {
            ret = RT_ERROR;
            break;
        }

        cec->cec_msg.tx_status = 0;
    }

    /* polling success, use this logic addr */
    if (i > POLLING_RETRY_TIMES)
    {
        HAL_CEC_SetLoigcAddr(cec->hw_base, prefer_la);
        cec->la = prefer_la;
    }

    return ret;
}

/**
 * @brief  Control cec device.
 * @param  dev: rt_device_t for cec.
 * @param  cmd: control command.
 * @param  args: args between driver and userspace.
 * return rt_err_t.
 */
static rt_err_t rt_cec_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_cec *cec = (struct rt_cec *)dev->user_data;
    rt_err_t ret = RT_EOK;

    CEC_LOG_D("%s cmd:%d\n", __func__, cmd);
    switch (cmd)
    {
    case RK_CEC_CTRL_SEND_MSG:
        memcpy(&cec->cec_msg, args, sizeof(cec->cec_msg));
        ret = rt_cec_transmit(cec, &cec->cec_msg);
        if (ret != RT_EOK)
            CEC_LOG_E("%s: send cec msg:0x%02x 0x%02x failed ret:%d\n",
                      __func__, cec->cec_msg.msg[0], cec->cec_msg.msg[1], ret);
        break;
    case RK_CEC_CTRL_READ_MSG:
        memcpy(args, &cec->cec_msg, sizeof(cec->cec_msg));
        break;
    case RK_CEC_CTRL_SET_LOGIC_ADDR:
        if (cec->standby)
            break;
        ret = rt_cec_poll_logical_addr(cec, *(uint8_t *)args);
        break;
    case RK_CEC_CTRL_GET_PHY_ADDR:
        memcpy(args, &cec->phy_addr, sizeof(cec->phy_addr));
        break;
    case RK_CEC_CTRL_STANDBY:
        cec->standby = true;
        HAL_CEC_Standy(cec->hw_base);
        break;
    case RK_CEC_CTRL_SET_EVENT:
        cec->event = (struct rt_event *)args;
        break;
    default:
        break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rt_cec_ops =
{
    rt_cec_init,
    rt_cec_open,
    rt_cec_close,
    NULL,
    NULL,
    rt_cec_control,
};
#endif

int rt_hw_cec_init(void)
{
    struct rt_cec *cec;

    RT_ASSERT(CEC_HPD_IRQ_PIN != 0);
    RT_ASSERT(CEC_I2C_DEV != 0);

    cec = rt_calloc(1, sizeof(struct rt_cec));
    RT_ASSERT(cec);

    g_cec = cec;
    cec->hw_base = CEC;
#ifdef RT_USING_DEVICE_OPS
    cec->dev.ops = &rt_cec_ops;
#else
    cec->dev.init = rt_cec_init;
    cec->dev.open = rt_cec_open;
    cec->dev.close = rt_cec_close;
    cec->dev.read = NULL;
    cec->dev.write = NULL;
    cec->dev.control = rt_cec_control;
#endif
    cec->standby = false;
    cec->dev.user_data = (void *)cec;

    cec->i2c_client = rt_calloc(1, sizeof(struct rt_i2c_client));
    RT_ASSERT(cec->i2c_client);
    cec->i2c_client->bus = rt_i2c_bus_device_find(CEC_I2C_DEV);
    RT_ASSERT(cec->i2c_client->bus);
    cec->i2c_client->client_addr = 0x50;

    cec->isr_workqueue = rt_workqueue_create("cecWQ", 1024, 5);
    RT_ASSERT(cec->isr_workqueue != NULL);
    rt_completion_init(&cec->done);

    /* register lcd device to RT-Thread */
    rt_device_register(&cec->dev, "cec", RT_DEVICE_FLAG_RDWR);

    cec->clk_cec_ctrl_en = get_clk_gate_from_id(CLK_CEC_CTRL_GATE);
    cec->pclk_cec_ctrl_en = get_clk_gate_from_id(PCLK_CEC_CTRL_GATE);

    RT_ASSERT(cec->clk_cec_ctrl_en != RT_NULL);
    RT_ASSERT(cec->pclk_cec_ctrl_en != RT_NULL);

    clk_enable(cec->clk_cec_ctrl_en);
    clk_enable(cec->pclk_cec_ctrl_en);

    HAL_CEC_Init(cec->hw_base);

    /* register cec irq */
    rt_hw_interrupt_install(CEC_INT_IRQn, rt_cec_irq_handler, (void *)cec, "cec_irq");
    rt_hw_interrupt_umask(CEC_INT_IRQn);

    /* register cec wake irq */
    rt_hw_interrupt_install(CEC_WAKE_IRQn, rt_cec_wake_irq_handler, (void *)cec, "cec_wake_irq");
    rt_hw_interrupt_umask(CEC_WAKE_IRQn);

    /* register hpd irq */
    rt_pin_mode(CEC_HPD_IRQ_PIN, PIN_MODE_INPUT);
    rt_pin_attach_irq(CEC_HPD_IRQ_PIN, PIN_IRQ_MODE_RISING_FALLING, rt_cec_hpd_irq_callback, (void *)cec);
    rt_pin_irq_enable(CEC_HPD_IRQ_PIN, PIN_IRQ_ENABLE);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_cec_init);

#endif
