/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    board_serdes_maxim.h
  * @author  Zitong Cai
  * @version V0.1
  * @date    31-Mar-2025
  * @brief
  *
  ******************************************************************************
  */

#ifndef __BOARD_SERDES_MAXIM_H__
#define __BOARD_SERDES_MAXIM_H__

#include "core.h"

static const struct serdes_reg_config max96789_sequence_config[] =
{
    //Independent 11_07_17-56 Using MAX96789/91/F (GMSL-1/2)
    //Disable Video pipe
    {0x02, 0x03},
    //Address Value of I2C SRC_A
    {0x42, 0x8a},
    //Address Value of I2C DST_A
    {0x43, 0x8a},
    //Address Value of I2C SRC_B
    {0x44, 0x8c},
    //Address Value of I2C DST_B
    {0x45, 0x8c},
    //Set Stream for DSI Port A && assign pipeX
    {0x53, 0x10},
    //Set Stream for DSI Port B && assign pipeY
    {0x57, 0x21},
    //Clock Select, X for portA, Y/Z for PortB
    {0x308, 0x76},
    //Start DSI-A Port
    {0x311, 0x01},
    //Set Port A Lane Mapping
    {0x332, 0x4E},
    //Set Port B Lane Mapping
    {0x333, 0xE4},
    //Set GMSL type
    {0x04, 0xF2},
    //Number of Lanes
    {0x331, 0x33},
    //Set phy_config
    {0x330, 0x06},
    //Set soft_dtx_en
    {0x31C, 0x98},
    //Set soft_dtx
    {0x321, 0x24},
    //Set soft_dty_en
    {0x31D, 0x98},
    //Set soft_dty_
    {0x322, 0x24},
    //Init Default
    {0x326, 0xE4},
    //HSYNC_WIDTH_L
    {0x385, 0x38},
    //VSYNC_WIDTH_L
    {0x386, 0x08},
    //HSYNC_WIDTH_H/VSYNC_WIDTH_H
    {0x387, 0x00},
    //VFP_L
    {0x3A5, 0xC8},
    //VBP_H
    {0x3A7, 0x00},
    //VFP_H/VBP_L
    {0x3A6, 0x20},
    //VRES_L
    {0x3A8, 0xD0},
    //VRES_H
    {0x3A9, 0x02},
    //HFP_L
    {0x3AA, 0x38},
    //HBP_H
    {0x3AC, 0x02},
    //HFP_H/HBP_L
    {0x3AB, 0x00},
    //HRES_L
    {0x3AD, 0x80},
    //HRES_H
    {0x3AE, 0x07},
    //Disable FIFO/DESKEW_EN
    {0x3A4, 0xC0},
    //HSYNC_WIDTH_L
    {0x395, 0x38},
    //VSYNC_WIDTH_L
    {0x396, 0x08},
    //HSYNC_WIDTH_H/VSYNC_WIDTH_H
    {0x397, 0x00},
    //VFP_L
    {0x3B1, 0xC8},
    //VBP_H
    {0x3B3, 0x00},
    //VFP_H/VBP_L
    {0x3B2, 0x20},
    //VRES_L
    {0x3B4, 0xD0},
    //VRES_H
    {0x3B5, 0x02},
    //HFP_L
    {0x3B6, 0x38},
    //HBP_H
    {0x3B8, 0x02},
    //HFP_H/HBP_L
    {0x3B7, 0x00},
    //HRES_L
    {0x3B9, 0x80},
    //HRES_H
    {0x3BA, 0x07},
    //Disable FIFO/DESKEW_EN
    {0x3B0, 0xC0},
    //Turn on video pipe
    {0x02, 0x33},
    //Enable splitter mode  reset one shot
    {0x10, 0x21},
    {0xffff, 0x4b}//delay
};

static const struct serdes_reg_config max96789_iomux_config[] =
{
    {0x2d3, 0x03, 0x07},
    {0x2d4, 0x04, 0x1f},
    {0x2d6, 0x04, 0x07},
    {0x2d8, 0x08, 0x1f},
    {0x2ee, 0x03, 0x07},
    {0x2ef, 0x09, 0x1f},
    {0x2e8, 0x04, 0x07},
    {0x2ea, 0x0e, 0x1f}
};

static const struct serdes_reg_config max96752_sequence_config[] =
{
    /*max96752 dual oLDI output*/
    {0x02, 0x43},
    {0x73, 0x31},
    {0x7b, 0x31},
    {0x7d, 0x38},
    //Address Value of I2C SRC_A
    {0x42, 0x8a},
    //Address Value of I2C DST_A
    {0x43, 0x90},
    {0x50, 0x00},
    {0x1ce, 0x4e},
    {0x1ea, 0x04},
};

static const struct serdes_reg_config max96752_iomux_config[] =
{
    {0x21e, 0x10, 0x17},
    {0x20f, 0x10, 0x17},
    {0x215, 0x10, 0x17},
    {0x212, 0x10, 0x17},
    {0x206, 0x03, 0x17},
    {0x207, 0x08, 0x1f},
    {0xffff, 0x46, 0x00},//delay
    {0x209, 0x10, 0x17},
    {0x20c, 0x04, 0x17},
    {0x20e, 0x04, 0x1f}
};

const struct serdes_desc rk_board_display_serdes[] =
{
    {
        .name = "max96789",
        .i2c_bus = "i2c8",
        .i2c_addr = 0x42,
        .serdes_init_seq = {
            .reg_config = max96789_sequence_config,
            .reg_config_cnt = ARRAY_SIZE(max96789_sequence_config),
        },
        .serdes_init_iomux = {
            .reg_config = max96789_iomux_config,
            .reg_config_cnt = ARRAY_SIZE(max96789_iomux_config),
        },
    },

    {
        .name = "max96752",
        .i2c_bus = "i2c8",
        .i2c_addr = 0x4a,
        .serdes_init_seq = {
            .reg_config = max96752_sequence_config,
            .reg_config_cnt = ARRAY_SIZE(max96752_sequence_config),
        },
        .serdes_init_iomux = {
            .reg_config = max96752_iomux_config,
            .reg_config_cnt = ARRAY_SIZE(max96752_iomux_config),
        },
    },
    { /* sentinel */ }
};

#endif
