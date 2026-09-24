/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-24     tom.song     the first version
 */

#ifndef __SPI_EXTERNAL_MCU_H_
#define __SPI_EXTERNAL_MCU_H_
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdlib.h>
#include "hal_base.h"
#include "board.h"

#if defined(RT_USING_SPI1)
#define Slave_SPI_DEVICE_NAME   "spi1_0"
#define Slave_BSU_NAME   "spi1"
#elif defined(RT_USING_SPI2)
#define Slave_SPI_DEVICE_NAME   "spi2_0"
#define Slave_BSU_NAME   "spi2"
#elif defined(RT_USING_SPI3)
#define Slave_SPI_DEVICE_NAME   "spi3_0"
#define Slave_BSU_NAME   "spi3"
#elif defined(RT_USING_SPI4)
#define Slave_SPI_DEVICE_NAME   "spi4_0"
#define Slave_BSU_NAME   "spi4"
#else
#define Slave_SPI_DEVICE_NAME   "spi1_0"
#define Slave_BSU_NAME   "spi1"
#endif

#define Slave_SPI_EXTMCU_NAME   "spi_extmcu"

#ifndef SPI_INFORM_SLAVE_PIN
#define SPI_INFORM_SLAVE_PIN   BANK_PIN(GPIO_BANK0, 20)
#endif

#ifndef PRESENCE_CHECK_PIN
#define PRESENCE_CHECK_PIN     BANK_PIN(GPIO_BANK2, 16)
#endif

#define DATE_SOC_SET        0x91
#define DATE_SOC_GET        0x90
#define DATE_MCU            0x80
#define POWER_DATA_LEN      0x5

struct rt_device_spi
{
    struct rt_device parent;
    const struct rt_spi_ext_ops *ops;
    struct rt_spi_device *spi;
};

struct rt_spi_ext_ops
{
    rt_size_t (*write)(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_size_t (*read)(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
};

int get_buff_pwrctrl(unsigned char *buff, unsigned char cmd, unsigned char value);
#endif
