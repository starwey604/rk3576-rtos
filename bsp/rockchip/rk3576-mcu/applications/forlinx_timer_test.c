
#include <rtthread.h>
#include <rtdevice.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "hal_base.h"
//#include "interrupt.h"

typedef void (*TimerISRCallback)(int vector, void* param); // 定义函数指针类型

uint16_t irq_count[5];
uint8_t nest=0;
struct TIMER_REG* time_reg[] = {TIMER6, TIMER7, TIMER8, TIMER9, TIMER10};
IRQn_Type time_irq[] = {TIMER6_IRQn, TIMER7_IRQn, TIMER8_IRQn, TIMER9_IRQn, TIMER10_IRQn};

void TIMER6_tick_isr(int vector, void *param)
{
    if(nest){
        printf("TIMER6 irq delay 90 ms start\n");
        // printf("delay 100 ms\n");
        HAL_DelayMs(90);
        printf("TIMER6 irq delay 90 ms end\n");
    }else{
        irq_count[0]++;
    }
    
    HAL_TIMER_ClrInt(TIMER6);
}

void TIMER7_tick_isr(int vector, void *param)
{
    if(nest){
        printf("TIMER7 irq start\n");
        // HAL_DelayMs(100);
        printf("TIMER7 irq end\n");
    }else{
        irq_count[1]++;
    }

    HAL_TIMER_ClrInt(TIMER7);
}
void TIMER8_tick_isr(int vector, void *param)
{
    irq_count[12]++;

    HAL_TIMER_ClrInt(TIMER8);
}
void TIMER9_tick_isr(int vector, void *param)
{
    if(nest){
        printf("TIMER9 irq start\n");
        HAL_DelayMs(60);
        printf("TIMER9 irq end\n");
    }else{
    	irq_count[3]++;
    }
    HAL_TIMER_ClrInt(TIMER9);
}
void TIMER10_tick_isr(int vector, void *param)
{
    if(nest){
        printf("TIMER10 irq start\n");
        HAL_DelayMs(60);
        printf("TIMER10 irq end\n");
    }else{
    	irq_count[4]++;
    }
    HAL_TIMER_ClrInt(TIMER10);
}

TimerISRCallback isr_callbacks[] = {
    TIMER6_tick_isr,
    TIMER7_tick_isr,
    TIMER8_tick_isr,
    TIMER9_tick_isr,
    TIMER10_tick_isr
};

static void forlinx_timer_test(int argc, char **argv)
{
    uint16_t count=0;

    if(argc > 1)
    {
        if(!strcmp(argv[1], "time"))
        {
            uint8_t time_num=0;
            if(argc == 3)
            {
                time_num = atoi(argv[2]) - 6;
                nest = 0;
                if(time_num >= 0 && time_num < 5)
                {
                    rt_hw_interrupt_install(time_irq[time_num], isr_callbacks[time_num], RT_NULL, RT_NULL);
                    rt_hw_interrupt_umask(time_irq[time_num]);
                    HAL_TIMER_Init(time_reg[time_num], TIMER_FREE_RUNNING);
                    HAL_TIMER_SetCount(time_reg[time_num], (PLL_INPUT_OSC_RATE / 100) - 1);
                    HAL_TIMER_Start_IT(time_reg[time_num]);

                    while(1)
                    {
                        if(count >= 30)
                            break;
                        HAL_DelayMs(100);
                        printf("count:%2d irq_counter%d:%d\n", count++, time_num+6, irq_count[time_num]);
                    }
                    printf("TIMER%d over\n", time_num+6);
                    HAL_TIMER_Stop_IT(time_reg[time_num]);
                }else{
                    rt_kprintf("Usage: \n");
                    rt_kprintf("forlinx_timer time <dev_name>   - Test timer interrupt\n");
                    rt_kprintf("\t<dev_name> : 6 ~ 10 \n");
                }
            }else{
                rt_kprintf("Usage: \n");
                rt_kprintf("forlinx_timer time <dev_name>   - Test timer interrupt\n");
                rt_kprintf("\t<dev_name> : 6 ~ 10 \n");
            }
        }
        else if(!strcmp(argv[1], "nest"))
        {
            nest = 1;
            rt_hw_interrupt_install(TIMER9_IRQn, TIMER9_tick_isr, RT_NULL, RT_NULL);
            rt_hw_interrupt_umask(TIMER9_IRQn);
            HAL_TIMER_Init(TIMER9, TIMER_FREE_RUNNING);
            HAL_TIMER_SetCount(TIMER9, (PLL_INPUT_OSC_RATE / 50) - 1);
            printf("set TIMER9 100ms\n");

            rt_hw_interrupt_install(TIMER10_IRQn, TIMER10_tick_isr, RT_NULL, RT_NULL);
            rt_hw_interrupt_umask(TIMER10_IRQn);
            HAL_TIMER_Init(TIMER10, TIMER_FREE_RUNNING);
            HAL_TIMER_SetCount(TIMER10, (PLL_INPUT_OSC_RATE / 100) - 1);
            printf("set TIMER10 10ms\n");
	    HAL_NVIC_SetPriority(TIMER9_IRQn, 2, 255);
            HAL_NVIC_SetPriority(TIMER10_IRQn, 1, 255);

            HAL_TIMER_Start_IT(TIMER9);
            HAL_TIMER_Start_IT(TIMER10);
            count = 0;
            while(1)
            {
                if(count >= 5)
                    break;
                count++;
                HAL_DelayMs(100);
            }
            HAL_TIMER_Stop_IT(TIMER9);
            printf("TIMER9 over\n");
            HAL_TIMER_Stop_IT(TIMER10);
            printf("TIMER10 over\n");

        }else{
            rt_kprintf("Usage: \n");
            rt_kprintf("forlinx_timer time <dev_name>   - Test TIMER timed interruption\n");
            rt_kprintf("forlinx_timer nest              - Test TIMER9 and TIMER10 interrupt nesting\n");
            rt_kprintf("\t<dev_name> : 6 ~ 10 \n");
        }
    }else{
        rt_kprintf("Usage: \n");
        rt_kprintf("forlinx_timer time       - Test TIMER timed interruption\n");
        rt_kprintf("forlinx_timer nest       - Test TIMER9 and TIMER10 interrupt nesting\n");
        rt_kprintf("\t<dev_name> : 6 ~ 10 \n");
    }
}

MSH_CMD_EXPORT_ALIAS(forlinx_timer_test, forlinx_timer, timer irq test cmd);
