/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    core.h
  * @author  Zitong Cai
  * @version V0.1
  * @date    12-Mar-2025
  * @brief   serdes driver
  *
  ******************************************************************************
  */

#ifndef CORE_H
#define CORE_H

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "gpio.h"

//#define SERDES_DEBUG_MFD
//#define SERDES_DEBUG_I2C
//#define SERDES_DEBUG_CHIP

#ifdef SERDES_DEBUG_MFD
#define SERDES_DBG_MFD(x...) rt_kprintf(x)
#else
#define SERDES_DBG_MFD(x...)
#endif

#ifdef SERDES_DEBUG_I2C
#define SERDES_DBG_I2C(x...) rt_kprintf(x)
#else
#define SERDES_DBG_I2C(x...)
#endif

#ifdef SERDES_DEBUG_CHIP
#define SERDES_DBG_CHIP(x...) rt_kprintf(x)
#else
#define SERDES_DBG_CHIP(x...)
#endif

#define RT_I2C_ERROR_TIMES   3
#define RT_SERDES_DEV_MAX    20

#define BIT(nr)             (1 << (nr))
#define __bf_shf(x) (__builtin_ffsll(x) - 1)

#define FIELD_GET(_mask, _reg)                      \
    ({                              \
        (typeof(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask)); \
    })

#define RT_SERDES_PANEL_INIT    0
#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))

struct serdes_reg_config
{
    rt_uint16_t reg;
    rt_uint16_t def;
    rt_uint8_t mask;
};

struct rt_serdes_config
{
    rt_uint8_t reg_config_cnt;
    const struct serdes_reg_config *reg_config;
};

struct serdes_desc
{
    char *name;
    char *i2c_bus;
    rt_uint16_t i2c_addr;

    struct rt_serdes_config serdes_init_seq;
    struct rt_serdes_config serdes_init_iomux;
};

struct serdes_chip_data
{
    const char *name;
    enum serdes_id serdes_id;
    enum serdes_type serdes_type;
    const struct rt_serdes_chip_iomux_ops *iomux_ops;
    const struct rt_serdes_chip_bridge_ops *bridge_ops;
};

struct rt_serdes
{
    struct rt_device parent;
    char dev_name[RT_NAME_MAX];
    struct serdes_desc serdes_desc;
    struct serdes_chip_data chip_data;
    struct rt_i2c_client *serdes_client;
};
typedef struct rt_serdes *rt_serdes_t;

struct serdes_id_data
{
    const char *name;
    const struct serdes_chip_data *data;
};

struct rt_serdes_chip_iomux_ops
{
    rt_err_t (*set_mux)(rt_serdes_t serdes);
};

struct rt_serdes_chip_bridge_ops
{
    rt_bool_t (*detect)(rt_serdes_t serdes, rt_uint8_t link);
};

rt_err_t rt_serdes_register(rt_serdes_t serdes);
rt_err_t serdes_i2c_set_iomux(rt_serdes_t serdes);
rt_err_t serdes_i2c_set_sequence(rt_serdes_t serdes);
rt_serdes_t rt_serdes_match(const struct serdes_desc *serdes_desc);
rt_err_t serdes_reg_write(struct rt_i2c_client *serdes_client, rt_uint16_t reg, rt_uint8_t val);
rt_err_t serdes_reg_read(struct rt_i2c_client *serdes_client, rt_uint16_t reg, rt_uint8_t *val);
rt_err_t serdes_set_bits(struct rt_i2c_client *serdes_client,
                         rt_uint16_t reg, rt_uint8_t mask, rt_uint8_t val);

extern struct serdes_chip_data serdes_max96752_data;
extern struct serdes_chip_data serdes_max96789_data;
extern const struct serdes_desc rk_board_display_serdes[];
#endif
