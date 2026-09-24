/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    serdes_i2c.c
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#include "core.h"
#include "hal_base.h"

static char *serdes_dev_list[RT_SERDES_DEV_MAX + 1] = {0};

int rt_serdes_probe(void)
{
    rt_int8_t cnt = 0;
    rt_serdes_t serdes;
    const struct serdes_desc *serdes_desc;

    if (!rk_board_display_serdes[0].name)
    {
        rt_kprintf("rk_board_display_serdes is empty\n");
        return -RT_ERROR;
    }

    for (serdes_desc = rk_board_display_serdes; serdes_desc->name != RT_NULL; serdes_desc++)
    {
        serdes = rt_serdes_match(serdes_desc);
        if (!serdes)
            continue;

        if (rt_serdes_register(serdes) != RT_EOK)
            continue;

        if (cnt == RT_SERDES_DEV_MAX)
        {
            rt_kprintf("serdes num buffer is full\n");
            return RT_EOK;
        }

        serdes_dev_list[cnt++] = serdes->dev_name;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_serdes_probe);

void rt_serdes_thread(void *parameter)
{
    rt_int8_t i, ret;
    rt_device_t serdes;

    for (i = 0; serdes_dev_list[i] != RT_NULL; i++)
    {
        serdes = rt_device_find(serdes_dev_list[i]);
        if (!serdes)
        {
            rt_kprintf("Can't find device: %s\n", serdes_dev_list[i]);
            continue;
        }

        ret = rt_device_init(serdes);
        if (ret != RT_EOK)
            continue;

        ret = rt_device_control(serdes, RT_SERDES_PANEL_INIT, RT_NULL);
        if (ret != RT_EOK)
        {
            rt_kprintf("serdes panel %s init failed!\n", serdes_dev_list[i]);
            continue;
        }

        rt_kprintf("serdes %s init successful!\n", serdes_dev_list[i]);
    }

    return;
};

int rt_serdes_start(void)
{
    rt_thread_t serdes_thread;

    serdes_thread = rt_thread_create("rt_serdes_work_thread",
                                     rt_serdes_thread, RT_NULL,
                                     1024, 16, 20);
    if (serdes_thread == RT_NULL)
    {
        rt_kprintf("failed to create serdes thread\n");
        return -RT_ERROR;
    }

    rt_thread_startup(serdes_thread);

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rt_serdes_start);
