/*
 * Copyright (c) 2025 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-24     Cliff Chen   first implementation
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdlib.h>
#include <string.h>

#if defined(RT_USING_COMMON_TEST_CACHE_PERF)

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

/* 测试线程相关参数 */
#define THREAD_STACK_SIZE  4096
#define THREAD_PRIORITY    20
#define THREAD_TIMESLICE   10

/* 测试模式定义 */
#define TEST_MODE_CACHE_OPS  0  /* 测试Cache操作性能 */
#define TEST_MODE_MEM_LATENCY 1 /* 测试内存访问延迟 */

/* CPU架构检测 */
#if defined(__aarch64__) || (defined(__ARM_ARCH) && __ARM_ARCH >= 8 && defined(__ARM_64BIT_STATE))
#define IS_AARCH64 1
#define IS_ARM 1
#define IS_RISCV 0
#define IS_RISCV64 0
#elif defined(__ARM_ARCH) && __ARM_ARCH >= 7
#define IS_AARCH64 0
#define IS_ARM 1
#define IS_RISCV 0
#define IS_RISCV64 0
#elif defined(__riscv) && (__riscv_xlen == 64)
#define IS_AARCH64 0
#define IS_ARM 0
#define IS_RISCV 1
#define IS_RISCV64 1
#elif defined(__riscv) && (__riscv_xlen == 32)
#define IS_AARCH64 0
#define IS_ARM 0
#define IS_RISCV 1
#define IS_RISCV64 0
#else
#define IS_AARCH64 0
#define IS_ARM 0
#define IS_RISCV 0
#define IS_RISCV64 0
#endif

/* CPU周期计数相关函数 - 支持ARM和RISC-V */
#if IS_AARCH64 /* ARMv8 AArch64模式 */

static inline uint64_t get_cycles(void)
{
    uint64_t val;
    /* 读取PMCCNTR_EL0寄存器 */
    __asm__ volatile("mrs %0, PMCCNTR_EL0" : "=r"(val));
    return val;
}

static inline void enable_cpu_cycle_counter(void)
{
    uint64_t val;

    /* 使能用户模式访问性能计数器 */
    __asm__ volatile("mrs %0, PMUSERENR_EL0" : "=r"(val));
    val |= 1UL;  /* 设置EN位 */
    __asm__ volatile("msr PMUSERENR_EL0, %0" :: "r"(val));

    /* 使能周期计数器 */
    __asm__ volatile("mrs %0, PMCNTENSET_EL0" : "=r"(val));
    val |= (1UL << 31);  /* 设置PMCCNTR使能位 */
    __asm__ volatile("msr PMCNTENSET_EL0, %0" :: "r"(val));

    /* 清零计数器 */
    __asm__ volatile("msr PMCCNTR_EL0, %0" :: "r"(0UL));

    /* 使能性能计数器 */
    __asm__ volatile("mrs %0, PMCR_EL0" : "=r"(val));
    val |= 1UL;  /* 设置E位使能PMU */
    __asm__ volatile("msr PMCR_EL0, %0" :: "r"(val));
}

static inline void disable_cpu_cycle_counter(void)
{
    uint64_t val;

    /* 禁用周期计数器 */
    __asm__ volatile("mrs %0, PMCNTENCLR_EL0" : "=r"(val));
    val |= (1UL << 31);  /* 清除PMCCNTR使能位 */
    __asm__ volatile("msr PMCNTENCLR_EL0, %0" :: "r"(val));
}

#elif IS_ARM /* ARMv7-A或ARMv8 AArch32模式 */

static inline uint64_t get_cycles(void)
{
    uint32_t pmccntr;
    uint32_t pmuseren;
    uint32_t pmcntenset;

    /* 读取PMUSEREN寄存器，检查用户模式访问权限 */
    __asm__ volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
    if (pmuseren & 1)    /* 检查允许用户模式访问 */
    {
        __asm__ volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
        if (pmcntenset & 0x80000000)    /* 检查周期计数器是否启用 */
        {
            __asm__ volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
            return ((uint64_t)pmccntr);
        }
    }

    return 0;
}

