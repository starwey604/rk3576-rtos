
#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <unistd.h>
#include <stdlib.h>
#include "hal_base.h"

static struct rt_i2c_bus_device *get_i2c_bus(int no)
{
    char name[8];
    snprintf(name, sizeof(name), "i2c%d", no);

    return rt_i2c_bus_device_find(name);
}

static int i2c_read(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr,
                    void *cmd_buf, size_t cmd_len,
                    void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[2];
    int ret;

    msgs[0].addr  = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = cmd_buf;
    msgs[0].len   = cmd_len;

    msgs[1].addr  = addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = data_buf;
    msgs[1].len   = data_len;

    ret = rt_i2c_transfer(i2c_bus, msgs, 2);
    if (ret != 2)
    {
        rt_kprintf("%s: 0x%x 0x%x failed: (%d)\n", __func__, addr,
                   *(rt_uint8_t *)cmd_buf, ret);

        return -RT_ERROR;
    }

    return RT_EOK;
}
static int i2c_write(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr,
                     void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[1];
    int ret;

    msgs[0].addr  = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = data_buf;
    msgs[0].len   = data_len;

    ret = rt_i2c_transfer(i2c_bus, msgs, 1);
    if (ret != 1)
    {
        rt_kprintf("%s: 0x%x 0x%x failed: (%d)\n", __func__, addr,
                   *(rt_uint8_t *)data_buf, ret);

        return -RT_ERROR;
    }

    return RT_EOK;
}

static void i2cset(uint8_t dev_id, uint8_t addr, uint8_t reg, uint8_t val)
{
    struct rt_i2c_bus_device *i2c_bus;
    rt_uint8_t cmd_buf[1];
    rt_uint8_t buf[256];



    i2c_bus = get_i2c_bus(dev_id);

    if (!i2c_bus)
    {
        rt_kprintf("Cannot get i2c-bus\n");
        return;
    }

    buf[0] = reg & 0xff;
    buf[1] = val & 0xff;

    i2c_write(i2c_bus, addr, buf, 2);
    cmd_buf[0] = buf[0];
    i2c_read(i2c_bus, addr, cmd_buf, 1, buf, 1);
    // rt_kprintf("R: %02x:%02x\n", cmd_buf[0], buf[0]);
}

static uint8_t i2cget(uint8_t dev_id, uint8_t addr, uint8_t reg)
{
    struct rt_i2c_bus_device *i2c_bus;
    rt_uint8_t cmd_buf[1];
    rt_uint8_t buf[1];

    i2c_bus = get_i2c_bus(dev_id);

    if (!i2c_bus)
    {
        rt_kprintf("Cannot get i2c-bus\n");
        return 1;
    }

    cmd_buf[0] = reg;
    i2c_read(i2c_bus, addr, cmd_buf, 1, buf, 1);
    return buf[0];
}

void forlinx_usage(void)
{
    rt_kprintf("usage: forlinx_i2c \n\n");

    rt_kprintf("example(set time) : forlinx_i2c -s 2025 03 11 14 30 00\n");
    rt_kprintf("example(get time) : forlinx_i2c -g\n");

}

void forlinx_i2c_test(int argc, char** argv)
{
    uint8_t index;
    uint8_t year, month, day, hour, min, sec;
    uint8_t low, high;

    if(argc > 1)
    {
        index = 1;
        if(!strcmp("-s", argv[index])){
            if(argc != 8){
                forlinx_usage();
                return;
            }
            index++;
            year = strtol(argv[index++], NULL, 10)%100;
            month = strtol(argv[index++], NULL, 10);
            day = strtol(argv[index++], NULL, 10);
            hour = strtol(argv[index++], NULL, 10);
            min = strtol(argv[index++], NULL, 10);
            sec = strtol(argv[index++], NULL, 10);
            printf("set date : %d-%d-%d %d:%d:%d\n", year, month, day, hour, min, sec);
            i2cset(7, 0x32, 0x16, year);
            i2cset(7, 0x32, 0x15, month);
            i2cset(7, 0x32, 0x14, day);
            i2cset(7, 0x32, 0x12, hour);
            low = min%10;
            high = min/10;
            min = (high<<4) | low;
            i2cset(7, 0x32, 0x11, min); //使用BCD码
            low = sec%10;
            high = sec/10;
            sec = (high<<4) | low;
            i2cset(7, 0x32, 0x10, sec); //使用BCD码
        }else if(!strcmp("-g", argv[index])){

            year = i2cget(7, 0x32, 0x16);
            month = i2cget(7, 0x32, 0x15);
            day = i2cget(7, 0x32, 0x14);
            hour = i2cget(7, 0x32, 0x12);
            min = i2cget(7, 0x32, 0x11);
            low = min & 0x0F;
            high = min>>4;
            min = high*10 + low;
            sec = i2cget(7, 0x32, 0x10);
            low = sec & 0x0F;
            high = sec>>4;
            sec = high*10 + low;
            printf("get date : %d-%d-%d %d:%d:%d\n", year, month, day, hour, min, sec);
        }else{
            printf("argc:%d\n", argc);
            forlinx_usage();
        }
    }else{
        forlinx_usage();
    }
}


MSH_CMD_EXPORT_ALIAS(forlinx_i2c_test, forlinx_i2c, RTC uses I2C2 test);


