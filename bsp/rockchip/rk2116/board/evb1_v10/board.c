/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-08     Jason Zhu    first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "cpuport.h"
#include "drv_clock.h"
#include "drv_uart.h"
#include "drv_cache.h"
#include "hal_base.h"
#include "hal_bsp.h"
#include "iomux.h"

#ifdef RT_USING_SDIO
#include "drv_sdio.h"
#include <drivers/mmcsd_core.h>
#endif

extern const struct clk_init clk_inits[];

#ifdef RT_USING_SDIO
struct rk_mmc_platform_data rk_mmc_table[] =
{
#ifdef RT_USING_SDIO0
    {
        .flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED,
        .irq = SDMMC_IRQn,
        .base = MMC_BASE,
        .clk_id = CCLK_SDMMC,
        .clk_gate = CCLK_SRC_SDMMC_GATE,
        .hclk_gate = HCLK_SDMMC_GATE,
        .freq_min = 100000,
        .freq_max = 50000000,
        .control_id = 0,
        .is_pwr_gpio = true, /* using gpio to control power */
        .pwr_gpio = GPIO0,
        .pwr_gpio_bank = GPIO_BANK0,
        .pwr_gpio_pin = GPIO_PIN_A3,
    },
#endif
    { /* sentinel */ },
};
#endif

#if defined(RT_USING_UART0)
const struct uart_board g_uart0_board =
{
    .baud_rate = UART_BR_1500000,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart0",
};
#endif /* RT_USING_UART0 */

/**
 * This function will initial Pisces board.
 */
void rt_hw_board_init()
{
    /* HAL_Init */
    HAL_Init();

    /* hal bsp init */
    BSP_Init();

    rt_memory_heap_init();
#ifdef RT_USING_PIN
    rt_hw_iomux_config();
#endif
    /* Initial usart deriver, and set console device */
    rt_hw_usart_init();

    clk_init(clk_inits, true);

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    rt_hw_ticksetup();
}
