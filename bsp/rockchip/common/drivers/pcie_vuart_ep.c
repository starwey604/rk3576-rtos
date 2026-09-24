/*
 * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-07     Cliff Chen   first implementation
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#ifdef RT_USING_PCIE_VUART_EP

#define DBG_TAG    "VUART"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* Driver version info */
#define PCIE_VUART_MAJIC_NUMBER          0x524B5655
#define PCIE_VUART_DRV_VERSION           0x10000000

/* Small buffer size for simplified design */
#define VUART_BUFFER_SIZE                256                               /* in bytes, align with word */

/* Shared memory structure definition - simplified design */
struct pcie_vuart_shm
{
    volatile uint32_t  magic;                                              /* Magic number for validation */
    volatile uint32_t  version;                                            /* Version number */
    volatile uint32_t  rc_to_ep_flag;                                      /* RC to EP ready flag */
    volatile uint32_t  ep_to_rc_flag;                                      /* EP to RC ready flag */
    volatile uint32_t  rc_to_ep_len;                                       /* RC to EP data length */
    volatile uint32_t  ep_to_rc_len;                                       /* EP to RC data length */
    volatile uint32_t  rc_to_ep_buf[VUART_BUFFER_SIZE / sizeof(uint32_t)]; /* RC to EP data buffer */
    volatile uint32_t  ep_to_rc_buf[VUART_BUFFER_SIZE / sizeof(uint32_t)]; /* EP to RC data buffer */;
};

/* Local buffer */
struct local_buffer
{
    uint8_t rx_buf[VUART_BUFFER_SIZE];
    uint8_t tx_buf[VUART_BUFFER_SIZE];
    uint32_t rx_index;
    uint32_t rx_len;
    uint32_t tx_len;
    struct rt_mutex mutex; /* Mutex for buffer access */
};

/* Device structure definition */
struct pcie_vuart_device
{
    struct rt_serial_device serial;      /* RT-Thread serial device */
    struct pcie_vuart_shm *shm;          /* Shared memory pointer */
    void *pcie_bar_addr;                 /* PCIE BAR base address */
    size_t pcie_bar_size;                /* PCIE BAR size */
    char *device_name;                   /* Device name */
    struct local_buffer loc_buf;         /* Local buffer */
    rt_thread_t thread;                  /* Thread for polling */
};

/* Global device instance */
static struct pcie_vuart_device g_vuart_dev;

/* Configure serial parameters */
static rt_err_t pcie_vuart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /* No configuration needed for virtual UART */
    return RT_EOK;
}

/* Device control interface */
static rt_err_t pcie_vuart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    /* Most control commands can be ignored in polling mode */
    return RT_EOK;
}

/* flush local buffer to PCIE RC */
static int pcie_vuart_flush(struct pcie_vuart_device *dev)
{
    uint32_t *src, *dst;
    int size;

    rt_mutex_take(&dev->loc_buf.mutex, RT_WAITING_FOREVER);

    /* Wait until remote side is ready to receive (ep_to_rc_flag is 0 && ep_to_rc_len is 0) */
    while (dev->shm->ep_to_rc_flag || dev->shm->ep_to_rc_len)
    {
        /* Short delay */
        rt_thread_mdelay(1);
    }

    /* padding zero */
    size = dev->loc_buf.tx_len;
    if (dev->loc_buf.tx_len % sizeof(uint32_t) != 0)
    {
        uint32_t padding_len = sizeof(uint32_t) - (dev->loc_buf.tx_len % sizeof(uint32_t));
        memset(dev->loc_buf.tx_buf + dev->loc_buf.tx_len, 0, padding_len);
        size = dev->loc_buf.tx_len + padding_len;
    }

    /* Copy data to ep_to_rc_buf */
    src = (uint32_t *)dev->loc_buf.tx_buf;
    dst = (uint32_t *)dev->shm->ep_to_rc_buf;
    for (int i = 0; i < size / sizeof(uint32_t); i++)
        dst[i] = src[i];

    /* clear tx_len for local buffer */
    size = dev->loc_buf.tx_len;
    dev->loc_buf.tx_len = 0;

    /* Set transmission flag to notify remote */
    dev->shm->ep_to_rc_len = size;
    dev->shm->ep_to_rc_flag = 1;

    rt_mutex_release(&dev->loc_buf.mutex);
    return size;
}

