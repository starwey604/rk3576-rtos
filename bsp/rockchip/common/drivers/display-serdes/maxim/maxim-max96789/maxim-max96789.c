/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    maxim-max96789.c
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#include "maxim-max96789.h"

static rt_bool_t max96789_bridge_linka_locked(rt_serdes_t serdes)
{

    rt_uint8_t i, val = 0;

    for (i = 0; i < 40; i++)
    {
        rt_thread_mdelay(5);
        if (serdes_reg_read(serdes->serdes_client, 0x001f, &val))
        {
            SERDES_DBG_CHIP("%s unlock val=0x%x\n", __func__, val);
            continue;
        }

        if (!FIELD_GET(LINKA_LOCKED, val))
        {
            SERDES_DBG_CHIP("%s unlock val=0x%x\n", __func__, val);
            continue;
        }

        rt_kprintf("serdes reg locked 0x%x, wait times %d\n", val, i);

        return RT_TRUE;
    }

    rt_kprintf("serdes %s link lock timeout\n", serdes->dev_name);

    return RT_TRUE;
}

static rt_bool_t max96789_bridge_linkb_locked(rt_serdes_t serdes)
{
    rt_uint8_t val = 0, i = 0;

    for (i = 0; i < 100; i++)
    {
        rt_thread_mdelay(5);
        if (serdes_reg_read(serdes->serdes_client, 0x001f, &val))
        {
            SERDES_DBG_CHIP("%s unlock val=0x%x\n", __func__, val);
            continue;
        }

        if (!FIELD_GET(LINKB_LOCKED, val))
        {
            SERDES_DBG_CHIP("%s unlock val=0x%x\n", __func__, val);
            continue;
        }

        rt_kprintf("serdes reg locked 0x%x, wait times %d\n", val, i);

        return RT_TRUE;
    }

    rt_kprintf("serdes %s link lock timeout\n", serdes->dev_name);

    return RT_TRUE;
}

static rt_bool_t max96789_bridge_detect(rt_serdes_t serdes, rt_uint8_t link)
{
    SERDES_DBG_CHIP("%s enter %s\n", serdes->dev_name, __func__);

    if (link == LINKA)
        return max96789_bridge_linka_locked(serdes);
    else
        return max96789_bridge_linkb_locked(serdes);
}

static rt_err_t max96789_set_pin_mux(rt_serdes_t serdes)
{
    SERDES_DBG_CHIP("%s start set pin mux\n", serdes->dev_name);

    serdes_i2c_set_iomux(serdes);
}

static struct rt_serdes_chip_bridge_ops max96789_bridge_ops =
{
    .detect = max96789_bridge_detect,
};

static struct rt_serdes_chip_iomux_ops max96789_iomux_ops =
{
    .set_mux = max96789_set_pin_mux,
};

struct serdes_chip_data serdes_max96789_data =
{
    .name       = "max96789",
    .serdes_type    = TYPE_SER,
    .serdes_id = MAXIM_ID_MAX96789,
    .iomux_ops  = &max96789_iomux_ops,
    .bridge_ops = &max96789_bridge_ops,
};