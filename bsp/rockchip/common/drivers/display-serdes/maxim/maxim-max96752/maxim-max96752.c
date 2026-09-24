/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    maxim-max96752.c
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#include "maxim-max96752.h"

static rt_err_t max96752_set_pin_mux(rt_serdes_t serdes)
{
    SERDES_DBG_CHIP("%s start set pin mux\n", serdes->dev_name);

    serdes_i2c_set_iomux(serdes);
}

static struct rt_serdes_chip_iomux_ops max96752_iomux_ops =
{
    .set_mux = max96752_set_pin_mux,
};

struct serdes_chip_data serdes_max96752_data =
{
    .name       = "max96752",
    .serdes_type    = TYPE_DES,
    .serdes_id = MAXIM_ID_MAX96752,
    .iomux_ops  = &max96752_iomux_ops,
};
