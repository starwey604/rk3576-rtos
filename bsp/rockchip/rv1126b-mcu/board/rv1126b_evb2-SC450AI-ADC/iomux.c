/*
 * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-26     LongChang Ma   first implementation
 */

#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"

/**
 * @brief  Config iomux for RV1126B's camera
 */
static void cam_iomux_config(void)
{
    /* Config iomux gpio :MIPI_REFCLK_OUT0 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4, GPIO_PIN_B1, PIN_CONFIG_MUX_FUNC3);
}

/**
 * @brief  Config iomux for RV1126B's gpio
 */
static void gpio_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4, GPIO_PIN_A2, PIN_CONFIG_MUX_FUNC0);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4, GPIO_PIN_A7, PIN_CONFIG_MUX_FUNC0);
}

/**
 * @brief  Config iomux for RV1126B
 */
void rt_hw_iomux_config(void)
{
    cam_iomux_config();
    gpio_iomux_config();
    i2c3_m1_iomux_config();
}
