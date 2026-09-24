/**
  * Copyright (c) 2025 Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    vop2_utils.h
  * @version V0.1
  * @brief   vop2 helper functions
  *
  * Change Logs:
  * Date           Author          Notes
  * 2025-04-21     Damon Ding      first implementation
  *
  ******************************************************************************
  */

#ifndef __VOP2_UTILS_H__
#define __VOP2_UTILS_H__

/*******************************************************************************
 * Included Files
 ******************************************************************************/
#include "hal_base.h"

/*******************************************************************************
 * Pre-processor Definitions
 ******************************************************************************/
#define DRM_FORMAT_MAX_PLANES   4u

#define ROCKCHIP_TILED_BLOCK_SIZE_MASK      0xf
#define ROCKCHIP_TILED_BLOCK_SIZE_8x8       (1ULL)
#define ROCKCHIP_TILED_BLOCK_SIZE_4x4_MODE0 (2ULL)
#define ROCKCHIP_TILED_BLOCK_SIZE_4x4_MODE1 (3ULL)

/*******************************************************************************
 * Public Types
 ******************************************************************************/
/**
 * struct drm_format_info - information about a DRM format
 */
struct drm_format_info
{
    /** @format: 4CC format identifier (DRM_FORMAT_*) */
    uint32_t format;

    /**
     * @depth:
     *
     * Color depth (number of bits per pixel excluding padding bits),
     * valid for a subset of RGB formats only. This is a legacy field, do
     * not use in new code and set to 0 for new formats.
     */
    uint8_t depth;

    /** @num_planes: Number of color planes (1 to 3) */
    uint8_t num_planes;

    union
    {
        /**
         * @cpp:
         *
         * Number of bytes per pixel (per plane), this is aliased with
         * @char_per_block. It is deprecated in favour of using the
         * triplet @char_per_block, @block_w, @block_h for better
         * describing the pixel format.
         */
        uint8_t cpp[DRM_FORMAT_MAX_PLANES];

        /**
         * @char_per_block:
         *
         * Number of bytes per block (per plane), where blocks are
         * defined as a rectangle of pixels which are stored next to
         * each other in a byte aligned memory region. Together with
         * @block_w and @block_h this is used to properly describe tiles
         * in tiled formats or to describe groups of pixels in packed
         * formats for which the memory needed for a single pixel is not
         * byte aligned.
         *
         * @cpp has been kept for historical reasons because there are
         * a lot of places in drivers where it's used. In drm core for
         * generic code paths the preferred way is to use
         * @char_per_block, drm_format_info_block_width() and
         * drm_format_info_block_height() which allows handling both
         * block and non-block formats in the same way.
         *
         * For formats that are intended to be used only with non-linear
         * modifiers both @cpp and @char_per_block must be 0 in the
         * generic format table. Drivers could supply accurate
         * information from their drm_mode_config.get_format_info hook
         * if they want the core to be validating the pitch.
         */
        uint8_t char_per_block[DRM_FORMAT_MAX_PLANES];
    };

    /**
     * @block_w:
     *
     * Block width in pixels, this is intended to be accessed through
     * drm_format_info_block_width()
     */
    uint8_t block_w[DRM_FORMAT_MAX_PLANES];

    /**
     * @block_h:
     *
     * Block height in pixels, this is intended to be accessed through
     * drm_format_info_block_height()
     */
    uint8_t block_h[DRM_FORMAT_MAX_PLANES];

    /** @hsub: Horizontal chroma subsampling factor */
    uint8_t hsub;
    /** @vsub: Vertical chroma subsampling factor */
    uint8_t vsub;

    /** @has_alpha: Does the format embeds an alpha component? */
    bool has_alpha;

    /** @is_yuv: Is it a YUV format? */
    bool is_yuv;

    /** @is_color_indexed: Is it a color-indexed format? */
    bool is_color_indexed;
};

/*******************************************************************************
 * Public Data
 ******************************************************************************/

/*******************************************************************************
 * Inline Functions
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/
const struct drm_format_info *drm_format_info(uint32_t format);

#endif /* __VOP2_UTILS_H__ */
