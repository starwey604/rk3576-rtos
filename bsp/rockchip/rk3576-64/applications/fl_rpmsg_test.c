#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include "hal_base.h"
#include "rpmsg_lite.h"
#include "rpmsg_queue.h"
#include "rpmsg_ns.h"

// test is CPU0 as master and CPU3 as remote.
#define MASTER_ID   ((uint32_t)0)
#define REMOTE_ID_3 ((uint32_t)3)

// define endpoint id for test
#ifdef HAL_AP_CORE
#define RPMSG_RTT_REMOTE_TEST3_EPT_ID 0x3003U
#define RPMSG_RTT_REMOTE_TEST_EPT3_NAME "rpmsg-ap3-ch0"
#else
#define RPMSG_RTT_REMOTE_TEST3_EPT_ID 0x3004U
#define RPMSG_RTT_REMOTE_TEST_EPT3_NAME "rpmsg-mcu0-test"
#endif

#define RPMSG_RTT_TEST_MSG "Rockchip rpmsg linux test!"

/* TODO: These are defined in the linked script gcc_arm.ld.S */
extern uint32_t __linux_share_rpmsg_start__[];
extern uint32_t __linux_share_rpmsg_end__[];

#define RPMSG_LINUX_MEM_BASE ((uint32_t)&__linux_share_rpmsg_start__)
#define RPMSG_LINUX_MEM_END  ((uint32_t)&__linux_share_rpmsg_end__)
#define RPMSG_LINUX_MEM_SIZE (2UL * RL_VRING_OVERHEAD)

struct rpmsg_block_t
{
    uint32_t len;
    uint8_t buffer[496 - 4];
};

struct rpmsg_info_t
{
    struct rpmsg_lite_instance *instance;
    struct rpmsg_lite_endpoint *ept;
    uint32_t cb_sta;    // callback status flags
    void *private;
};

static void rpmsg_share_mem_check(void)
{
    if ((RPMSG_LINUX_MEM_BASE + RPMSG_LINUX_MEM_SIZE) > RPMSG_LINUX_MEM_END)
    {
        rt_kprintf("share memory size error!\n");
        while (1)
        {
            ;
        }
    }
}

rpmsg_ns_new_ept_cb rpmsg_ns_cb(uint32_t new_ept, const char *new_ept_name, uint32_t flags, void *user_data)
{
    uint32_t cpu_id;
    char ept_name[RL_NS_NAME_SIZE];

#ifdef HAL_AP_CORE
    cpu_id = HAL_CPU_TOPOLOGY_GetCurrentCpuId();
    printf("rpmsg remote: name service callback cpu_id-%ld\n", cpu_id);
#endif
    strncpy(ept_name, new_ept_name, RL_NS_NAME_SIZE);
    printf("rpmsg remote: new_ept-0x%lx name-%s\n", new_ept, ept_name);
}

rpmsg_queue_handle remote_queue;
struct rpmsg_info_t *info;
static void rpmsg_linux_test(void)
{
    int j;
    uint32_t master_id, remote_id;
    struct rpmsg_block_t *block;
    char *rx_msg = (char *)rt_malloc(RL_BUFFER_PAYLOAD_SIZE);
    uint32_t master_ept_id;
    uint32_t ept_flags;
    void *ns_cb_data;
   

    rpmsg_share_mem_check();
    master_id = MASTER_ID;
#ifdef HAL_AP_CORE
    remote_id = HAL_CPU_TOPOLOGY_GetCurrentCpuId();
    rt_kprintf("rpmsg remote: remote core cpu_id-%ld\n", remote_id);
#else
    remote_id = 4;
#endif

    info = malloc(sizeof(struct rpmsg_info_t));
    if (info == NULL)
    {
        rt_kprintf("info malloc error!\n");
        while (1)
        {
            ;
        }
    }
    info->private = malloc(sizeof(struct rpmsg_block_t));
    if (info->private == NULL)
    {
        rt_kprintf("info malloc error!\n");
        while (1)
        {
            ;
        }
    }

    //初始化rpmsg ept
    rt_kprintf("rpmsg remote: shmem_base-0x%lx shmem_end-%lx\n", RPMSG_LINUX_MEM_BASE, RPMSG_LINUX_MEM_END);
    //RPMsg-lite remote 端初始化
    info->instance = rpmsg_lite_remote_init((void *)RPMSG_LINUX_MEM_BASE, RL_PLATFORM_SET_LINK_ID(master_id, remote_id), RL_NO_FLAGS);
    rpmsg_lite_wait_for_link_up(info->instance, 10U);
    rt_kprintf("rpmsg remote: link up! link_id-0x%lx\n", info->instance->link_id);
    //绑定 name service ept（0x35这个ept id是专门给name service用于传新通道的名字）
    rpmsg_ns_bind(info->instance, rpmsg_ns_cb, &ns_cb_data);
    //RPMsg-lite 创建队列
    remote_queue  = rpmsg_queue_create(info->instance);
    //创建端点
    info->ept = rpmsg_lite_create_ept(info->instance, RPMSG_RTT_REMOTE_TEST3_EPT_ID, rpmsg_queue_rx_cb, remote_queue);
    ept_flags = RL_NS_CREATE;

    //声明 remote new ept name
    rpmsg_ns_announce(info->instance, info->ept, RPMSG_RTT_REMOTE_TEST_EPT3_NAME, ept_flags);
    
    /****************** rpmsg test run **************/
    // for (j = 0; j <= 100; j++)
    // {
    //     // rt_kprintf("%d\n",j);
    //     //接收到的数据自动复制到缓存区
    //     rpmsg_queue_recv(info->instance, remote_queue, (uint32_t *)&master_ept_id, rx_msg, RL_BUFFER_PAYLOAD_SIZE, &msg_len, RL_BLOCK);
    //     // rpmsg_queue_recv_nocopy(remote_rpmsg, remote_queue, (uint32_t *)&master_ept_id, (char **)&rx_msg, RL_NULL, RL_BLOCK);
    //     // rt_kprintf("rpmsg remote: master_ept_id-0x%lx rx_msg: %s\n", master_ept_id, rx_msg);
    //     //发送消息
    //     // rpmsg_lite_send(info->instance, info->ept, master_ept_id, RPMSG_RTT_TEST_MSG, strlen(RPMSG_RTT_TEST_MSG), RL_BLOCK);
    //     rpmsg_lite_send(info->instance, info->ept, master_ept_id, rx_msg, msg_len, RL_BLOCK);
    // }
    // rt_kprintf("rpmsg_lite_send 100-count ok.\n");
}

INIT_APP_EXPORT(rpmsg_linux_test);

void forlinx_rpmsg_test(void)
{
    uint32_t master_ept_id;
    char *rx_msg = (char *)rt_malloc(RL_BUFFER_PAYLOAD_SIZE);
    uint32_t msg_len;
    
    for (int j = 0; j <= 100; j++)
    {
        //接收到的数据自动复制到缓存区
        rpmsg_queue_recv(info->instance, remote_queue, (uint32_t *)&master_ept_id, rx_msg, RL_BUFFER_PAYLOAD_SIZE, &msg_len, RL_BLOCK);
        rt_kprintf("rpmsg remote: master_ept_id-0x%lx rx_msg: %d\n", master_ept_id, rx_msg[0]);
        //发送消息
        rpmsg_lite_send(info->instance, info->ept, master_ept_id, rx_msg, msg_len, RL_BLOCK);
    }
    rt_free(rx_msg);
}

MSH_CMD_EXPORT_ALIAS(forlinx_rpmsg_test, forlinx_rpmsg, rpmsg test);
