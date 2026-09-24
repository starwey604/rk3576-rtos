/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-08     Jason Zhu    first implementation
 */

#ifndef __BOARD_IOMUX_BASE_H__
#define __BOARD_IOMUX_BASE_H__

void fspi0_iomux_config(void);
void i2c1_iomux_config(void);
void pdm_iomux_config(void);
void pwm0_iomux_config(void);
void rmii_iomux_config(void);
void sai0_iomux_config(void);
void sai1_iomux_config(void);
void sai4_iomux_config(void);
void sdmmc_iomux_config(void);
void spdif_rx_iomux_config(void);
void spdif_tx_iomux_config(void);
void uart0_iomux_config(void);
void usb_host_iomux_config(void);
void rt_hw_iomux_config(void);

#endif
