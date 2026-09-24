/*
 * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-07     Cliff Chen   first implementation
 */

#ifndef __PCIE_VUART_EP_H__
#define __PCIE_VUART_EP_H__

int pcie_vuart_init(void *bar_addr, size_t bar_size);
int pcie_vuart_deinit(void);

#endif /* __PCIE_VUART_EP_H__ */
