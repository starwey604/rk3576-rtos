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
                         GPIO_PIN_A4 |  // FSPI_CLK
                         GPIO_PIN_A5,   // FSPI_D2
                         PIN_CONFIG_MUX_FUNC1);
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

/** @defgroup IOMUX_Public_Functions Public Functions
 *  @{
 */

void rt_hw_iomux_config(void)
{
    fspi0_iomux_config();
    uart0_iomux_config();
}

/** @} */  // IOMUX_Public_Functions

/** @} */  // IOMUX

/** @} */  // RKBSP_Board_Driver
