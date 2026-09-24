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
#include "drv_clock.h"
#include "drv_uart.h"
#include "drv_cache.h"
#include "drv_heap.h"
#include "drv_otp.h"
#include "drv_thermal.h"
#include "hal_base.h"
#include "hal_bsp.h"
#include "iomux.h"

#if defined(RT_USING_USB_DEVICE)
#include "drv_usbd.h"
#endif

extern const rt_uint32_t __heap_start[];
extern const rt_uint32_t __heap_limit[];

void rt_memory_heap_init(void)
{
    rt_system_heap_init((void *)__heap_start, (void *)__heap_limit);
}

extern const struct clk_init clk_inits[];

#if defined(RT_USING_OTP)
RT_WEAK const struct otp_data g_otp_data =
{
    .reg = OTPC,
    .size = 0x78,
    .nbytes = 0x2,
    .ns_offset = 0x1c0,
};
#endif /* RT_USING_OTP */

#if defined(RT_USING_TSADC)
RT_WEAK const struct tsadc_init g_tsadc_init =
{
    .chn_id = {0},
    .chn_num = 1,
    .polarity = TSHUT_LOW_ACTIVE,
    .mode = TSHUT_MODE_CRU,
    .otp_offset = {32},
    .otp_mask = 0x3ff,
};
#endif /* RT_USING_TSADC */

#if defined(RT_USING_UART0)
RT_WEAK const struct uart_board g_uart0_board =
{
    .baud_rate = UART_BR_1500000,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart0",
};
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
RT_WEAK const struct uart_board g_uart1_board =
{
    .baud_rate = UART_BR_1500000,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart1",
};
#endif /* RT_USING_UART1 */

#if defined(RT_USING_USB_DEVICE)
RT_WEAK struct ep_id g_usb_ep_pool[] =
{
    { 0x0,  USB_EP_ATTR_CONTROL,    USB_DIR_INOUT,  64,   ID_ASSIGNED   },
    { 0x1,  USB_EP_ATTR_BULK,       USB_DIR_IN,     1024, ID_UNASSIGNED },
    { 0x2,  USB_EP_ATTR_BULK,       USB_DIR_OUT,    512,  ID_UNASSIGNED },
    { 0x3,  USB_EP_ATTR_ISOC,       USB_DIR_IN,     1024, ID_UNASSIGNED },
    { 0x4,  USB_EP_ATTR_ISOC,       USB_DIR_OUT,    1024,  ID_UNASSIGNED },
    { 0x5,  USB_EP_ATTR_INT,        USB_DIR_IN,     64,   ID_UNASSIGNED },
    { 0x6,  USB_EP_ATTR_INT,        USB_DIR_OUT,    64,   ID_UNASSIGNED },
    { 0xFF, USB_EP_ATTR_TYPE_MASK,  USB_DIR_MASK,   0,    ID_ASSIGNED   },
};
#endif /* RT_USING_USB_DEVICE */

/**
 * This function will initial Pisces board.
 */
RT_WEAK void rt_hw_board_init()
{
    /* HAL_Init */
    HAL_Init();

    /* hal bsp init */
    BSP_Init();

    /* System tick init */

#ifdef RT_USING_PIN
    rt_hw_iomux_config();
#endif

    rt_memory_heap_init();
    /* Initial usart deriver, and set console device */
    rt_hw_usart_init();

    clk_init(clk_inits, true);

    /* Update system core clock after clk_init */
    SystemCoreClockUpdate();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
