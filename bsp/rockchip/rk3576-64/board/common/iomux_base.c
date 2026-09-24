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
 * @brief  Config iomux m0 for SPI0
 */
RT_WEAK void spi0_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D0 |
                         GPIO_PIN_D1 ,
                         PIN_CONFIG_MUX_FUNC11);
}
/**
 * @brief  Config iomux m0 for I2C0
 */
RT_WEAK void i2c0_m1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C1,
                         PIN_CONFIG_MUX_FUNC9);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C2,
                         PIN_CONFIG_MUX_FUNC9);
}

/**
 * @brief  Config iomux m0 for I2C0
 */
RT_WEAK void i2c1_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B2,
                         PIN_CONFIG_MUX_FUNC11);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B3,
                         PIN_CONFIG_MUX_FUNC11);
}

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
 * @brief  Config iomux m0 for UART0
 */
RT_WEAK void uart0_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D4,
                         PIN_CONFIG_MUX_FUNC9);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D5,
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
 * @brief  Config iomux m0 for CAN0
 */
RT_WEAK void can0_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A0,
                         PIN_CONFIG_MUX_FUNC13);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A1,
                         PIN_CONFIG_MUX_FUNC13);
}

/**
 * @brief  Config iomux m0 for pwm0_2ch0
 */
RT_WEAK void pwm0_2ch0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C4,
                         PIN_CONFIG_MUX_FUNC12);
}

/**
 * @brief  Config iomux m1 for pwm3_8ch3
 */
RT_WEAK void pwm2_8ch3_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_C7,
                         PIN_CONFIG_MUX_FUNC14);
}

/**
 * @brief  Config iomux for DSMC_HOST
 */
RT_WEAK void dsmc_host_iomux_config(void)
{
    /* need pull up first */
    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_D6 |   // DSMC_CLKN
                         GPIO_PIN_D7 |   // DSMC_RESETN
                         GPIO_PIN_D3 |   // DSMC_CSN0
                         GPIO_PIN_B0 |   // DSMC_CSN1
                         GPIO_PIN_D1 |   // DSMC_CSN2
                         GPIO_PIN_D2,    // DSMC_CSN3
                         PIN_CONFIG_PUL_UP);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_D5 |   // DSMC_CLKP
                         GPIO_PIN_D6 |   // DSMC_CLKN
                         GPIO_PIN_B7 |   // DSMC_DQS0
                         GPIO_PIN_D4 |   // DSMC_D0
                         GPIO_PIN_D0 |   // DSMC_D1
                         GPIO_PIN_C7 |   // DSMC_D2
                         GPIO_PIN_C6 |   // DSMC_D3
                         GPIO_PIN_C5 |   // DSMC_D4
                         GPIO_PIN_C4 |   // DSMC_D5
                         GPIO_PIN_B0 |   // DSMC_CSN1
                         GPIO_PIN_C3 |   // DSMC_INT3
                         GPIO_PIN_C1 |   // DSMC_D6
                         GPIO_PIN_C0 |   // DSMC_D7
                         GPIO_PIN_D3 |   // DSMC_CSN0
                         GPIO_PIN_A4 |   // DSMC_RDYN
                         GPIO_PIN_D7 |   // DSMC_RESETN
                         GPIO_PIN_B5 |   // DSMC_D8
                         GPIO_PIN_B4 |   // DSMC_D9
                         GPIO_PIN_B3 |   // DSMC_D10
                         GPIO_PIN_B2 |   // DSMC_D11
                         GPIO_PIN_B1 |   // DSMC_D12
                         GPIO_PIN_A7 |   // DSMC_D13
                         GPIO_PIN_A6 |   // DSMC_D14
                         GPIO_PIN_A5 |   // DSMC_D15
                         GPIO_PIN_B6 |   // DSMC_DQS1
                         GPIO_PIN_D1 |   // DSMC_CSN2
                         GPIO_PIN_D2,    // DSMC_CSN3
                         PIN_CONFIG_MUX_FUNC5);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A1,    // DSMC_INT2
                         PIN_CONFIG_MUX_FUNC5);

    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_D5 |   // DSMC_CLKP
                         GPIO_PIN_D6 |   // DSMC_CLKN
                         GPIO_PIN_B7 |   // DSMC_DQS0
                         GPIO_PIN_D4 |   // DSMC_D0
                         GPIO_PIN_D0 |   // DSMC_D1
                         GPIO_PIN_C7 |   // DSMC_D2
                         GPIO_PIN_C6 |   // DSMC_D3
                         GPIO_PIN_C5 |   // DSMC_D4
                         GPIO_PIN_C4 |   // DSMC_D5
                         GPIO_PIN_B0 |   // DSMC_CSN1
                         GPIO_PIN_C3 |   // DSMC_INT3
                         GPIO_PIN_C1 |   // DSMC_D6
                         GPIO_PIN_C0 |   // DSMC_D7
                         GPIO_PIN_D3 |   // DSMC_CSN0
                         GPIO_PIN_A4 |   // DSMC_RDYN
                         GPIO_PIN_D7 |   // DSMC_RESETN
                         GPIO_PIN_B5 |   // DSMC_D8
                         GPIO_PIN_B4 |   // DSMC_D9
                         GPIO_PIN_B3 |   // DSMC_D10
                         GPIO_PIN_B2 |   // DSMC_D11
                         GPIO_PIN_B1 |   // DSMC_D12
                         GPIO_PIN_A7 |   // DSMC_D13
                         GPIO_PIN_A6 |   // DSMC_D14
                         GPIO_PIN_A5 |   // DSMC_D15
                         GPIO_PIN_B6 |   // DSMC_DQS1
                         GPIO_PIN_D1 |   // DSMC_CSN2
                         GPIO_PIN_D2,    // DSMC_CSN3
                         PIN_CONFIG_DRV_LEVEL2);

    HAL_PINCTRL_SetParam(GPIO_BANK4,
                         GPIO_PIN_A1,    // DSMC_INT2
                         PIN_CONFIG_DRV_LEVEL2);
}

