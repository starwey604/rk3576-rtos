/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd
 */

/**
 * @file  hal_conf_template.h
 */

#ifndef _HAL_CONF_H_
#define _HAL_CONF_H_

#include "rtconfig.h"

#define HAL_MCU_CORE
#define __RISC_V
#define SYS_TIMER TIMER0 /* System timer designation (RK TIMER) */

#ifdef SMODE_RTOS
#define SMP_CPU_CNT 1
#define RISCV_SMODE
#endif

#ifdef RT_USING_CACHE
#define HAL_DCACHE_MODULE_ENABLED
#define HAL_ICACHE_MODULE_ENABLED
#endif

#ifdef RT_USING_CAN
#define HAL_CANFD_MODULE_ENABLED
#endif

#ifdef RT_USING_CEC
#define HAL_CEC_MODULE_ENABLED
#endif

#ifdef RT_USING_CRU
#define HAL_CRU_MODULE_ENABLED
#endif

#ifdef RT_USING_FLEXBUS
#define HAL_FLEXBUS_MODULE_ENABLED
#endif

#ifdef RT_USING_FLEXBUS_ADC
#define HAL_FLEXBUS_ADC_MODULE_ENABLED
#endif

#ifdef RT_USING_FLEXBUS_DAC
#define HAL_FLEXBUS_DAC_MODULE_ENABLED
#endif

#ifdef RT_USING_GMAC
#define HAL_GMAC_MODULE_ENABLED
#ifdef RT_USING_GMAC_PTP
#define HAL_GMAC_PTP_FEATURE_ENABLED
#endif
#endif

#ifdef RT_USING_I2C
#define HAL_I2C_MODULE_ENABLED
#endif

#ifdef RT_USING_NPOR
#define HAL_NPOR_MODULE_ENABLED
#endif

#ifdef RT_USING_OTP
#define HAL_OTP_MODULE_ENABLED
#endif

#ifdef RT_USING_PDM
#define HAL_PDM_MODULE_ENABLED
#endif

#ifdef RT_USING_PIN
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PINCTRL_MODULE_ENABLED
#endif

#ifdef RT_USING_PWM
#define HAL_PWM_MODULE_ENABLED
#endif

#ifdef RT_HWCRYPTO_USING_RNG
#define HAL_TRNG_MODULE_ENABLED
#endif

#ifdef RT_USING_SAI
#define HAL_SAI_MODULE_ENABLED
#endif

#ifdef RT_USING_SARADC
#define HAL_SARADC_MODULE_ENABLED
#endif

#ifdef RT_USING_SDIO
#define HAL_SDIO_MODULE_ENABLED
#endif

#ifdef RT_USING_SNOR
#define HAL_SNOR_MODULE_ENABLED
#define HAL_SNOR_FSPI_HOST
#define HAL_FSPI_MODULE_ENABLED
#define HAL_FSPI_DMA_ENABLED
#ifdef RT_USING_XIP
#define HAL_FSPI_XIP_ENABLE
#define HAL_SRAM_SECTION_ENABLED
#endif
#endif

#ifdef RT_USING_SPDIFRX
#define HAL_SPDIFRX_MODULE_ENABLED
#endif

#ifdef RT_USING_SPDIFTX
#define HAL_SPDIFTX_MODULE_ENABLED
#endif

#ifdef RT_USING_SPI
#define HAL_SPI_MODULE_ENABLED
#ifdef RT_USING_SPI_SLAVE_FLEXIBLE_LENGTH
#define HAL_SPI_SLAVE_FLEXIBLE_LENGTH_ENABLED
#endif
#endif

#ifdef RT_USING_SPINAND
#define HAL_SPINAND_MODULE_ENABLED
#ifdef RT_USING_SPINAND_FSPI_HOST
#define HAL_FSPI_MODULE_ENABLED
#endif
#endif

#ifdef RT_USING_SPI2APB
#define HAL_SPI2APB_MODULE_ENABLED
#endif

#ifdef RT_USING_TSADC
#define HAL_TSADC_MODULE_ENABLED
#endif

#ifdef RT_USING_UART
#define HAL_UART_MODULE_ENABLED
#endif

#ifdef RT_USING_USB_DEVICE
#define HAL_PCD_MODULE_ENABLED
#define USB_PHY_BCD_DETECT
#endif

#ifdef RT_USING_USB_HOST
#define HAL_HCD_MODULE_ENABLED
#endif

#ifdef RT_USING_VOP
#define HAL_VOP_MODULE_ENABLED
#endif

#define HAL_DBG_USING_RTT_SERIAL 1   /* redirect the hal log to rtt console */
#define HAL_HWSPINLOCK_MODULE_ENABLED
#define HAL_SPINLOCK_MODULE_ENABLED
#define HAL_TIMER_MODULE_ENABLED

#endif /* _HAL_CONF_H_ */
