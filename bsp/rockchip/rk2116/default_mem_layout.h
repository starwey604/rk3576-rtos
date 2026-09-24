/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#ifndef _MEM_LAYOUT_H_
#define _MEM_LAYOUT_H_

/* -------------------------------------------------------------------------- */
/* Notes:                                                                     */
/* 1. Users are encouraged to modify the "size" definitions as needed,        */
/*    the base addresses will automatically adjust to these changes.          */
/* 2. Always ensure that total allocated sizes do not exceed the physical     */
/*    memory size available on the device.                                    */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Physical Memory Sizes                                                      */
/* -------------------------------------------------------------------------- */
XIP_SIZE                    = 0x00400000; /* 4 MB - Total size of XIP memory */
SRAM_SIZE                   = 0x00140000; /* 1280 KB - Total size of SRAM    */
DRAM_SIZE                   = 0x01000000; /* 16 MB - Total size of DRAM      */

/* -------------------------------------------------------------------------- */
/* SRAM Memory Layout                                                         */
/* -------------------------------------------------------------------------- */
SRAM_BASE                   = 0x000f0000;

/* User-modifiable sizes */
SRAM_DSP_TCM_RSD0_SIZE      = 0x00010000; /* 64 KB */
SRAM_DSP0_SIZE              = 0x00020000; /* 128 KB */
SRAM_CPU0_RTT_SIZE          = 0x0007F000; /* 508 KB */
SRAM_TRANS_SIZE             = 0x00001000; /* 4 KB */
SRAM_DSP1_SIZE              = 0x00020000; /* 128 KB */
SRAM_DSP_TCM_RSD1_SIZE      = 0x00070000; /* 448 KB */

/* Automatically calculated base addresses for SRAM */
/* sram structure:
 *
 * reserved for dsp tcm
 * dsp0
 * rtt(if psram exist, run in psram)
 * trans data
 * dsp1
 * reserved for dsp tcm(default 0)
 * others, Can be covered
 * psram: 0x0200000
 * loader: 0x0208000
 * tfm: 0x0228000 or 0x08000000 if psram exist
 */
SRAM_DSP_TCM_RSD0_BASE      = SRAM_BASE;
SRAM_DSP0_BASE              = (SRAM_DSP_TCM_RSD0_BASE + SRAM_DSP_TCM_RSD0_SIZE);
SRAM_CPU0_RTT_BASE          = (SRAM_DSP0_BASE + SRAM_DSP0_SIZE);
SRAM_TRANS_BASE             = (SRAM_CPU0_RTT_BASE + SRAM_CPU0_RTT_SIZE);
SRAM_DSP1_BASE              = (SRAM_TRANS_BASE + SRAM_TRANS_SIZE);
SRAM_DSP_TCM_RSD1_BASE      = (SRAM_DSP1_BASE + SRAM_DSP1_SIZE)

/* -------------------------------------------------------------------------- */
/* DRAM Memory Layout                                                         */
/* -------------------------------------------------------------------------- */
DRAM_BASE                   = 0x08000000;

/* User-modifiable sizes */
DRAM_CPU0_TFM_SIZE          = 0x00100000; /* 1 MB */
DRAM_CPU0_RTT_SIZE          = 0x00500000; /* 5 MB */
DRAM_DSP0_SIZE              = 0x00500000; /* 5 MB */
DRAM_DSP1_SIZE              = 0x00500000; /* 5 MB */

/* Automatically calculated base addresses for DRAM */
DRAM_CPU0_TFM_BASE          = DRAM_BASE;
DRAM_CPU0_RTT_BASE          = (DRAM_CPU0_TFM_BASE + DRAM_CPU0_TFM_SIZE);
DRAM_DSP0_BASE              = (DRAM_CPU0_RTT_BASE + DRAM_CPU0_RTT_SIZE);
DRAM_DSP1_BASE              = (DRAM_DSP0_BASE + DRAM_DSP0_SIZE);

/* -------------------------------------------------------------------------- */
/* XIP Memory Layout                                                          */
/* -------------------------------------------------------------------------- */
XIP_BASE                    = 0x10000000;

/* Sizes - User-modifiable */
XIP_RKPARTITIONTABLE_SIZE   =  0x00010000; /* 64 KB */
XIP_IDBLOCK_SIZE            =  0x00020000; /* 128 KB */
XIP_CPU0_TFM_SIZE           =  0x00020000; /* 128 KB */
XIP_CPU0_RTT_SIZE           =  0x00040000; /* 256 KB */
XIP_DSP0_FIRMWARE_SIZE      =  0x00100000; /* 1 MB */
XIP_DSP1_FIRMWARE_SIZE      =  0x00100000; /* 1 MB */
XIP_DSP2_FIRMWARE_SIZE      =  0x00100000; /* 1 MB */
XIP_USER_DATA_SIZE          =  0x00020000; /* 128 KB */

/* Automatically calculated base addresses */
XIP_RKPARTITIONTABLE_BASE   = XIP_BASE;
XIP_IDBLOCK_BASE            = (XIP_RKPARTITIONTABLE_BASE + XIP_RKPARTITIONTABLE_SIZE);
XIP_CPU0_TFM_BASE           = (XIP_IDBLOCK_BASE + XIP_IDBLOCK_SIZE);
XIP_CPU0_RTT_BASE           = (XIP_CPU0_TFM_BASE + XIP_CPU0_TFM_SIZE);
XIP_DSP0_FIRMWARE_BASE      = (XIP_CPU0_RTT_BASE + XIP_CPU0_RTT_SIZE);
XIP_DSP1_FIRMWARE_BASE      = (XIP_DSP0_FIRMWARE_BASE + XIP_DSP0_FIRMWARE_SIZE);
XIP_DSP2_FIRMWARE_BASE      = (XIP_DSP1_FIRMWARE_BASE + XIP_DSP1_FIRMWARE_SIZE);
XIP_USER_DATA_BASE          = (XIP_DSP2_FIRMWARE_BASE + XIP_USER_DATA_SIZE);

/* -------------------------------------------------------------------------- */
/* DSP Stack Sizes                                                            */
/* -------------------------------------------------------------------------- */
/* User-modifiable sizes */
DSP0_STACK_SIZE             = 0x00001000; /* 4 KB */
DSP1_STACK_SIZE             = 0x00001000; /* 4 KB */

#endif /* _MEM_LAYOUT_H_ */
