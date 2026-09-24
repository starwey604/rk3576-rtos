
#include <rtdevice.h>
#include <string.h>

static int forlinx_pwm_test(int argc, char **argv)
{
    rt_err_t result = -RT_ERROR;
    char *result_str;
    static struct rt_device_pwm *pwm_device = RT_NULL;
    // struct rt_pwm_configuration cfg = {0};

    if(argc > 1)
    {
        if(!strcmp(argv[1], "probe"))
        {
            if(argc == 3)
            {
                pwm_device = (struct rt_device_pwm *)rt_device_find(argv[2]);
                result_str = (pwm_device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s\n", argv[2], result_str);
            }
            else
            {
                rt_kprintf("forlinx_pwm_test probe <device name>                  - probe pwm by name\n");
                rt_kprintf("    e.g. MSH >forlinx_pwm_test enable  pwm1              - PWM1  nomal\n");
            }
        }
        else
        {
            if(pwm_device == RT_NULL)
            {
                rt_kprintf("Please using 'forlinx_pwm_test probe <device name>' first.\n");
                return -RT_ERROR;
            }
            if(!strcmp(argv[1], "enable"))
            {
                if(argc == 3)
                {
                    result = rt_pwm_enable(pwm_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d is enabled %s \n", pwm_device->parent.parent.name, atoi(argv[2]), result_str);
                }
                else
                {
                    rt_kprintf("forlinx_pwm_test enable <channel>                     - enable pwm channel\n");
                    rt_kprintf("    e.g. MSH >forlinx_pwm_test enable  1              - PWM_CH1  nomal\n");
                }
            }
            else if(!strcmp(argv[1], "disable"))
            {
                if(argc == 3)
                {
                    result = rt_pwm_disable(pwm_device, atoi(argv[2]));
                }
                else
                {
                    rt_kprintf("forlinx_pwm_test disable <channel>                    - disable pwm channel\n");
                }
            }
            else if (!strcmp(argv[1], "set"))
            {
                if(argc == 7)
                {
                    result = rt_pwm_set_internal(pwm_device, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
                    rt_kprintf("pwm info set on %s at channel %d\n", pwm_device, atoi(argv[2]));
                }
                else
                {
                    rt_kprintf("Set info of device: [%s] error\n", pwm_device);
                    rt_kprintf("Usage: forlinx_pwm_test set <channel> <period> <pulse> <polarity> <aligned>\n");
                }
            }
        }
    }else{
        rt_kprintf("Usage: \n");
        rt_kprintf("forlinx_pwm_test probe   <device name>                                   - probe pwm by name\n");
        rt_kprintf("forlinx_pwm_test set     <channel> <period> <pulse> <polarity> <aligned> - set pwm channel info\n");
        rt_kprintf("forlinx_pwm_test enable  <channel>                                       - enable pwm channel\n");
        rt_kprintf("forlinx_pwm_test disable <channel>                                       - disable pwm channel\n");

    }
    return RT_EOK;
}

MSH_CMD_EXPORT(forlinx_pwm_test, forlinx pwm out test);


