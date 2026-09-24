/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    gpio.h
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#ifndef __SERDES_DISPLAY_GPIO_H__
#define __SERDES_DISPLAY_GPIO_H__

enum serdes_type
{
    TYPE_ID_INVALID = 0,
    TYPE_SER,
    TYPE_DES,
    TYPE_OTHER,
};

enum serdes_id
{
    SERDES_ID_INVALID = 0,

    MAXIM_ID_MAX96745,
    MAXIM_ID_MAX96752,
    MAXIM_ID_MAX96755,
    MAXIM_ID_MAX96772,
    MAXIM_ID_MAX96789,

    SERDES_NUM_ID,
};

enum link_mode
{
    DUAL_LINK = 0,
    LINKA,
    LINKB,
    SPLITTER_MODE,
};

#endif
