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
 * @brief  Config iomux for CEC
 */
void cec_iomux_config(void)
{
    WRITE_REG_MASK_WE(PERIA_GRF->SOC_CON10,
                      PERIA_GRF_SOC_CON10_I2C3_SEL_MASK,
                      (0x1 << PERIA_GRF_SOC_CON10_I2C3_SEL_SHIFT));


    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B3 |  // HDMI_I2C_SCL
                         GPIO_PIN_B4 |  // HDMI_I2C_SDA
                         GPIO_PIN_B7 |  // HDMI_CEC
                         GPIO_PIN_C0,   // HDMI_HPD
                         PIN_CONFIG_MUX_FUNC1);
}

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
                         GPIO_PIN_A4 |  // FSPI_CLK
                         GPIO_PIN_A5,   // FSPI_D2
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for I2C1
 */
void i2c1_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_A6,   // I2C1_SCL,
                        RM0_IO_I2C1_SCL);

    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_A7,   // I2C1_SDA
                        RM0_IO_I2C1_SDA);
}

/**
 * @brief  Config iomux for opt PDM
 */
void pdm_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_B2,        //PDM_CLK
                        RM2_IO_PDM_CLK0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK2,
                        GPIO_PIN_B3,        // PDM_SDI0
                        RM2_IO_PDM_SDI0);
}

/**
 * @brief  Config iomux for pwm0
 */
void pwm0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A5,   // PWM0_0
                        RM0_IO_PWM0_CH0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B0,   // PWM0_3 IR
                        RM0_IO_PWM0_CH3);
}

/**
 * @brief  Config iomux for RMII
 */
void rmii_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B0 |  // ETH_RMII_RXD0
                         GPIO_PIN_B1 |  // ETH_RMII_RXD1
                         GPIO_PIN_B2 |  // ETH_RMII_CLK
                         GPIO_PIN_B3 |  // ETH_RMII_TXD0
                         GPIO_PIN_B4 |  // ETH_RMII_TXD1
                         GPIO_PIN_B5 |  // ETH_RMII_TXEN
                         GPIO_PIN_B6 |  // ETH_RMII_MDC
                         GPIO_PIN_B7 |  // ETH_RMII_MDIO
                         GPIO_PIN_C0,   // ETH_RMII_CRSDV
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for SAI0
 */
void sai0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A0,   // SAI0_SCLK
                        RM2_IO_SAI0_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A1,   // SAI0_LRCK
                        RM2_IO_SAI0_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A2,   // SAI0_SDO0
                        RM2_IO_SAI0_SDO0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A3,   // SAI0_SDO1
                        RM2_IO_SAI0_SDO1);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A4,   // SAI0_SDO2
                        RM2_IO_SAI0_SDO2);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A5,   // SAI0_SDO3
                        RM2_IO_SAI0_SDO3);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_A6,   // SAI0_SDI0
                        RM2_IO_SAI0_SDI0);
}

/**
 * @brief  Config iomux for SAI1
 */
void sai1_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A6,   // SAI1_SCLK
                        RM2_IO_SAI1_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_A7,   // SAI1_LRCK
                        RM2_IO_SAI1_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B0,   // SAI1_SDI0
                        RM2_IO_SAI1_SDI0);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B1,   // SAI1_SDI1
                        RM2_IO_SAI1_SDI1);
}

/**
 * @brief  Config iomux for SAI4
 */
void sai4_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B5,   // SAI4_MCLK
                        RM2_IO_MCLK4);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B6,   // SAI4_SCLK
                        RM2_IO_SAI4_SCLK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_B7,   // SAI4_LRCK
                        RM2_IO_SAI4_LRCK);

    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_C0,   // SAI4_SDI0
                        RM2_IO_SAI4_SDI);
}

/**
 * @brief  Config iomux for SAI5
 */
void sai5_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK5,
                        GPIO_PIN_C1,   // SAI5_SDI0
                        RM2_IO_SAI5_SDI);
}

/**
 * @brief  Config iomux for sdmmc
 */
void sdmmc_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_A0 |  // SDMMC_CLK
                         GPIO_PIN_A1 |  // SDMMC_CMD
                         GPIO_PIN_A2 |  // SDMMC_D0
                         GPIO_PIN_A3 |  // SDMMC_D1
                         GPIO_PIN_A4 |  // SDMMC_D2
                         GPIO_PIN_A5,   // SDMMC_D3
                         PIN_CONFIG_MUX_FUNC1);

    HAL_PINCTRL_SetParam(GPIO_BANK2,
                         GPIO_PIN_A1 |   // SDMMC_CMD
                         GPIO_PIN_A2 |   // SDMMC_D0
                         GPIO_PIN_A3 |   // SDMMC_D1
                         GPIO_PIN_A4 |   // SDMMC_D2
                         GPIO_PIN_A5,    // SDMMC_D3
                         PIN_CONFIG_PUL_UP);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A0,   // SDMMC_DET_L
                         PIN_CONFIG_MUX_FUNC1);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A3,   // SD_PWREN_H GPIO
                         PIN_CONFIG_MUX_FUNC0);
}

/**
 * @brief  Config iomux for arc SPDIF_RX
 */
void spdif_rx_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A5,   // SPDIF_RX
                        RM2_IO_SPDIF_RX);
}

/**
 * @brief  Config iomux for SPDIF_TX
 */
void spdif_tx_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK3,
                        GPIO_PIN_A4,   // SPDIF_TX
                        RM2_IO_SPDIF_TX);
}

/**
 * @brief  Config iomux for UART0
 */
void uart0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B1,   // UART0_TX_M0
                        RM2_IO_UART0_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B2,   // UART0_RX_M0
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
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A6,
                         PIN_CONFIG_MUX_FUNC0);

    HAL_PINCTRL_SetParam(GPIO_BANK0,
                         GPIO_PIN_A6, // HI-Z
                         PIN_CONFIG_PUL_NORMAL);

    HAL_GPIO_SetPinDirection(GPIO0, GPIO_PIN_A6, GPIO_OUT);
    HAL_GPIO_SetPinLevel(GPIO0, GPIO_PIN_A6, GPIO_HIGH);
}

/** @defgroup IOMUX_Public_Functions Public Functions
 *  @{
 */

void rt_hw_iomux_config(void)
{
    cec_iomux_config();
    fspi0_iomux_config();
    i2c1_iomux_config();
    pdm_iomux_config();
    pwm0_iomux_config();
    rmii_iomux_config();
    sai0_iomux_config();
    sai1_iomux_config();
    sai4_iomux_config();
    sai5_iomux_config();
    sdmmc_iomux_config();
    spdif_rx_iomux_config();
    spdif_tx_iomux_config();
    uart0_iomux_config();
    uart2_iomux_config();
    usb_host_iomux_config();
}

/** @} */  // IOMUX_Public_Functions

/** @} */  // IOMUX

/** @} */  // RKBSP_Board_Driver
