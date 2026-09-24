/**
  * Copyright (c) 2024 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cec.h
  * @version V0.1
  * @brief   cec driver
  *
  * Change Logs:
  * Date           Author          Notes
  * 2024-08-21     Algea Cao   first implementation
  *
  ******************************************************************************
  */

#ifndef __DRV_CEC_H__
#define __DRV_CEC_H__

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include <rtdevice.h>
#include <rtthread.h>
#include "hal_base.h"

#ifndef CEC_HPD_IRQ_PIN
#define CEC_HPD_IRQ_PIN   0
#endif

#ifndef CEC_I2C_DEV
#define CEC_I2C_DEV   0
#endif

#define RK_CEC_CTRL_SET_LOGIC_ADDR      0x1000
#define RK_CEC_CTRL_GET_LOGIC_ADDR      0x1001
#define RK_CEC_CTRL_GET_PHY_ADDR        0x1002
#define RK_CEC_CTRL_SEND_MSG            0x1003
#define RK_CEC_CTRL_READ_MSG            0x1004
#define RK_CEC_CTRL_STANDBY             0x1005
#define RK_CEC_CTRL_SET_EVENT           0x1006

#endif /* __DRV_CEC_H__ */
