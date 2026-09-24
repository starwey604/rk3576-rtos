/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    serdes_core.c
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#include "core.h"

RT_WEAK const struct serdes_desc rk_board_display_serdes[] = {0};

static struct serdes_id_data serdes_id_data[] =
{
#ifdef RT_USING_SERDES_CHIP_MAXIM_MAX96789
    {.name = "max96789", .data = &serdes_max96789_data},
#endif
#ifdef RT_USING_SERDES_CHIP_MAXIM_MAX96752
    {.name = "max96752", .data = &serdes_max96752_data},
#endif
    { /* sentinel */ }
};

rt_serdes_t rt_serdes_match(const struct serdes_desc *serdes_desc)
{
    rt_uint8_t i;
    rt_serdes_t serdes;
    struct serdes_id_data *serdes_dev;

    serdes = (rt_serdes_t)rt_calloc(1, sizeof(struct rt_serdes));
    if (!serdes)
    {
        rt_kprintf("%s: serdes failed to apply for memory\n", __func__);
        return RT_NULL;
    }

    for (serdes_dev = serdes_id_data; serdes_dev->name != RT_NULL; serdes_dev++)
    {
        if (strcmp(serdes_dev->name, serdes_desc->name) == 0)
        {
            rt_memcpy(&serdes->chip_data,
                      serdes_dev->data, sizeof(struct serdes_chip_data));
            rt_memcpy(&serdes->serdes_desc, serdes_desc, sizeof(struct serdes_desc));

            rt_snprintf(serdes->dev_name, sizeof(serdes->dev_name),
                        "%s-00%02x-%s", serdes_desc->i2c_bus,
                        serdes_desc->i2c_addr, serdes_desc->name);

            return serdes;
        }
    }

    rt_free(serdes);
    serdes = RT_NULL;

    SERDES_DBG_MFD("serdes %s match fail\n", serdes_desc->name);

    return RT_NULL;
}

rt_err_t serdes_reg_read(struct rt_i2c_client *serdes_client, rt_uint16_t reg, rt_uint8_t *val)
{
    rt_int8_t ret;
    rt_uint8_t i2c_reg[2] = {0, 0};
    struct rt_i2c_msg msgs[2] = {0, 0};

    i2c_reg[0] = ((uint16_t)(reg >> 8) & 0xFF);
    i2c_reg[1] = ((uint16_t)(reg) & 0xFF);

    msgs[0].addr = serdes_client->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = i2c_reg;
    msgs[0].len = 2;

    msgs[1].addr = serdes_client->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = val;
    msgs[1].len = 1;

    ret = rt_i2c_transfer(serdes_client->bus, msgs, 2);

    if (ret == 2)
    {
        SERDES_DBG_I2C("%s Read Reg%04x %04x\n", __func__, reg, *val);
        return RT_EOK;
    }

    return ret;
}

rt_err_t serdes_reg_write(struct rt_i2c_client *serdes_client, rt_uint16_t reg, rt_uint8_t val)
{
    rt_int8_t ret;
    rt_uint8_t buf[4];
    struct rt_i2c_msg msgs;

    buf[0] = ((uint16_t)(reg >> 8) & 0xFF);
    buf[1] = ((uint16_t)(reg) & 0xFF);
    buf[2] = val;

    msgs.addr = serdes_client->client_addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 3;

    ret = rt_i2c_transfer(serdes_client->bus, &msgs, 1);

    if (ret == 1)
    {
        SERDES_DBG_I2C("%s Write Reg%04x %04x\n", __func__, reg, val);
        return RT_EOK;
    }

    return ret;
}

rt_err_t serdes_set_bits(struct rt_i2c_client *serdes_client,
                         rt_uint16_t reg, rt_uint8_t mask, rt_uint8_t val)
{
    rt_uint8_t value;
    rt_err_t ret = RT_EOK;

    ret = serdes_reg_read(serdes_client, reg, &value);
    if (ret != RT_EOK)
    {
        SERDES_DBG_I2C("%s read Reg%04x fali, ret=%d\n", __func__, reg, ret);
        return ret;
    }

    value &= ~mask;
    value |= val;
    ret = serdes_reg_write(serdes_client, reg, value);
    if (ret != RT_EOK)
    {
        SERDES_DBG_I2C("%s write Reg%04x %04x fali, ret=%d\n", __func__, reg, value, ret);
        return ret;
    }

    SERDES_DBG_I2C("%s Reg%04x %04x mask=%04x value=%04x\n", __func__, reg, val, mask, value);
    return RT_EOK;
}

