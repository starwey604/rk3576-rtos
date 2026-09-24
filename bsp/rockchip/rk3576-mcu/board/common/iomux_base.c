/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-12     Steven Liu   first implementation
 */

#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"
#include "drivers/pin.h"

/**
 * @brief  Config iomux m1 for I2C7
 */
RT_WEAK void i2c7_m1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A0,
                         PIN_CONFIG_MUX_FUNC11);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC11);
}

/**
 * @brief  Config iomux m2 for I2C8
 */
RT_WEAK void i2c8_m2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B6,
                         PIN_CONFIG_MUX_FUNC11);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B7,
                         PIN_CONFIG_MUX_FUNC11);
}

/**
 * @brief  Config iomux for PERI_5V_EN
 */
RT_WEAK void peri_s0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B6,
                         PIN_CONFIG_MUX_FUNC0);

    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_B6, // vcc5v0_peri_s0
                         PIN_CONFIG_PUL_UP);

    HAL_GPIO_SetPinDirection(GPIO0_EXP2, GPIO_PIN_B6, GPIO_OUT);
    HAL_GPIO_SetPinLevel(GPIO0_EXP2, GPIO_PIN_B6, GPIO_HIGH);
}

/**
 * @brief  Config iomux m1 for UART8
 */
RT_WEAK void uart8_m1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A6,
                         PIN_CONFIG_MUX_FUNC9);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A7,
                         PIN_CONFIG_MUX_FUNC9);
}

/**
 * @brief  Config iomux m2 for UART5
 */
RT_WEAK void uart5_m2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_B1,
                         PIN_CONFIG_MUX_FUNC10);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_B0,
                         PIN_CONFIG_MUX_FUNC10);
}

/**
 * @brief  Config iomux m0 for UART5
 *         LubanCat 3 exposes UART5 on the 40-pin header as
 *         GPIO3_D4 (UART5_RX_M0) / GPIO3_D5 (UART5_TX_M0).
 */
RT_WEAK void uart5_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_D4,
                         PIN_CONFIG_MUX_FUNC9);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_D5,
                         PIN_CONFIG_MUX_FUNC9);
}

/**
 * @brief  Config iomux m2 for UART7
 */
RT_WEAK void uart7_m2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A0,
                         PIN_CONFIG_MUX_FUNC10);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC10);
}

/**
 * @brief  Config iomux for SPI4
 */
RT_WEAK void spi4_m3_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B2 |  // SPI4_CSN0_M3
                         GPIO_PIN_B3 |  // SPI4_CLK_M3
                         GPIO_PIN_B4 |  // SPI4_MOSI_M3
                         GPIO_PIN_B5,   // SPI4_MISO_M3
                         PIN_CONFIG_MUX_FUNC10);
}

/**
 * @brief  Config iomux for RK3576
 */
RT_WEAK void rt_hw_iomux_config(void)
{
#ifdef RT_USING_UART

#ifdef RT_USING_UART5
    uart5_m2_iomux_config();
#endif
#endif
}