/**
 * @brief  Config iomux for DSMC_HOST local bus
 */
RT_WEAK void dsmc_host_lb_iomux_config(void)
{
    /* need pull down first */
    HAL_PINCTRL_SetParam(GPIO_BANK4,
                         GPIO_PIN_A0,    // DSMC_INT0
                         PIN_CONFIG_PUL_DOWN | PIN_CONFIG_DRV_LEVEL2);

    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_C2,    // DSMC_INT1
                         PIN_CONFIG_PUL_DOWN | PIN_CONFIG_DRV_LEVEL2);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A0,    // DSMC_INT0
                         PIN_CONFIG_MUX_FUNC5);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_C2,    // DSMC_INT1
                         PIN_CONFIG_MUX_FUNC5);
}

/**
 * @brief  Config iomux for Flexbus ADC mode
 */
RT_WEAK  void flexbus_adc_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_D6 |  // FLEXBUS1_CLK
                         GPIO_PIN_D5 |  // FLEXBUS1_D0
                         GPIO_PIN_D4 |  // FLEXBUS1_D1
                         GPIO_PIN_D3 |  // FLEXBUS1_D2
                         GPIO_PIN_D0 |  // FLEXBUS1_D3
                         GPIO_PIN_C7 |  // FLEXBUS1_D4
                         GPIO_PIN_C6 |  // FLEXBUS1_D5
                         GPIO_PIN_C5 |  // FLEXBUS1_D6
                         GPIO_PIN_C4 |  // FLEXBUS1_D7
                         GPIO_PIN_C1 |  // FLEXBUS1_D8
                         GPIO_PIN_C0 |  // FLEXBUS1_D9
                         GPIO_PIN_B7 |  // FLEXBUS1_D10
                         GPIO_PIN_A4,   // FLEXBUS1_D11
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A5 |  // FLEXBUS1_D12_M1
                         GPIO_PIN_B0 |  // FLEXBUS1_D13_M1
                         GPIO_PIN_B1 |  // FLEXBUS1_D14_M1
                         GPIO_PIN_B2,   // FLEXBUS1_D15_M1
                         PIN_CONFIG_MUX_FUNC4);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A3,   // FLEXBUS1_CSN_M4
                         PIN_CONFIG_MUX_FUNC4);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B4,   // REF_CLK1_OUT, only used for slave-mode
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for Flexbus DAC mode
 */