static inline void enable_cpu_cycle_counter(void)
{
    /* 配置性能计数器控制寄存器 */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(1));

    /* 使能所有计数器 */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x8000000f));

    /* 清零所有计数器 */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 3" :: "r"(0x8000000f));
}

static inline void disable_cpu_cycle_counter(void)
{
    /* 禁用所有计数器 */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 2" :: "r"(0x8000000f));
}

#elif IS_RISCV64 /* RISC-V 64位 */

static inline uint64_t get_cycles(void)
{
    uint64_t cycles;
    /* 读取cycle寄存器，获取CPU周期计数 */
    __asm__ volatile("rdcycle %0" : "=r"(cycles));
    return cycles;
}

static inline void enable_cpu_cycle_counter(void)
{
    /* RISC-V的周期计数器总是启用的，不需要特殊启用操作 */
}

static inline void disable_cpu_cycle_counter(void)
{
    /* RISC-V的周期计数器不能被禁用 */
}

#elif IS_RISCV /* RISC-V 32位 */

static inline uint64_t get_cycles(void)
{
    uint32_t cycles_hi, cycles_lo;

    /* 读取cycle寄存器高32位和低32位 */
    __asm__ volatile("rdcycleh %0" : "=r"(cycles_hi));
    __asm__ volatile("rdcycle %0" : "=r"(cycles_lo));

    /* 将高32位和低32位组合成64位值 */
    return ((uint64_t)cycles_hi << 32) | cycles_lo;
}

static inline void enable_cpu_cycle_counter(void)
{
    /* RISC-V的周期计数器总是启用的，不需要特殊启用操作 */
}

static inline void disable_cpu_cycle_counter(void)
{
    /* RISC-V的周期计数器不能被禁用 */
}

#else
#warning "不支持当前架构的周期计数器，将使用RT-Thread的tick计数代替"
static inline uint64_t get_cycles(void)
{
    return rt_tick_get();
}

static inline void enable_cpu_cycle_counter(void)
{
    /* 不需要特殊操作 */
}

static inline void disable_cpu_cycle_counter(void)
{
    /* 不需要特殊操作 */
}
#endif

/* 获取Cache line大小 */
static int get_cache_line_size(void)
{
    /* 如果RT-Thread定义了Cache line大小，优先使用 */
#if defined(CACHE_LINE_SIZE)
    return CACHE_LINE_SIZE;
#endif

    /* 如果未定义，尝试从CPU寄存器获取 */
#if IS_AARCH64  /* ARMv8 AArch64架构 */
    uint64_t ctr;
    __asm__ volatile("mrs %0, CTR_EL0" : "=r"(ctr));
    return 4 << ((ctr >> 16) & 0xf);  /* 从CTR_EL0寄存器获取DCache line大小 */
#elif IS_ARM  /* ARMv7或ARMv8 AArch32架构 */
    uint32_t ctr;
    __asm__ volatile("mrc p15, 0, %0, c0, c0, 1" : "=r"(ctr));
    return 4 << ((ctr >> 16) & 0xf);  /* 从CTR寄存器获取DCache line大小 */
#elif IS_RISCV  /* RISC-V架构 */
    /* RISC-V处理器通常使用32或64字节的Cache行
     * 这里假设使用64字节
     */
    return 64;
#else
    /* 默认假设为64字节 */
    return 64;
#endif
}