/* Send a single character */
static int pcie_vuart_putc(struct rt_serial_device *serial, char c)
{
    struct pcie_vuart_device *dev = rt_container_of(serial, struct pcie_vuart_device, serial);

    if (dev->loc_buf.tx_len && dev->loc_buf.tx_len >= sizeof(dev->loc_buf.tx_buf))
    {
        /* Local buffer is full, flush it to remote */
        pcie_vuart_flush(dev);
    }

    /* Copy character to local buffer */
    dev->loc_buf.tx_buf[dev->loc_buf.tx_len++] = c;

    return 1;
}

/* Receive a single character */
static int pcie_vuart_getc(struct rt_serial_device *serial)
{
    struct pcie_vuart_device *dev = rt_container_of(serial, struct pcie_vuart_device, serial);
    int ch = -1;

    /* There is no data in local buffer, recv data from PCIE RC */
    if (dev->loc_buf.rx_len == 0 || dev->loc_buf.rx_index >= dev->loc_buf.rx_len)
    {
        uint32_t *src, *dst;
        uint32_t size;

        /* Return -1 if no data ready */
        if (!dev->shm->rc_to_ep_flag || !dev->shm->rc_to_ep_len)
        {
            return ch;
        }

        /* Round up to 4 bytes */
        size = dev->shm->rc_to_ep_len;
        if (size % sizeof(uint32_t) != 0)
            size = size + sizeof(uint32_t) - (size % sizeof(uint32_t));

        /* Copy data from remote buffer */
        src = (uint32_t *)dev->shm->rc_to_ep_buf;
        dst = (uint32_t *)dev->loc_buf.rx_buf;
        for (int i = 0; i < size / sizeof(uint32_t); i++)
            dst[i] = src[i];

        /* update rx_len for local buffer */
        dev->loc_buf.rx_len = dev->shm->rc_to_ep_len;
        dev->loc_buf.rx_index = 0;

        /* Clear remote side flag */
        dev->shm->rc_to_ep_len = 0;
        dev->shm->rc_to_ep_flag = 0;
    }

    /* Copy data form local buffer if avaiable */
    if (dev->loc_buf.rx_len > 0)
        ch = dev->loc_buf.rx_buf[dev->loc_buf.rx_index++];

    return ch;
}

/* poll thread for flush local buffer to PCIE RC */
void poll_entry(void *parameter)
{
    struct pcie_vuart_device *dev = (struct pcie_vuart_device *)parameter;

    while (1)
    {
        /* Check rx ready in share memory */
        if (dev->shm->rc_to_ep_flag && dev->shm->rc_to_ep_len > 0)
        {
            rt_hw_serial_isr(&dev->serial, RT_SERIAL_EVENT_RX_IND);
        }

        /* Check tx data in local buffer */
        if (dev->loc_buf.tx_len > 0)
        {
            /* flush local buffer to PCIE RC */
            pcie_vuart_flush(dev);
        }

        /* Short delay */
        rt_thread_mdelay(10);
    }
}

/* Serial operation interface structure */
static const struct rt_uart_ops pcie_vuart_ops =
{
    .configure = pcie_vuart_configure,
    .control = pcie_vuart_control,
    .putc = pcie_vuart_putc,
    .getc = pcie_vuart_getc,
};

