/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-08     Jason Zhu    first implementation
 */

/** @addtogroup RKBSP_Board_Driver
 *  @{
 */

/** @addtogroup IOMUX
 *  @{
 */

/** @defgroup How_To_Use How To Use
 *  @{
 @verbatim

 ==============================================================================
                    #### How to use ####
 ==============================================================================
 This file provide IOMUX for board, it will be invoked when board initialization.

 @endverbatim
 @} */
#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"

/********************* Private MACRO Definition ******************************/
/** @defgroup IOMUX_Private_Macro Private Macro
 *  @{
 */

/** @} */  // IOMUX_Private_Macro

/********************* Private Structure Definition **************************/
/** @defgroup IOMUX_Private_Structure Private Structure
 *  @{
 */

/** @} */  // IOMUX_Private_Structure

/********************* Private Variable Definition ***************************/
/** @defgroup IOMUX_Private_Variable Private Variable
 *  @{
 */

/** @} */  // IOMUX_Private_Variable

/********************* Private Function Definition ***************************/
/** @defgroup IOMUX_Private_Function Private Function
 *  @{
 */

/** @} */  // IOMUX_Private_Function

/********************* Public Function Definition ****************************/
/**
 * @brief  Config iomux for FSPI0
 */
void fspi0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK4,
                         GPIO_PIN_A0 |  // FSPI_D3
                         GPIO_PIN_A1 |  // FSPI_D1
                         GPIO_PIN_A2 |  // FSPI_CSN
                         GPIO_PIN_A3 |  // FSPI_D0
                         GPIO_PIN_B4 |  // FSPI_CLK
                         GPIO_PIN_B5,   // FSPI_D2
                         PIN_CONFIG_MUX_FUNC1);
}

void can_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A0,   // CAN_TX
                        RM1_IO_CAN_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A1,   // CAN_RX
                        RM1_IO_CAN_RX);
}

/**
 * @brief  Config iomux for I2C1
 */
void i2c1_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_A0,   // I2C1_SCL,
                        RM0_IO_I2C1_SCL);

    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_A1,   // I2C1_SDA
                        RM0_IO_I2C1_SDA);
}

/**
 * @brief  Config iomux for pwm0
 */
void pwm0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A3,   // PWM0_CH2
                        RM0_IO_PWM0_CH2);
}

/**
 * @brief  Config iomux for SAI1
 */
void sai1_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A0,   // SAI1_SCLK
                        RM2_IO_SAI1_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A1,   // SAI1_LRCK
                        RM2_IO_SAI1_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A2,   // SAI1_SDI0
                        RM2_IO_SAI1_SDI0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A3,   // SAI1_SDI1
                        RM2_IO_SAI1_SDI1);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A4,   // SAI1_SDO0
                        RM2_IO_SAI1_SDO0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A5,   // SAI1_SDO1
                        RM2_IO_SAI1_SDO1);
}

/**
 * @brief  Config iomux for SAI2
 */
void sai2_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B4,   // SAI2_SCLK
                        RM2_IO_SAI2_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B5,   // SAI2_LRCK
                        RM2_IO_SAI2_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B6,   // SAI2_SDO0
                        RM2_IO_SAI2_SDO0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B7,   // SAI2_SDO1
                        RM2_IO_SAI2_SDO1);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_C0,   // SAI2_SDI0
                        RM2_IO_SAI2_SDI0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_C1,   // SAI2_SDI1
                        RM2_IO_SAI2_SDI1);

}

/**
 * @brief  Config iomux for SAI3
 */
void sai3_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A6,   // SAI3_SCLK
                        RM2_IO_SAI3_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A7,   // SAI3_LRCK
                        RM2_IO_SAI3_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B0,   // SAI3_SDI0
                        RM2_IO_SAI3_SDI0);
}

/**
 * @brief  Config iomux for SAI4
 */
void sai4_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK4,
                        GPIO_PIN_B0,   // SAI4_SCLK
                        RM2_IO_SAI4_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK4,
                        GPIO_PIN_B1,   // SAI4_LRCK
                        RM2_IO_SAI4_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK4,
                        GPIO_PIN_B2,   // SAI4_SDI0
                        RM2_IO_SAI4_SDI);
}

/**
 * @brief  Config iomux for SPI0
 */
void spi0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B0 |  // SPI0_CLK
                         GPIO_PIN_A6 |  // SPI0_CSN
                         GPIO_PIN_B1 |  // SPI0_MOSI
                         GPIO_PIN_A7,   // SPI0_MISO
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for SPI3
 */
void spi3_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A2,   // SPI3_CLK
                        RM1_IO_SPI3_CLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A3,   // SPI3_CSN0
                        RM1_IO_SPI3_CSN);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A4,   // SPI3_MISO
                        RM1_IO_SPI3_MISO);

    HAL_PINCTRL_SetRMIO(GPIO_BANK4,
                        GPIO_PIN_A5,   // SPI3_MOSI
                        RM1_IO_SPI3_MOSI);
}

/**
 * @brief  Config iomux for UART0
 */
void uart0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B1,   // UART0_TX
                        RM2_IO_UART0_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B2,   // UART0_RX
                        RM2_IO_UART0_RX);
}

/**
 * @brief  Config iomux for UART2
 */
void uart2_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A6,   // UART2_RX
                        RM1_IO_UART2_RX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A7,   // UART2_TX
                        RM1_IO_UART2_TX);
}

/**
 * @brief  Config iomux for usb host
 */
void usb_host_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK5,
                         GPIO_PIN_B1,
                         PIN_CONFIG_MUX_FUNC0);

    HAL_PINCTRL_SetParam(GPIO_BANK5,
                         GPIO_PIN_B1, // HI-Z
                         PIN_CONFIG_PUL_NORMAL);

    HAL_GPIO_SetPinDirection(GPIO5, GPIO_PIN_B1, GPIO_OUT);
    HAL_GPIO_SetPinLevel(GPIO5, GPIO_PIN_B1, GPIO_HIGH);
}

/** @defgroup IOMUX_Public_Functions Public Functions
 *  @{
 */

void rt_hw_iomux_config(void)
{
    fspi0_iomux_config();
    i2c1_iomux_config();
    pwm0_iomux_config();
    sai1_iomux_config();
    sai2_iomux_config();
    sai3_iomux_config();
    sai4_iomux_config();
    spi0_iomux_config();
    spi3_iomux_config();
    uart0_iomux_config();
    uart2_iomux_config();
    usb_host_iomux_config();
}

/** @} */  // IOMUX_Public_Functions

/** @} */  // IOMUX

/** @} */  // RKBSP_Board_Driver