/* 获取处理器名称信息 */
static void print_cpu_info(void)
{
#if IS_AARCH64
    uint64_t midr;
    __asm__ volatile("mrs %0, MIDR_EL1" : "=r"(midr));

    uint32_t implementer = (midr >> 24) & 0xFF;
    uint32_t variant = (midr >> 20) & 0xF;
    uint32_t architecture = (midr >> 16) & 0xF;
    uint32_t partnum = (midr >> 4) & 0xFFF;
    uint32_t revision = midr & 0xF;

    rt_kprintf("CPU: AArch64 Implementer=0x%02x Variant=0x%x Architecture=0x%x PartNum=0x%03x Revision=0x%x\n",
               implementer, variant, architecture, partnum, revision);
#elif IS_ARM
    uint32_t midr;
    __asm__ volatile("mrc p15, 0, %0, c0, c0, 0" : "=r"(midr));

    uint32_t implementer = (midr >> 24) & 0xFF;
    uint32_t variant = (midr >> 20) & 0xF;
    uint32_t architecture = (midr >> 16) & 0xF;
    uint32_t partnum = (midr >> 4) & 0xFFF;
    uint32_t revision = midr & 0xF;

    rt_kprintf("CPU: ARMv7/AArch32 Implementer=0x%02x Variant=0x%x Architecture=0x%x PartNum=0x%03x Revision=0x%x\n",
               implementer, variant, architecture, partnum, revision);
#elif IS_RISCV64
    rt_kprintf("CPU: RISC-V 64-bit\n");
    /* 尝试读取一些RISC-V CSR寄存器以获取更多信息 */
    unsigned long mvendorid = 0, marchid = 0, mimpid = 0;

    /* 尝试读取mvendorid (厂商ID) */
    __asm__ volatile("csrr %0, mvendorid" : "=r"(mvendorid));

    /* 尝试读取marchid (架构ID) */
    __asm__ volatile("csrr %0, marchid" : "=r"(marchid));

    /* 尝试读取mimpid (实现ID) */
    __asm__ volatile("csrr %0, mimpid" : "=r"(mimpid));

    rt_kprintf("RISC-V Vendor ID: 0x%lx, Architecture ID: 0x%lx, Implementation ID: 0x%lx\n",
               mvendorid, marchid, mimpid);
#elif IS_RISCV
    rt_kprintf("CPU: RISC-V 32-bit\n");
    /* 尝试读取一些RISC-V CSR寄存器以获取更多信息 */
    unsigned long mvendorid = 0, marchid = 0, mimpid = 0;

    /* 尝试读取mvendorid (厂商ID) */
    __asm__ volatile("csrr %0, mvendorid" : "=r"(mvendorid));

    /* 尝试读取marchid (架构ID) */
    __asm__ volatile("csrr %0, marchid" : "=r"(marchid));

    /* 尝试读取mimpid (实现ID) */
    __asm__ volatile("csrr %0, mimpid" : "=r"(mimpid));

    rt_kprintf("RISC-V Vendor ID: 0x%lx, Architecture ID: 0x%lx, Implementation ID: 0x%lx\n",
               mvendorid, marchid, mimpid);
#else
    rt_kprintf("CPU: Unknown architecture\n");
#endif

#ifdef RT_USING_SMP
    rt_kprintf("Current running on CPU %d\n", rt_hw_cpu_id());
#endif
}

