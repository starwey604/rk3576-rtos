/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-19     Jason Zhu   first implementation
 */

#include <stdio.h>
#include <string.h>
#include <rtthread.h>
#include "board_base.h"

#ifndef RT_USING_USER_MAIN
void rtthread_startup(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init board */
    rt_hw_board_init();

    /* init timer system */
    rt_system_timer_init();

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return;
}
#endif

int main(void)
{
#ifndef RT_USING_USER_MAIN
    /* startup RT-Thread RTOS */
    rtthread_startup();
#else
    rt_kprintf("Hello RV1126B MCU\n");
#endif

    return 0;
}
