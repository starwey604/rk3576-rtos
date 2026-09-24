#include <rtthread.h>
#include <rtdevice.h>

#include <unistd.h>
#include <stdlib.h>
#include "hal_base.h"

#define DEV_NAME "pin"


static void usage(void){
    rt_kprintf("  usage: forlinx_gpio <dir> <val>\n\n");
    rt_kprintf("  dir:      direction        (0:input, 1:output)\n");
    rt_kprintf("  val:      output level     (0:low 1:high)\n");
    rt_kprintf("            ignore  (=\n");
    rt_kprintf("example(output high): forlinx_gpio 1 1\n");
    rt_kprintf("example(output low) : forlinx_gpio 1 0\n");
    rt_kprintf("example(input)      : forlinx_gpio 0 0\n\n");
}

/*
 * 测试GPIO 通过输入参数，确定GPIO引脚功能（输入/输出）如果是输入则第三个无效，如果是输出，则第三个参数确定引脚输出状态
 * GPIO1_03 原理图：P27-28（VO_LCDC_CLK）
*/
static void forlinx_gpio_test(int argc, char **argv)
{
    char *pstr;
    uint32_t dir   = (uint32_t) -1;
    uint32_t val   = (uint32_t) -1;
    struct rt_device_pin_mode pin_mode;

    if (argc == 3)
    {
        printf("this is forlinx gpio test.\n");

        // Get dir: output or input
        dir = strtol(argv[1], &pstr, 10);
        if ((*pstr != 0)  || (dir > 2))
        {
            usage();
        }
        val = strtol(argv[2], &pstr, 10);
        if ((*pstr != 0)  || (val > 2))
        {
            usage();
        }
        printf("dir = %ld, val = %ld\n", dir, val);

        pin_mode.pin = BANK_PIN(GPIO_BANK1, 29);
        HAL_PINCTRL_SetParam(GPIO_BANK1, 0x01UL << 29, PIN_CONFIG_DRV_LEVEL2);   //设置驱动能力
        if(dir == 1)
        {
            if(val == 1)
            {
                printf("GPIO1_29 output high\n\n");
            }else{
                printf("GPIO1_29 output low\n\n");
            }
            pin_mode.mode = PIN_MODE_OUTPUT;
            rt_pin_mode(pin_mode.pin, pin_mode.mode);
            rt_pin_write(pin_mode.pin, val);
        }else if(dir == 0){
            pin_mode.mode = PIN_MODE_INPUT;
            rt_pin_mode(pin_mode.pin, pin_mode.mode);
            val = rt_pin_read(pin_mode.pin);
            printf("GPIO1_29 input val = %ld\n\n", val);

        }else{
            usage();
        }
    }else{
        usage();
    }
}

MSH_CMD_EXPORT_ALIAS(forlinx_gpio_test, forlinx_gpio, gpio test cmd);


#define PIN_NUM(p) ((p & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT)
#define PIN_BANK(p) ((p & GPIO_BANK_MASK) >> GPIO_BANK_SHIFT)
static volatile uint32_t isr_flag = 0;
static struct rt_device_pin_status g_pin_status;

static void irq_callback(void *args)
{
    struct rt_device_pin_status *pstatus = (struct rt_device_pin_status *)args;

    isr_flag = 1;
#ifdef USE_DEVICE_OPS
    rt_device_read(pin_dev, 0, pstatus, sizeof(struct rt_device_pin_status));
#else
    pstatus->status = rt_pin_read(pstatus->pin);
#endif
    rt_pin_detach_irq(pstatus->pin);
    rt_pin_irq_enable(pstatus->pin, PIN_IRQ_DISABLE);

    rt_kprintf("isr: gpio%d pin%d input level %d\n\n", PIN_BANK(pstatus->pin), PIN_NUM(pstatus->pin), pstatus->status);
}
/*
 * 测试GPIO中断 
 * GPIO1_03 原理图：P27-28（VO_LCDC_CLK）
*/
static void forlinx_gpio_irq(int argc, char **argv)
{
    int i;

    struct rt_device_pin_mode pin_mode;
    struct rt_device_pin_status pin_status;

    pin_mode.pin = BANK_PIN(GPIO_BANK1, 29);
    pin_status.pin = BANK_PIN(GPIO_BANK1, 29);
    // HAL_PINCTRL_SetParam(GPIO_BANK1, 0x01UL << 3, PIN_CONFIG_DRV_LEVEL2);   //设置驱动能力
    pin_mode.mode = PIN_MODE_INPUT_PULLUP;
    rt_pin_mode(pin_mode.pin, pin_mode.mode);

    memcpy(&g_pin_status, &pin_status, sizeof(pin_status));
    rt_pin_attach_irq(pin_mode.pin, PIN_IRQ_MODE_FALLING, irq_callback, (void *)&g_pin_status);

    rt_pin_irq_enable(pin_mode.pin, PIN_IRQ_ENABLE);

    isr_flag = 0;
    rt_kprintf("wait 60s for gpio%d pin5 input...\n", GPIO_BANK1);

    //wait isr
    for (i = 0; i < 60; i++)
    {
        HAL_DelayMs(1000);
        if (isr_flag)
        {
            break;
        }
    }
    if (i >= 60)
    {
        rt_kprintf("wait for gpio%d pin5 input TIMEOUT!\n\n", GPIO_BANK1);
        rt_pin_detach_irq(pin_mode.pin);
        rt_pin_irq_enable(pin_mode.pin, PIN_IRQ_DISABLE);
    }

}
MSH_CMD_EXPORT_ALIAS(forlinx_gpio_irq, forlinx_gpio_irq, gpio irq test cmd);

