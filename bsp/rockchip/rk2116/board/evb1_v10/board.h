/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-08     Jason Zhu    first implementation
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "board_base.h"

#ifdef RT_USING_CEC
#undef  CEC_HPD_IRQ_PIN
#define CEC_HPD_IRQ_PIN       BANK_PIN(GPIO_BANK0, 16)
#undef  CEC_I2C_DEV
#define CEC_I2C_DEV           "i2c3"
#endif

#endif