/* Cache操作性能测试函数 */
static void cache_performance_test(int test_size, int iterations)
{
    void *test_buffer;
    uint64_t start_cycles, end_cycles;
    uint64_t clean_cycles = 0, invalidate_cycles = 0;
    int line_size = get_cache_line_size();
    int num_lines = test_size / line_size;
    int i;
    uint64_t clean_cycles_per_line_x100, invalidate_cycles_per_line_x100;

    rt_kprintf("Starting cache performance test...\n");
    print_cpu_info();
    rt_kprintf("Cache line size: %d bytes\n", line_size);
    rt_kprintf("Test buffer size: %d bytes (%d cache lines)\n", test_size, num_lines);
    rt_kprintf("Iterations: %d\n\n", iterations);

    /* 分配对齐到cache line大小的测试缓冲区 */
    test_buffer = rt_malloc_align(test_size, line_size);
    if (!test_buffer)
    {
        rt_kprintf("Error: Failed to allocate test buffer\n");
        return;
    }

    /* 初始化缓冲区以确保它被加载到Cache中 */
    memset(test_buffer, 0x55, test_size);

    /* 启用CPU周期计数器 */
    enable_cpu_cycle_counter();

    /* 测试Cache Clean操作性能 */
    rt_kprintf("Testing cache clean performance...\n");
    for (i = 0; i < iterations; i++)
    {
        /* 确保数据在Cache中并且是"脏"数据 */
        volatile uint8_t *p = (volatile uint8_t *)test_buffer;
        for (int j = 0; j < test_size; j += line_size)
        {
            p[j] = (uint8_t)(i & 0xFF);
        }

        /* 强制刷新流水线并开始计数 */
#if IS_ARM || IS_AARCH64
#if IS_AARCH64
        __asm__ volatile("dsb sy");
#else
        __asm__ volatile("dsb");
#endif
#elif IS_RISCV
        __asm__ volatile("fence");
#endif

        start_cycles = get_cycles();

        /* 执行Cache Clean操作，使用RT-Thread的API */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, test_buffer, test_size);

        /* 结束计数 */
        end_cycles = get_cycles();

        /* 累加周期数 */
        clean_cycles += (end_cycles - start_cycles);
    }

    /* 测试Cache Invalidate操作性能 */
    rt_kprintf("Testing cache invalidate performance...\n");
    for (i = 0; i < iterations; i++)
    {
        /* 确保数据在Cache中 */
        volatile uint8_t *p = (volatile uint8_t *)test_buffer;
        for (int j = 0; j < test_size; j += line_size)
        {
            volatile uint8_t dummy = p[j];
            (void)dummy;
        }

        /* 强制刷新流水线并开始计数 */
#if IS_ARM || IS_AARCH64
#if IS_AARCH64
        __asm__ volatile("dsb sy");
#else
        __asm__ volatile("dsb");
#endif
#elif IS_RISCV
        __asm__ volatile("fence");
#endif

        start_cycles = get_cycles();

        /* 执行Cache Invalidate操作，使用RT-Thread的API */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, test_buffer, test_size);

        /* 结束计数 */
        end_cycles = get_cycles();

        /* 累加周期数 */
        invalidate_cycles += (end_cycles - start_cycles);
    }

    /* 禁用CPU周期计数器 */
    disable_cpu_cycle_counter();

    /* 计算平均每个Cache line操作所需的周期数 (整数版，乘以100保留精度) */
    clean_cycles_per_line_x100 = (clean_cycles * 100) / (iterations * num_lines);
    invalidate_cycles_per_line_x100 = (invalidate_cycles * 100) / (iterations * num_lines);

    /* 输出测试结果 */
    rt_kprintf("\nTest Results:\n");
    rt_kprintf("Total test iterations: %d\n", iterations);
    rt_kprintf("Total cache lines processed: %d\n\n", iterations * num_lines);

    rt_kprintf("Cache Clean Performance:\n");
    rt_kprintf("  Total cycles: %llu\n", clean_cycles);
    rt_kprintf("  Average cycles per operation: %llu\n", clean_cycles / iterations);
    rt_kprintf("  Average cycles per cache line: %llu.%02llu\n\n",
               clean_cycles_per_line_x100 / 100,
               clean_cycles_per_line_x100 % 100);

    rt_kprintf("Cache Invalidate Performance:\n");
    rt_kprintf("  Total cycles: %llu\n", invalidate_cycles);
    rt_kprintf("  Average cycles per operation: %llu\n", invalidate_cycles / iterations);
    rt_kprintf("  Average cycles per cache line: %llu.%02llu\n",
               invalidate_cycles_per_line_x100 / 100,
               invalidate_cycles_per_line_x100 % 100);

    /* 释放测试缓冲区 */
    rt_free_align(test_buffer);

    rt_kprintf("Cache test completed.\n");
}