/* Driver initialization function */
int rt_hw_pcie_vuart_init(void *pcie_bar_addr, size_t bar_size)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result;

    /* Parameter check */
    if (pcie_bar_addr == RT_NULL || bar_size < sizeof(struct pcie_vuart_shm))
    {
        rt_kprintf("PCIE VUART: Invalid BAR memory configuration\n");
        return -RT_ERROR;
    }

    /* Initialize device structure */
    g_vuart_dev.pcie_bar_addr = pcie_bar_addr;
    g_vuart_dev.pcie_bar_size = bar_size;
    g_vuart_dev.shm = (struct pcie_vuart_shm *)pcie_bar_addr;
    g_vuart_dev.device_name = "vuart";

    /* Initialize shared memory */
    rt_memset(g_vuart_dev.shm, 0, sizeof(struct pcie_vuart_shm));
    g_vuart_dev.shm->magic = PCIE_VUART_MAJIC_NUMBER;
    g_vuart_dev.shm->version = PCIE_VUART_DRV_VERSION;

    rt_mutex_init(&g_vuart_dev.loc_buf.mutex, "vuart_lock", RT_IPC_FLAG_PRIO);

    /* Create polling thread */
    g_vuart_dev.thread = rt_thread_create("vuart_poll",
                                          poll_entry,
                                          &g_vuart_dev,
                                          2048,
                                          RT_THREAD_PRIORITY_MAX - 2,
                                          10);
    RT_ASSERT(g_vuart_dev.thread != RT_NULL);
    rt_thread_startup(g_vuart_dev.thread);

    /* Register serial device */
    g_vuart_dev.serial.ops = &pcie_vuart_ops;
    g_vuart_dev.serial.config = config;

    result = rt_hw_serial_register(&g_vuart_dev.serial,
                                   g_vuart_dev.device_name,
                                   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,  /* Polling mode, rx interrupts */
                                   &g_vuart_dev);
    if (result != RT_EOK)
    {
        rt_kprintf("PCIE VUART: Failed to register serial device\n");
        return result;
    }

    rt_kprintf("PCIE VUART: Initialized (Poll Mode, Version 0x%x)\n", PCIE_VUART_DRV_VERSION);
    return RT_EOK;
}

/* Set as console device */
void rt_hw_pcie_vuart_set_console(void)
{
    rt_console_set_device(g_vuart_dev.device_name);
    finsh_set_device(g_vuart_dev.device_name);
    rt_kprintf("PCIE VUART: Set as console device\n");
}

/* Initialize PCIE VUART device */
int pcie_vuart_init(void *bar_addr, size_t bar_size)
{
    int ret = rt_hw_pcie_vuart_init(bar_addr, bar_size);
    if (ret == RT_EOK)
    {
        /* Set virtual UART as console */
        rt_hw_pcie_vuart_set_console();
    }

    return ret;
}

/* De-initialization function */
int pcie_vuart_deinit(void)
{
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_kprintf("PCIE VUART: Deinitialized\n");
    return RT_EOK;
}
MSH_CMD_EXPORT(pcie_vuart_deinit, "pcie_vuart_deinit");

/* Auto-initialization function */
int pcie_vuart_auto_init(void)
{
    return pcie_vuart_init((void *)0x3c400000, 768);
}
MSH_CMD_EXPORT(pcie_vuart_auto_init, "pcie_vuart_auto_init");

#ifdef RT_USING_PCIE_VUART_TEST
void test_vuart_write(void)
{
    /* Note: In real applications, get BAR address from PCIE configuration */
    void *bar_addr = (void *)0x3c400000;                           /* Replace with actual BAR address */
    size_t bar_size = sizeof(struct pcie_vuart_shm);               /* Replace with actual BAR size */

    int ret = rt_hw_pcie_vuart_init(bar_addr, bar_size);
    if (ret == RT_EOK)
    {
        rt_device_t new_device;

        new_device = rt_device_find(g_vuart_dev.device_name);
        if (new_device == RT_NULL)
        {
            rt_kprintf("PCIE VUART: Failed to find device\n");
            return;
        }

        rt_device_open(new_device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM);
        while (1)
        {
            rt_device_write(new_device, 0, "Hello World!\n", 13);
            rt_thread_mdelay(100);
        }
    }
}
MSH_CMD_EXPORT(test_vuart_write, "test_vuart_write");
#endif

#endif /* RT_USING_PCIE_VUART */