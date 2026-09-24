/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    board.h
  * @author  Tom Song
  * @version V0.1
  * @date    24-Jan-2025
  * @brief
  *
  ******************************************************************************
  */

#ifndef __BOARD_H__
#define __BOARD_H__

#define NCA9539_I2C_BUS_NAME           "i2c7"

#define SPI_INFORM_SLAVE_PIN           BANK_PIN(GPIO_BANK0, 20)    //GPIO0_C4
#define PRESENCE_CHECK_PIN             BANK_PIN(GPIO_BANK2, 16)    //GPIO2_C0

#endif