RT_WEAK  void flexbus_dac_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B6 |  // FLEXBUS0_CLK
                         GPIO_PIN_B5 |  // FLEXBUS0_D0
                         GPIO_PIN_B4 |  // FLEXBUS0_D1
                         GPIO_PIN_B3 |  // FLEXBUS0_D2
                         GPIO_PIN_B2 |  // FLEXBUS0_D3
                         GPIO_PIN_B1 |  // FLEXBUS0_D4
                         GPIO_PIN_A7 |  // FLEXBUS0_D5
                         GPIO_PIN_A6 |  // FLEXBUS0_D6
                         GPIO_PIN_A5 |  // FLEXBUS0_D7
                         GPIO_PIN_B0 |  // FLEXBUS0_D8
                         GPIO_PIN_C2 |  // FLEXBUS0_D9
                         GPIO_PIN_C3 |  // FLEXBUS0_D10
                         GPIO_PIN_D1 |  // FLEXBUS0_D11
                         GPIO_PIN_D2,   // FLEXBUS0_D12
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A0 |  // FLEXBUS0_D13_M0
                         GPIO_PIN_A1,   // FLEXBUS0_D14_M0
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_D7,   // FLEXBUS0_D15_M0
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_B4,   // FLEXBUS0_CSN_M4
                         PIN_CONFIG_MUX_FUNC4);
}

/**
 * @brief  Config iomux for Flexbus SPI mode
 */
RT_WEAK  void flexbus_spi_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B6 |  // FLEXBUS0_CLK
                         GPIO_PIN_B5 |  // FLEXBUS0_D0
                         GPIO_PIN_B4 |  // FLEXBUS0_D1
                         GPIO_PIN_B3 |  // FLEXBUS0_D2
                         GPIO_PIN_B2 |  // FLEXBUS0_D3
                         GPIO_PIN_B1 |  // FLEXBUS0_D4
                         GPIO_PIN_A7 |  // FLEXBUS0_D5
                         GPIO_PIN_A6 |  // FLEXBUS0_D6
                         GPIO_PIN_A5 |  // FLEXBUS0_D7
                         GPIO_PIN_B0 |  // FLEXBUS0_D8
                         GPIO_PIN_C2 |  // FLEXBUS0_D9
                         GPIO_PIN_C3 |  // FLEXBUS0_D10
                         GPIO_PIN_D1 |  // FLEXBUS0_D11
                         GPIO_PIN_D2 |  // FLEXBUS0_D12
                         GPIO_PIN_D7,   // FLEXBUS0_D15
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A0 |  // FLEXBUS0_D13
                         GPIO_PIN_A1,   // FLEXBUS0_D14
                         PIN_CONFIG_MUX_FUNC6);
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3, GPIO_PIN_A4, PIN_CONFIG_MUX_FUNC8); /* CSN_M0 */
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
#ifdef RT_USING_CAN
#ifdef RT_USING_CAN0
    can0_m0_iomux_config();
#endif
#ifdef RT_USING_DSMC_HOST
    dsmc_host_iomux_config();
#endif
#endif
#ifdef RT_USING_FLEXBUS
#ifdef RT_USING_FLEXBUS_ADC
    flexbus_adc_iomux_config();
#endif
#ifdef RT_USING_FLEXBUS_DAC
    flexbus_dac_iomux_config();
#endif
#ifdef RT_USING_FLEXBUS_SPI
    flexbus_spi_iomux_config();
#endif
#endif
}
