/**
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: Cerf Yu <cerf.yu@rock-chips.com>
 */

#ifndef __RTT_ADAPTER_LINUX_BITOPS_H__
#define __RTT_ADAPTER_LINUX_BITOPS_H__

#if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 1, 0))

#include <rtatomic.h>

#define RGA_ATOMIC_OP(name, addr, bit) rt_atomic_##name((volatile unsigned long *)(addr), (bit))
#define RGA_ATOMIC_LOAD(addr) rt_atomic_load((addr))

#else

#ifdef __ARM_ARCH_6M__

#include <rthw.h>

/*
 *   Because cortex-M0 unsupport atomic, atomic operation is simulated by
 * turning interrupts on/off in software.
 */
static inline unsigned long rga_soft_atomic_or(volatile unsigned long *ptr, unsigned long val)
{
    rt_base_t level;
    unsigned long temp;

    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = (*ptr) | val;
    rt_hw_interrupt_enable(level);

    return temp;
}

static inline unsigned long rga_soft_atomic_xor(volatile unsigned long *ptr, unsigned long val)
{
    rt_base_t level;
    unsigned long temp;

    level = rt_hw_interrupt_disable();
    temp = *ptr;
    *ptr = (*ptr) ^ val;
    rt_hw_interrupt_enable(level);

    return temp;
}

static inline unsigned long rga_soft_atomic_load(volatile unsigned long *ptr)
{
    rt_base_t level;
    unsigned long temp;

    level = rt_hw_interrupt_disable();
    temp = *ptr;
    rt_hw_interrupt_enable(level);

    return temp;
}

#define RGA_ATOMIC_OP(name, addr, bit) rga_soft_atomic_##name((addr), (bit))
#define RGA_ATOMIC_LOAD(addr) rga_soft_atomic_load((addr))

#else

#include <stdatomic.h>

#define RGA_ATOMIC_OP(name, addr, bit) atomic_fetch_##name((addr), (bit))
#define RGA_ATOMIC_LOAD(addr) atomic_load((addr))

#endif /* #ifdef __ARM_ARCH_6M__ */

#endif /* #if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 1, 0)) */

#define BIT(nr)             (1UL << (nr))

static inline void set_bit(unsigned long bit, volatile unsigned long *addr)
{
    RGA_ATOMIC_OP( or, addr, BIT(bit));
}

static inline void clear_bit(unsigned long bit, volatile unsigned long *addr)
{
    RGA_ATOMIC_OP( or, addr, ~BIT(bit));
}

static inline void change_bit(unsigned long bit, volatile unsigned long *addr)
{
    RGA_ATOMIC_OP(xor, addr, BIT(bit));
}

static inline int test_bit(unsigned long bit, volatile unsigned long *addr)
{
    return RGA_ATOMIC_LOAD(addr) & BIT(bit);
}

static inline int test_and_set_bit(unsigned long bit, volatile unsigned long *addr)
{
    return RGA_ATOMIC_OP( or, addr, BIT(bit)) & BIT(bit);
}

static inline int test_and_clear_bit(volatile unsigned long bit, volatile unsigned long *addr)
{
    return RGA_ATOMIC_OP( or, addr, ~BIT(bit)) & BIT(bit);
}

#endif /* #ifndef __RTT_ADAPTER_LINUX_BITOPS_H__ */