/* 创建内存随机访问链表 */
static void *create_mem_chain(size_t total_size, size_t stride, int random_order)
{
    char *buffer;
    size_t npointers, i;
    size_t *p, *tmp;

    /* 确保stride最小为sizeof(size_t) */
    if (stride < sizeof(size_t))
    {
        stride = sizeof(size_t);
    }

    /* 确保total_size足够大 */
    if (total_size < stride * 2)
    {
        total_size = stride * 2;
    }

    /* 计算可以放置多少个指针 */
    npointers = total_size / stride;

    /* 确保至少有两个指针 */
    if (npointers < 2)
    {
        npointers = 2;
        total_size = npointers * stride;
    }

    /* 分配内存 */
    buffer = (char *)rt_malloc_align(total_size, 64);  /* 对齐到64字节 */
    if (!buffer)
    {
        rt_kprintf("Error: Failed to allocate memory for random access test\n");
        return NULL;
    }

    /* 初始化内存 */
    memset(buffer, 0, total_size);

    /* 创建链表 */
    for (i = 0; i < npointers - 1; i++)
    {
        p = (size_t *)(buffer + i * stride);
        *p = (size_t)(buffer + (i + 1) * stride);
    }

    /* 最后一个指针指向第一个 */
    p = (size_t *)(buffer + (npointers - 1) * stride);
    *p = (size_t)(buffer);

    /* 如果需要随机顺序，打乱链表 */
    if (random_order)
    {
        size_t randpos, iterations;

        /* 使用Fisher-Yates洗牌算法，迭代次数取决于指针数量 */
        iterations = npointers * 2;  /* 基本洗牌次数 */

        for (i = 0; i < iterations; i++)
        {
            /* 随机选择一个指针 */
            randpos = (size_t)rand() % npointers;
            p = (size_t *)(buffer + randpos * stride);

            /* 获取指向的下一个位置 */
            tmp = (size_t *)(*p);

            /* 随机选择另一个指针 */
            randpos = (size_t)rand() % npointers;
            size_t *q = (size_t *)(buffer + randpos * stride);

            /* 交换p和q指向的位置 */
            *p = *q;
            *q = (size_t)tmp;
        }
    }

    return buffer;
}

/* 测量内存链表的访问延迟 */
static void measure_mem_latency(void *chain, size_t iterations, size_t total_size, size_t stride)
{
    uint64_t start_cycles, end_cycles, total_cycles = 0;
    size_t *p = (size_t *)chain;
    size_t i, npointers;
    uint64_t cycles_per_access_x100;
    size_t warmup_iterations;
    size_t nruns = 5;  /* 多次运行取最佳结果 */
    uint64_t best_cycles = UINT64_MAX;
    uint64_t run_cycles[5] = {0};

    /* 计算链表中的指针数量 */
    npointers = total_size / stride;

    /* 预热迭代次数 - 足够遍历整个链表多次 */
    warmup_iterations = npointers * 3;

    rt_kprintf("Running memory latency test with %lu pointers, %lu iterations...\n",
               npointers, iterations);

    /* 多次运行测试，取最佳结果 */
    for (size_t run = 0; run < nruns; run++)
    {
        rt_kprintf("Run %lu/%lu: ", run + 1, nruns);

        /* 第一阶段：彻底预热 - 确保整个链表在Cache中 */
        rt_kprintf("Warming up cache...");
        p = (size_t *)chain;

        /* 先遍历整个链表，确保所有节点都被访问 */
        for (i = 0; i < npointers; i++)
        {
            p = (size_t *)(*p);
        }

        /* 再进行深度预热，确保链表稳定在Cache中 */
        for (i = 0; i < warmup_iterations; i++)
        {
            p = (size_t *)(*p);
        }

        /* 强制内存屏障 */
#if IS_ARM || IS_AARCH64
#if IS_AARCH64
        __asm__ volatile("dsb sy");
#else
        __asm__ volatile("dsb");
#endif
#elif IS_RISCV
        __asm__ volatile("fence");
#endif

        /* 第二阶段：预运行 - 稳定处理器状态 */
        p = (size_t *)chain;
        for (i = 0; i < 1000; i++)
        {
            p = (size_t *)(*p);
        }

        /* 强制内存屏障 */
#if IS_ARM || IS_AARCH64
#if IS_AARCH64
        __asm__ volatile("dsb sy");
#else
        __asm__ volatile("dsb");
#endif
#elif IS_RISCV
        __asm__ volatile("fence");
#endif

        rt_kprintf("Measuring...");

        /* 启用CPU周期计数器 */
        enable_cpu_cycle_counter();

        /* 第三阶段：开始测量 */
        start_cycles = get_cycles();

        /* 访问链表 */
        for (i = 0; i < iterations; i++)
        {
            p = (size_t *)(*p);
        }

        /* 防止编译器优化掉循环 */
        volatile size_t dummy = (size_t)p;
        (void)dummy;

        /* 结束测量 */
        end_cycles = get_cycles();

        /* 禁用CPU周期计数器 */
        disable_cpu_cycle_counter();

        /* 计算本次运行的总周期数 */
        run_cycles[run] = end_cycles - start_cycles;

        /* 记录最佳结果 */
        if (run_cycles[run] < best_cycles)
        {
            best_cycles = run_cycles[run];
        }

        rt_kprintf("Done. Cycles: %llu\n", run_cycles[run]);

        /* 每次运行之间短暂休息 */
        rt_thread_mdelay(100);
    }

    /* 使用最佳结果计算平均每次访问的周期数 */
    total_cycles = best_cycles;
    cycles_per_access_x100 = (total_cycles * 100) / iterations;

    /* 输出最终结果 */
    rt_kprintf("\nMemory Access Latency Results:\n");
    rt_kprintf("Best run: %llu cycles total for %lu iterations\n",
               best_cycles, iterations);
    rt_kprintf("Memory access latency: %llu.%02llu cycles per access\n",
               cycles_per_access_x100 / 100,
               cycles_per_access_x100 % 100);

    /* 显示每次运行的结果 */
    rt_kprintf("\nAll runs (cycles):");
    for (size_t run = 0; run < nruns; run++)
    {
        rt_kprintf(" %llu", run_cycles[run]);
    }
    rt_kprintf("\n");
}

