/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */
/* RT-Thread Kernel */
/* kservice optimization */
/* Inter-Thread communication */
/* Memory Management */
/* Kernel Device Object */
/* RT-Thread Components */
/* Device Drivers */
/* Using USB */
/* C/C++ and POSIX layer */
/* POSIX (Portable Operating System Interface) layer */
/* Interprocess Communication (IPC) */
/* Socket is in the 'Network' category */
/* Network */
/* Utilities */
/* RT-Thread Benchmarks */
/* System */
/* RT-Thread Utestcases */
/* RT-Thread third party package */
/* Bluetooth */
/* examples bluetooth */
/* Bluetooth examlpes */
/* Example 'BT API TEST' Config */
/* Example 'BT DISCOVERY' Config */
/* Example 'A2DP SINK' Config */
/* Example 'A2DP SOURCE' Config  */
/* Example 'HFP CLIENT' Config */
/* RT-Thread rockchip common drivers */
/* Enable Fault Dump Hook */
/* RT-Thread rockchip inno-mipi-dphy driver */
/* RT-Thread rockchip jpeg enc driver */
/* RT-Thread rockchip rga driver */
/* RT-Thread rockchip pm drivers */
/* RT-Thread rockchip mipi-dphy driver */
/* RT-Thread rockchip isp driver */
/* RT-Thread rockchip vcm driver */
/* RT-Thread rockchip vicap driver */
/* RT-Thread rockchip camera driver */
/* RT-Thread rockchip ambient light sensor driver */
/* RT-Thread rockchip vicap_lite driver */
/* RT-Thread rockchip csi2host driver */
/* RT-Thread rockchip buffer_manage driver */
/* RT-Thread rockchip coredump driver */
/* Enable PSTORE */
/* RT-Thread rockchip RPMSG driver */
/* Enable FTL */
/* RT-Thread rockchip rk3576 mcu drivers */
/* Enable UART */
/* Enable SPI */
/* RT-Thread board config */
/* RT-Thread Common Test case */
MEMORY
{
    DDR (rxw) : ORIGIN = 0x00000000, LENGTH = 512K
    LINUX_ATAGS (rxw) : ORIGIN = 0x20000000, LENGTH = 0x2000 /* shared memory for linux atags */
    LINUX_RPMSG (rxw) : ORIGIN = 0x27d00000, LENGTH = 0x00400000 /* shared memory for linux rpmsg */
}
MAIN_STACK_SIZE = 0x400;
ENTRY(Reset_Handler)
SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
        *start_m0.o(.text .text.* .rodata .rodata*)
        . = ALIGN(4);
    } > DDR
    .text :
    {
        KEEP(*(.init))
        KEEP(*(.fini))
        _stext = .;
        *(.text) /* remaining code */
        *(.text.*) /* remaining code */
        *(.rodata) /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)
        . = ALIGN(4);
        PROVIDE(__ctors_start__ = .);
        /* old GCC version uses .ctors */
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        /* new GCC version uses .init_array */
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);
        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);
        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(4);
        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;
        . = ALIGN(4);
        . = ALIGN(32);
        _etext = .;
    } > DDR
    .data :
    {
        . = ALIGN(32);
        __data_start__ = .;
        KEEP(*(.sram.data))
        *(vtable)
        *(.data*)
        . = ALIGN(4);
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);
        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > DDR
    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        __copy_table_end__ = .;
    } > DDR
    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (ADDR(.bss))
        LONG (SIZEOF(.bss))
        __zero_table_end__ = .;
    } > DDR
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        /* This is used by the startup in order to initialize the .data secion */
        _sidata = .;
        __exidx_end = .;
    } > DDR
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > DDR
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        . = ALIGN(4);
    } > DDR
    .heap :
    {
        . = ALIGN(4);
        PROVIDE( __sram_heap_start__ = .);
        . = ORIGIN(DDR) + LENGTH(DDR) - MAIN_STACK_SIZE;
        PROVIDE( __sram_heap_end__ = . );
        . = ALIGN(4);
    } > DDR
    .stack (NOLOAD) :
    {
        . = ALIGN(4);
        _sstack = .;
        . = . + MAIN_STACK_SIZE;
        _estack = .;
        . = ALIGN(4);
        PROVIDE(__StackTop = .);
    } > DDR
    .linux_share_atags(NOLOAD) :
    {
        PROVIDE(__linux_share_atags_start__ = .);
        . += LENGTH(LINUX_ATAGS);
        PROVIDE(__linux_share_atags_end__ = .);
    } > LINUX_ATAGS
    .linux_share_rpmsg(NOLOAD) :
    {
        PROVIDE(__linux_share_rpmsg_start__ = .);
        . += LENGTH(LINUX_RPMSG);
        PROVIDE(__linux_share_rpmsg_end__ = .);
    } > LINUX_RPMSG
}
