/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-19     Jason Zhu   first implementation
 */

#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"

#ifdef RT_USING_PIN
#ifdef RT_USING_I2C0
/**
 * @brief  Config iomux m0 for I2C0
 */
RT_WEAK void i2c0_m0_iomux_config(void)
{
    /* I2C0 M0 SCL-0C2 SDA-0C3 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C2 | GPIO_PIN_C3,
                         PIN_CONFIG_MUX_FUNC5);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_C2 | GPIO_PIN_C3,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C0
 */
RT_WEAK void i2c0_m1_iomux_config(void)
{
    /* I2C0 M1 SCL-2A1 SDA-2A0 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC3);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK2,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif
#ifdef RT_USING_I2C1
/**
 * @brief  Config iomux m0 for I2C1
 */
RT_WEAK void i2c1_m0_iomux_config(void)
{
    /* I2C1 M0 SCL-0B3 SDA-0B4 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B3 | GPIO_PIN_B4,
                         PIN_CONFIG_MUX_FUNC3);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_B3 | GPIO_PIN_B4,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C1
 */
RT_WEAK void i2c1_m1_iomux_config(void)
{
    /* I2C1 M1 SCL-3A2 SDA-3A3 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A2 | GPIO_PIN_A3,
                         PIN_CONFIG_MUX_FUNC2);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_A2 | GPIO_PIN_A3,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m2 for I2C1
 */
RT_WEAK void i2c1_m2_iomux_config(void)
{
    /* I2C1 M2 SCL-4A1 SDA-4A0 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK4,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m3 for I2C1
 */
RT_WEAK void i2c1_m3_iomux_config(void)
{
    /* I2C1 M3 SCL-7B0 SDA-7B1 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK7,
                         GPIO_PIN_B0 | GPIO_PIN_B1,
                         PIN_CONFIG_MUX_FUNC5);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK7,
                         GPIO_PIN_B0 | GPIO_PIN_B1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif
#ifdef RT_USING_I2C2
/**
 * @brief  Config iomux m0 for I2C2
 */
RT_WEAK void i2c2_m0_iomux_config(void)
{
    /* I2C2 M0 SCL-0D0 SDA-0D1 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D0 | GPIO_PIN_D1,
                         PIN_CONFIG_MUX_FUNC1);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_D0 | GPIO_PIN_D1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C2
 */
RT_WEAK void i2c2_m1_iomux_config(void)
{
    /* I2C2 M1 SCL-5D4 SDA-5D5 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK5,
                         GPIO_PIN_D4 | GPIO_PIN_D5,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK5,
                         GPIO_PIN_D4 | GPIO_PIN_D5,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m2 for I2C2
 */
RT_WEAK void i2c2_m2_iomux_config(void)
{
    /* I2C2 M2 SCL-6C0 SDA-6C3 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK6,
                         GPIO_PIN_C0 | GPIO_PIN_C3,
                         PIN_CONFIG_MUX_FUNC8);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK6,
                         GPIO_PIN_C0 | GPIO_PIN_C3,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif
#ifdef RT_USING_I2C3
/**
 * @brief  Config iomux m0 for I2C3
 */
RT_WEAK void i2c3_m0_iomux_config(void)
{
    /* I2C3 M0 SCL-0C0 SDA-0C1 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C0 | GPIO_PIN_C1,
                         PIN_CONFIG_MUX_FUNC1);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_C0 | GPIO_PIN_C1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C3
 */
RT_WEAK void i2c3_m1_iomux_config(void)
{
    /* I2C3 M1 SCL-4A4 SDA-4A5 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A4 | GPIO_PIN_A5,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK4,
                         GPIO_PIN_A4 | GPIO_PIN_A5,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m2 for I2C3
 */
RT_WEAK void i2c3_m2_iomux_config(void)
{
    /* I2C3 M2 SCL-5D0 SDA-5D1 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK5,
                         GPIO_PIN_D0 | GPIO_PIN_D1,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK5,
                         GPIO_PIN_D0 | GPIO_PIN_D1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m3 for I2C3
 */
RT_WEAK void i2c3_m3_iomux_config(void)
{
    /* I2C3 M3 SCL-6A0 SDA-6A1 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK6,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC8);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK6,
                         GPIO_PIN_A0 | GPIO_PIN_A1,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif
#ifdef RT_USING_I2C4
/**
 * @brief  Config iomux m0 for I2C4
 */
RT_WEAK void i2c4_m0_iomux_config(void)
{
    /* I2C4 M0 SCL-3B4 SDA-3B5 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B4 | GPIO_PIN_B5,
                         PIN_CONFIG_MUX_FUNC5);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_B4 | GPIO_PIN_B5,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C4
 */
RT_WEAK void i2c4_m1_iomux_config(void)
{
    /* I2C4 M1 SCL-6A2 SDA-6A3 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK6,
                         GPIO_PIN_A2 | GPIO_PIN_A3,
                         PIN_CONFIG_MUX_FUNC8);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK6,
                         GPIO_PIN_A2 | GPIO_PIN_A3,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m2 for I2C4
 */
RT_WEAK void i2c4_m2_iomux_config(void)
{
    /* I2C4 M2 SCL-4A7 SDA-4A6 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A6 | GPIO_PIN_A7,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK4,
                         GPIO_PIN_A6 | GPIO_PIN_A7,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif
#ifdef RT_USING_I2C5
/**
 * @brief  Config iomux m0 for I2C5
 */
RT_WEAK void i2c5_m0_iomux_config(void)
{
    /* I2C5 M0 SCL-0C4 SDA-0C5 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C4 | GPIO_PIN_C5,
                         PIN_CONFIG_MUX_FUNC5);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_C4 | GPIO_PIN_C5,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m1 for I2C5
 */
RT_WEAK void i2c5_m1_iomux_config(void)
{
    /* I2C5 M1 SCL-3B6 SDA-3B7 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B6 | GPIO_PIN_B7,
                         PIN_CONFIG_MUX_FUNC5);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_B6 | GPIO_PIN_B7,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}

/**
 * @brief  Config iomux m2 for I2C5
 */
RT_WEAK void i2c5_m2_iomux_config(void)
{
    /* I2C5 M2 SCL-5A1 SDA-5A7 */
    HAL_PINCTRL_SetIOMUX(GPIO_BANK5, GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC2);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK5, GPIO_PIN_A7,
                         PIN_CONFIG_MUX_FUNC6);
    /* pull none smt */
    HAL_PINCTRL_SetParam(GPIO_BANK5,
                         GPIO_PIN_A1 | GPIO_PIN_A7,
                         PIN_CONFIG_PUL_NORMAL |
                         PIN_CONFIG_SMT_ENABLE);
}
#endif

#ifdef RT_USING_UART4
RT_WEAK void uart4_m2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK6,
                         GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK6,
                         GPIO_PIN_A0,
                         PIN_CONFIG_MUX_FUNC6);
}
#endif
#endif

/**
 * @brief  Config iomux for RV1126B
 */
RT_WEAK void rt_hw_iomux_config(void)
{
}