/* 内存随机访问延迟测试函数 */
static void memory_latency_test(int test_size, int iterations, int stride)
{
    void *chain;

    rt_kprintf("Starting memory latency test...\n");
    print_cpu_info();
    rt_kprintf("Test size: %d bytes\n", test_size);
    rt_kprintf("Stride: %d bytes\n", stride);
    rt_kprintf("Iterations: %d\n\n", iterations);

    /* 初始化随机数发生器 */
    srand(rt_tick_get());

    /* 创建随机访问链表 */
    chain = create_mem_chain(test_size, stride, 1);
    if (!chain)
    {
        return;
    }

    /* 测量访问延迟 */
    rt_kprintf("Measuring random memory access latency...\n");
    measure_mem_latency(chain, iterations, test_size, stride);

    /* 释放内存 */
    rt_free_align(chain);

    rt_kprintf("Memory latency test completed.\n");
}

/* 测试主函数 */
static void perf_test(int test_size, int iterations, int stride, int test_mode)
{
    /* 根据测试模式运行不同测试 */
    if (test_mode == TEST_MODE_CACHE_OPS)
    {
        cache_performance_test(test_size, iterations);
    }
    else if (test_mode == TEST_MODE_MEM_LATENCY)
    {
        memory_latency_test(test_size, iterations, stride);
    }
}

/* 测试线程入口函数 */
static void test_thread_entry(void *parameter)
{
    int *params = (int *)parameter;
    int test_size = params[0];
    int iterations = params[1];
    int stride = params[2];
    int test_mode = params[3];

    perf_test(test_size, iterations, stride, test_mode);

    /* 完成后释放参数内存 */
    rt_free(params);
}

