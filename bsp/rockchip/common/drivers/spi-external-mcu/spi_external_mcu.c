/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-24     tom.song     the first version
 */

#include "spi_external_mcu.h"

static struct rt_spi_device *SpiSlave;
static struct rt_device_spi *spi_ext;

static unsigned char GetChkSum_CRC8(unsigned char *dptr, unsigned short len)
{
    unsigned char  crc = 0;
    unsigned short i;
    for (i = 0; i < len; i++)
    {
        crc ^= dptr[i];
    }
    return crc;
}

int get_buff_pwrctrl(unsigned char *buff, unsigned char cmd, unsigned char value)
{
    if (!buff)
        return RT_ERROR;
    buff[0] = DATE_SOC_SET;
    buff[1] = POWER_DATA_LEN;
    buff[2] = cmd;
    buff[3] = value;
    buff[ POWER_DATA_LEN - 1 ] = GetChkSum_CRC8(buff, POWER_DATA_LEN - 1);
    return RT_EOK;
}

static void SpiSlaveHardwareConfiguration(struct rt_spi_device *spiDev)
{
    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_SLAVE | RT_SPI_LSB;

    cfg.max_hz = 9 * 1000 * 1000;
    if (rt_spi_configure(spiDev, &cfg) != RT_EOK)
    {
        rt_kprintf("Slave spi configure fail.\n");
    }
}

static void slave_gpioInit(void)
{
    rt_pin_mode(SPI_INFORM_SLAVE_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(SPI_INFORM_SLAVE_PIN, PIN_HIGH);
    rt_pin_mode(PRESENCE_CHECK_PIN, PIN_MODE_INPUT);
}

static rt_size_t _spidev_device_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   size)
{
    struct rt_device_spi *device;

    device = (struct rt_device_spi *)dev;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->spi != RT_NULL);

    return rt_spi_transfer(device->spi, RT_NULL, buffer, size);
}

static rt_size_t _spidev_device_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   size)
{
    struct rt_device_spi *device;
    rt_size_t ret;

    device = (struct rt_device_spi *)dev;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->spi != RT_NULL);
    rt_pin_write(SPI_INFORM_SLAVE_PIN, PIN_LOW);
    ret = rt_spi_transfer(device->spi, buffer, RT_NULL, size);
    rt_thread_mdelay(1);
    rt_pin_write(SPI_INFORM_SLAVE_PIN, PIN_HIGH);
    return ret;
}

static const struct rt_spi_ext_ops ext_ops =
{
    .write = _spidev_device_write,
    .read  = _spidev_device_read,
};

static rt_err_t rt_spidev_device_init(struct rt_device_spi *dev, const char *name)
{
    struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);
    device = &(dev->parent);

    device->type    = RT_Device_Class_SPIDevice;

#ifdef RT_USING_DEVICE_OPS
    device->ops     = &ext_ops;
#else
    device->init    = RT_NULL;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = _spidev_device_read;
    device->write   = _spidev_device_write;
    device->control = RT_NULL;
#endif

    dev->ops        = &ext_ops;
    dev->spi        = SpiSlave;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}

static int spi_extmcu_init(void)
{
    int ret = RT_EOK;

    SpiSlave = (struct rt_spi_device *)rt_device_find(Slave_SPI_DEVICE_NAME);
    if (!SpiSlave)
    {
        rt_kprintf("spi can't find %s device!\n", Slave_SPI_DEVICE_NAME);
        return RT_ERROR;
    }
    else
    {
        SpiSlaveHardwareConfiguration(SpiSlave);
    }

    slave_gpioInit();

    if (rt_pin_read(PRESENCE_CHECK_PIN) != PIN_HIGH)
    {
        return RT_ERROR;
    }

    spi_ext = (struct rt_device_spi *)rt_calloc(1, sizeof(struct rt_device_spi));
    if (!spi_ext)
    {
        rt_kprintf("rt_calloc spi_ext fail!\n");
        return RT_ERROR;
    }

    spi_ext->ops = &ext_ops;

    rt_spidev_device_init(spi_ext, Slave_SPI_EXTMCU_NAME);

    return ret;
}
INIT_DEVICE_EXPORT(spi_extmcu_init);