rt_err_t serdes_i2c_set_sequence(rt_serdes_t serdes)
{
    rt_int8_t ret;
    rt_uint8_t i, def, num = 0;

    struct rt_serdes_config *serdes_init_seq;
    struct rt_i2c_client *serdes_client = serdes->serdes_client;

    if (!serdes_client)
        return -RT_ERROR;

    serdes_init_seq = &serdes->serdes_desc.serdes_init_seq;
    if (!serdes_init_seq || !serdes_init_seq->reg_config)
        return -RT_ERROR;

    for (i = 0; i < serdes_init_seq->reg_config_cnt; i++)
    {
        if (num >= RT_I2C_ERROR_TIMES)
            return -RT_ERROR;

        if (serdes_init_seq->reg_config[i].reg == 0xffff)
        {
            SERDES_DBG_MFD("serdes %s delay %d ms\n", serdes->dev_name,
                           serdes_init_seq->reg_config[i].def);

            rt_thread_mdelay(serdes_init_seq->reg_config[i].def);
            continue;
        }

        ret = serdes_reg_write(serdes_client,
                               serdes_init_seq->reg_config[i].reg,
                               serdes_init_seq->reg_config[i].def);

        if (ret != RT_EOK)
        {
            rt_kprintf("%s write reg %04x fali, ret=%d, again now\n", serdes->dev_name,
                       serdes_init_seq->reg_config[i].reg, ret);
            ret = serdes_reg_write(serdes_client,
                                   serdes_init_seq->reg_config[i].reg,
                                   serdes_init_seq->reg_config[i].def);
            if (ret != RT_EOK)
            {
                num++;
                rt_kprintf("%s write reg %04x fali\n", serdes->dev_name,
                           serdes_init_seq->reg_config[i].reg);
                continue;
            }
        }

        serdes_reg_read(serdes_client, serdes_init_seq->reg_config[i].reg, &def);
        if ((def != serdes_init_seq->reg_config[i].def) || (ret < 0))
        {
            /* if read value != write value then write again */
            rt_kprintf("%s read %04x %04x != %04x\n", serdes->dev_name,
                       serdes_init_seq->reg_config[i].reg,
                       def, serdes_init_seq->reg_config[i].def);
            serdes_reg_write(serdes_client,
                             serdes_init_seq->reg_config[i].reg,
                             serdes_init_seq->reg_config[i].def);
        }
    }

    if (serdes->chip_data.serdes_id == MAXIM_ID_MAX96752)
    {
        ret = serdes_reg_write(serdes_client, 0x10, 0x21);
        if (ret != RT_EOK)
            rt_kprintf("%s reset oneshot fali, ret=%d\n", serdes->dev_name, ret);
        else
            rt_kprintf("%s reset oneshot\n", serdes->dev_name);
        rt_thread_mdelay(20);
    }

    SERDES_DBG_MFD("serdes %s sequence init complete!\n", serdes->dev_name);
    return RT_EOK;
}

rt_err_t serdes_i2c_set_iomux(rt_serdes_t serdes)
{
    rt_int8_t ret = 0;
    rt_uint8_t i, def, num = 0;
    struct rt_serdes_config *serdes_init_iomux;
    struct rt_i2c_client *serdes_client = serdes->serdes_client;

    if (!serdes_client)
        return -RT_ERROR;

    serdes_init_iomux = &serdes->serdes_desc.serdes_init_iomux;
    if (!serdes_init_iomux || !serdes_init_iomux->reg_config)
        return -RT_ERROR;

    for (i = 0; i < serdes_init_iomux->reg_config_cnt; i++)
    {
        if (num >= RT_I2C_ERROR_TIMES)
            return -RT_ERROR;

        if (serdes_init_iomux->reg_config[i].reg == 0xffff)
        {
            SERDES_DBG_MFD("serdes %s delay %d ms\n", serdes->dev_name,
                           serdes_init_iomux->reg_config[i].def);

            rt_thread_mdelay(serdes_init_iomux->reg_config[i].def);
            continue;
        }

        ret = serdes_set_bits(serdes_client,
                              serdes_init_iomux->reg_config[i].reg,
                              serdes_init_iomux->reg_config[i].mask,
                              serdes_init_iomux->reg_config[i].def);
        if (ret != RT_EOK)
        {
            num++;
            rt_kprintf("%s serdes_set_bits Reg%04x fali, ret=%d\n", serdes->dev_name,
                       serdes_init_iomux->reg_config[i].reg, ret);
            continue;
        }
    }

    SERDES_DBG_MFD("serdes %s iomux complete!\n", serdes->dev_name);
    return RT_EOK;
}

