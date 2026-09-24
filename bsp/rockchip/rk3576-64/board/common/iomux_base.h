/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-12     Steven Liu   first implementation
 */

#ifndef __IOMUX_BASE_H__
#define __IOMUX_BASE_H__

void dsmc_host_iomux_config(void);
void dsmc_host_lb_iomux_config(void);
void i2c0_m1_iomux_config(void);
void i2c1_m0_iomux_config(void);
void uart0_m0_iomux_config(void);
void uart5_m2_iomux_config(void);
void flexbus_adc_iomux_config(void);
void flexbus_dac_iomux_config(void);
void rt_hw_iomux_config(void);

#endif