/* MSH命令处理函数 */
int cmd_cache_perf_test(int argc, char **argv)
{
    int test_size = 64 * 1024;  /* 默认测试64KB数据 */
    int iterations = 100;      /* 默认测试100次迭代 */
    int stride = 64;          /* 默认步长64字节 */
    long cpu_id = -1;          /* 默认不绑定CPU */
    int test_mode = TEST_MODE_CACHE_OPS; /* 默认测试Cache操作 */
    rt_thread_t test_thread;
    int *params;

    /* 解析命令行参数 */
    if (argc > 1)
    {
        if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--memory") == 0)
        {
            /* 内存延迟测试模式 */
            test_mode = TEST_MODE_MEM_LATENCY;

            /* 移动参数位置 */
            if (argc > 2)
            {
                test_size = atoi(argv[2]);
            }
            if (argc > 3)
            {
                iterations = atoi(argv[3]);
            }
            if (argc > 4)
            {
                stride = atoi(argv[4]);
            }
#ifdef RT_USING_SMP
            if (argc > 5)
            {
                cpu_id = atoi(argv[5]);
                if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
                {
                    rt_kprintf("Invalid CPU ID: %d, valid range: 0-%d\n", cpu_id, RT_CPUS_NR - 1);
                    return -1;
                }
            }
#endif
        }
        else
        {
            /* Cache操作测试模式 */
            test_size = atoi(argv[1]);
            if (argc > 2)
            {
                iterations = atoi(argv[2]);
            }
#ifdef RT_USING_SMP
            if (argc > 3)
            {
                cpu_id = atoi(argv[3]);
                if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
                {
                    rt_kprintf("Invalid CPU ID: %d, valid range: 0-%d\n", cpu_id, RT_CPUS_NR - 1);
                    return -1;
                }
            }
#endif
        }
    }

    /* 分配参数数组 */
    params = (int *)rt_malloc(sizeof(int) * 4);
    if (!params)
    {
        rt_kprintf("Error: Failed to allocate memory for parameters\n");
        return -1;
    }
    params[0] = test_size;
    params[1] = iterations;
    params[2] = stride;
    params[3] = test_mode;

    /* 创建测试线程 */
    test_thread = rt_thread_create("perf_test",
                                   test_thread_entry,
                                   params,
                                   THREAD_STACK_SIZE,
                                   THREAD_PRIORITY,
                                   THREAD_TIMESLICE);
    if (!test_thread)
    {
        rt_kprintf("Error: Failed to create test thread\n");
        rt_free(params);
        return -1;
    }

#ifdef RT_USING_SMP
    /* 如果指定了CPU ID，绑定线程到该CPU */
    if (cpu_id >= 0)
    {
        rt_kprintf("Binding thread to CPU %d...\n", cpu_id);
        rt_thread_control(test_thread, RT_THREAD_CTRL_BIND_CPU, (void *)(cpu_id));
    }
#endif

    /* 启动线程 */
    rt_thread_startup(test_thread);

    return 0;
}

/* 内存延迟测试命令 */
int cmd_mem_latency_test(int argc, char **argv)
{
    char *new_argv[6];
    int new_argc = 0;
    char mem_arg[] = "-m";

    /* 构建新参数数组，添加-m选项 */
    new_argv[new_argc++] = argv[0];
    new_argv[new_argc++] = mem_arg;

    /* 复制原有参数 */
    for (int i = 1; i < argc && new_argc < 6; i++)
    {
        new_argv[new_argc++] = argv[i];
    }

    /* 调用主测试命令 */
    return cmd_cache_perf_test(new_argc, new_argv);
}

#ifdef RT_USING_FINSH
#ifdef RT_USING_SMP
MSH_CMD_EXPORT_ALIAS(cmd_cache_perf_test, cache_perf, "cache performance test [size] [iterations] [cpu_id] or -m/--memory [size] [iterations] [stride] [cpu_id]");
MSH_CMD_EXPORT_ALIAS(cmd_mem_latency_test, mem_latency, "memory latency test [size] [iterations] [stride] [cpu_id]");
#else
MSH_CMD_EXPORT_ALIAS(cmd_cache_perf_test, cache_perf, "cache performance test [size] [iterations] or -m/--memory [size] [iterations] [stride]");
MSH_CMD_EXPORT_ALIAS(cmd_mem_latency_test, mem_latency, "memory latency test [size] [iterations] [stride]");
#endif
#endif

#endif /* end of RT_USING_COMMON_TEST_CACHE_PERF */