#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>
#include <stdlib.h>
#include "hal_base.h"

#define DBG_TAG "adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>


static int forlinx_adc(int argc, char **argv)
{
    int value = 0, count = 0;
    static rt_adc_device_t adc_device = RT_NULL;
    char *result_str;

    if (argc > 1)
    {
        if (!strcmp(argv[1], "probe"))
        {
            adc_device = (rt_adc_device_t)rt_device_find("rk_adc0");
            result_str = (adc_device == RT_NULL) ? "failure" : "success";
            rt_kprintf("probe rk_adc0 %s \n", result_str);
        }
        else if (!strcmp(argv[1], "read"))
        {
            if (argc == 3)
            {
                while(1)
                {
                    value = rt_adc_read(adc_device, atoi(argv[2]));
                    rt_kprintf("%s channel %d  read value is %04d \n", adc_device->parent.parent.name, atoi(argv[2]), value);
                    HAL_DelayMs(100);
                    if(++count > 4)
                        break;
                }
            }
            else
            {
                rt_kprintf("adc read <channel>     - read adc value on the channel\n");
            }
        }
        else
        {
            rt_kprintf("Unknown command. Please enter 'adc' for help\n");
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("forlinx_adc probe               - probe adc by name\n");
        rt_kprintf("forlinx_adc read <channel>      - read adc value on the channel\n");
        return RT_ERROR;
    }
    return RT_EOK;
}

MSH_CMD_EXPORT(forlinx_adc, forlinx adc test);

