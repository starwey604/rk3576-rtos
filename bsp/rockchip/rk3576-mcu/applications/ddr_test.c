/********************************************************************************************************************************* */
#include <stdio.h>
#include <string.h>
#include <rtthread.h>
#include <rthw.h>
#include <hal_base.h>

#define SHM_ADDR (0x27900000)
#define DATA_SIZE 4*1024*1024   //4M = 0x400000
static uint32_t irq_count=0;

void forlinx_ddr_test(void)
{
    uint32_t  value;
    uint32_t  ddr_addr,ddr_size,i,count;
    ddr_addr=0x27900000;
    uint32_t * data=(volatile uint32_t*)0x100000;
    value=0;
    ddr_size=128;
    count=0;
    rt_kprintf("mem_test:ddr :%x size:%d\n",ddr_addr,ddr_size);
    for(i=0;i<ddr_size;i=i+4)
    {
        value = *(volatile uint32_t *)(ddr_addr+i);

        //printf("before write: DDR  addr i:%d 0x%x:0x%x\n",i,ddr_addr,data[i]);
        rt_kprintf("before write: DDR  addr i:%d 0x%x:0x%x\n",i,ddr_addr+i,value);
        //*(volatile unsigned int *)(map_base+i) = Value + 1;
        //*(map_base+i) = 1;
    }
    /*//for(i=0;i<ddr_size;i=i+4)
    {
        //*(volatile uint32_t *)(0x100000+i) = 0xa;
        memset((volatile uint8_t*)0x100000,0xaa,128);
    }*/


    while (1)
    {

        if( *(volatile uint32_t *)(ddr_addr) == 0xcc)
        {
            HAL_DelayUs(10);
            for (i=0;i<ddr_size;i=i+4)
            {
                value = *(volatile uint32_t *)(ddr_addr+i);
                if(value != 0xcc)
                    rt_kprintf(" error at loop:%d addr i:%d 0x%x:0x%x\n",count,i,ddr_addr+i,value);
                    //*(volatile unsigned int *)(map_base+i) = Value + 1;
                    //*(map_base+i) = 1;
            }
            *(volatile uint32_t *)(ddr_addr) = 0;
            for(i=0;i<ddr_size;i=i+4)
            {
               *(volatile uint32_t *)(ddr_addr+i) = 0xaa;
            }
            rt_kprintf("loop:%d\n",count);
            count ++;
        }
        HAL_DelayUs(990);
     }
}

MSH_CMD_EXPORT_ALIAS(forlinx_ddr_test, forlinx_ddr, mcu use ddr test);