static rt_err_t rt_serdes_init(rt_device_t dev)
{
    rt_int8_t ret;
    rt_serdes_t serdes;

    if (!dev)
    {
        rt_kprintf("%s: serdes dev is NULL\n", __func__);
        return -RT_ERROR;
    }

    serdes = rt_container_of(dev, struct rt_serdes, parent);

    if (serdes->chip_data.serdes_type == TYPE_SER)
    {
        if (serdes_i2c_set_sequence(serdes) != RT_EOK)
        {
            rt_kprintf("serdes %s failed to set sequence\n", serdes->dev_name);
            return -RT_ERROR;
        }
    }

    if (serdes->chip_data.iomux_ops)
    {
        ret = serdes->chip_data.iomux_ops->set_mux(serdes);
        if (ret != RT_EOK)
        {
            rt_kprintf("serdes %s failed to set iomux\n", serdes->dev_name);
            return -RT_ERROR;
        }
    }

    if (serdes->chip_data.bridge_ops)
    {
        serdes->chip_data.bridge_ops->detect(serdes, LINKA);
    }

    return RT_EOK;
}

static rt_err_t rt_serdes_control(rt_device_t dev, int cmd, void *args)
{
    rt_serdes_t serdes;

    if (!dev)
    {
        rt_kprintf("%s: serdes dev is NULL\n", __func__);
        return -RT_ERROR;
    }

    serdes = rt_container_of(dev, struct rt_serdes, parent);

    switch (cmd)
    {
    case RT_SERDES_PANEL_INIT:

        if (serdes->chip_data.serdes_type != TYPE_DES)
            return RT_EOK;

        if (serdes_i2c_set_sequence(serdes) != RT_EOK)
        {
            rt_kprintf("serdes %s failed to set sequence\n", serdes->dev_name);
            return -RT_ERROR;
        }

        break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rt_serdes_ops =
{
    rt_serdes_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_serdes_control
};
#endif

/*
 * serdes register
 */
static int rt_hw_serdes_register(rt_serdes_t serdes,
                                 const char              *name,
                                 rt_uint32_t              flag,
                                 void                    *data)
{
    rt_int8_t result;
    rt_device_t device;
    RT_ASSERT(serdes != RT_NULL);

    device = &serdes->parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rt_serdes_ops;
#else
    device->init        = rt_serdes_init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_serdes_control;
#endif
    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = data;

    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_STANDALONE);

    if (result != RT_EOK)
    {
        LOG_E("rt_serdes register err code: %d", result);
        return result;
    }

    LOG_I("rt_serdes %s init success", name);

    return RT_EOK;
}

rt_err_t rt_serdes_register(rt_serdes_t serdes)
{
    rt_int8_t ret;
    struct rt_i2c_client *serdes_client;
    struct serdes_desc *serdes_desc = &serdes->serdes_desc;

    if (!serdes || !serdes_desc)
        return -RT_ERROR;

    serdes_client = (struct rt_i2c_client *)rt_calloc(1, sizeof(struct rt_i2c_client));
    if (!serdes_client)
    {
        rt_kprintf("%s: serdes_cient failed to apply for memory\n", __func__);
        return -RT_ERROR;
    }

    serdes_client->client_addr = serdes_desc->i2c_addr;
    serdes_client->bus = (struct rt_i2c_bus_device *)rt_device_find(serdes_desc->i2c_bus);
    if (!serdes_client->bus)
    {
        rt_kprintf("%s: unable to find %s\n", __func__, serdes_desc->i2c_bus);
        rt_free(serdes_client);
        return -RT_ERROR;
    }

    ret = rt_hw_serdes_register(serdes, serdes->dev_name, RT_DEVICE_FLAG_INT_RX, RT_NULL);
    if (ret)
    {
        rt_kprintf("failed to register serdes device %s\n", serdes->dev_name);
        rt_free(serdes_client);
        return -RT_ERROR;
    }

    serdes->serdes_client = serdes_client;

    rt_kprintf("serdes %s registered\n", serdes->dev_name);
    return RT_EOK;
}