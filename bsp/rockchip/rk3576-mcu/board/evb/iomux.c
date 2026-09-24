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
RT_WEAK void gpio1_d5_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK1,
                         GPIO_PIN_D5,     // JTAG_TMS_M0
                         PIN_CONFIG_MUX_FUNC0);
}

RT_WEAK void pwm0_ch0_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C4,     
                         PIN_CONFIG_MUX_FUNC12);
}

RT_WEAK void spi4_m3_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B2 |
			 GPIO_PIN_B3 |     
                         GPIO_PIN_B4 |
			 GPIO_PIN_B5,     
                         PIN_CONFIG_MUX_FUNC10);
}
RT_WEAK void spi0_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D0 |
			 GPIO_PIN_D1 ,    
                         PIN_CONFIG_MUX_FUNC11);
}
void rt_hw_iomux_config(void)
{
#ifdef RT_USING_UART
#ifdef RT_USING_UART5
    uart5_m2_iomux_config();
#endif
#ifdef RT_USING_UART7
    uart7_m2_iomux_config();
#endif
#ifdef RT_USING_UART8
    uart8_m1_iomux_config();
#endif
#endif
#ifdef RT_USING_I2C7
    i2c7_m1_iomux_config();
#endif
#ifdef RT_USING_I2C8
    i2c8_m2_iomux_config();
#endif
#ifdef RT_USING_PERI_EN
    peri_s0_iomux_config();
#endif
    gpio1_d5_iomux_config();
#ifdef RT_USING_I2C
    i2c7_m1_iomux_config();
#endif
#ifdef RT_USING_PWM
    pwm0_ch0_m0_iomux_config();
#endif
#ifdef RT_USING_SPI
    spi4_m3_iomux_config();
    spi0_m0_iomux_config();
#endif
}
