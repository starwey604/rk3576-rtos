/* SPDX-License-Identifier: (GPL-2.0+ WITH Linux-syscall-note) OR MIT
 *
 * Rockchip ISP35
 * Copyright (C) 2025 Rockchip Electronics Co., Ltd.
 */

#ifndef _UAPI_RK_ISP35_CONFIG_H
#define _UAPI_RK_ISP35_CONFIG_H

// #include <linux/types.h>
// #include <linux/v4l2-controls.h>
#include "rk-isp33-config.h"

#define RKISP_CMD_GET_PARAMS_V35 \
    _IOR('V', BASE_VIDIOC_PRIVATE + 119, struct isp35_isp_params_cfg)

#define ISP35_MODULE_DPCC       ISP3X_MODULE_DPCC
#define ISP35_MODULE_BLS        ISP3X_MODULE_BLS
#define ISP35_MODULE_SDG        ISP3X_MODULE_SDG
#define ISP35_MODULE_LSC        ISP3X_MODULE_LSC
#define ISP35_MODULE_AWB_GAIN       ISP3X_MODULE_AWB_GAIN
#define ISP35_MODULE_BDM        ISP3X_MODULE_BDM
#define ISP35_MODULE_CCM        ISP3X_MODULE_CCM
#define ISP35_MODULE_GOC        ISP3X_MODULE_GOC
#define ISP35_MODULE_CPROC      ISP3X_MODULE_CPROC
#define ISP35_MODULE_IE         ISP3X_MODULE_IE
#define ISP35_MODULE_RAWAF      ISP3X_MODULE_RAWAF
#define ISP35_MODULE_RAWAE0     ISP3X_MODULE_RAWAE0
#define ISP35_MODULE_RAWAE1     ISP3X_MODULE_RAWAE1
#define ISP35_MODULE_RAWAE2     ISP3X_MODULE_RAWAE2
#define ISP35_MODULE_RAWAE3     ISP3X_MODULE_RAWAE3
#define ISP35_MODULE_RAWAWB     ISP3X_MODULE_RAWAWB
#define ISP35_MODULE_RAWHIST0       ISP3X_MODULE_RAWHIST0
#define ISP35_MODULE_RAWHIST1       ISP3X_MODULE_RAWHIST1
#define ISP35_MODULE_RAWHIST2       ISP3X_MODULE_RAWHIST2
#define ISP35_MODULE_RAWHIST3       ISP3X_MODULE_RAWHIST3
#define ISP35_MODULE_HDRMGE     ISP3X_MODULE_HDRMGE
#define ISP35_MODULE_RAWNR      ISP3X_MODULE_RAWNR
#define ISP35_MODULE_GIC        ISP3X_MODULE_GIC
#define ISP35_MODULE_DHAZ       ISP3X_MODULE_DHAZ
#define ISP35_MODULE_3DLUT      ISP3X_MODULE_3DLUT
#define ISP35_MODULE_LDCH       ISP3X_MODULE_LDCH
#define ISP35_MODULE_GAIN       ISP3X_MODULE_GAIN
#define ISP35_MODULE_DEBAYER        ISP3X_MODULE_DEBAYER
#define ISP35_MODULE_BAYNR      ISP3X_MODULE_BAYNR
#define ISP35_MODULE_BAY3D      ISP3X_MODULE_BAY3D
#define ISP35_MODULE_YNR        ISP3X_MODULE_YNR
#define ISP35_MODULE_CNR        ISP3X_MODULE_CNR
#define ISP35_MODULE_SHARP      ISP3X_MODULE_SHARP
#define ISP35_MODULE_DRC        ISP3X_MODULE_DRC
#define ISP35_MODULE_CAC        ISP3X_MODULE_CAC
#define ISP35_MODULE_CSM        ISP3X_MODULE_CSM
#define ISP35_MODULE_CGC        ISP3X_MODULE_CGC
#define ISP35_MODULE_RGBIR      ISP39_MODULE_RGBIR
#define ISP35_MODULE_HSV        ISP33_MODULE_HSV
#define ISP35_MODULE_ENH        ISP33_MODULE_ENH
#define ISP35_MODULE_HIST       ISP33_MODULE_HIST
#define ISP35_MODULE_AI         BIT_ULL(51)
#define ISP35_MODULE_AIAWB      BIT_ULL(52)
#define ISP35_MODULE_AWBSYNC        BIT_ULL(53)

#define ISP35_MODULE_FORCE      ISP3X_MODULE_FORCE

/* Measurement types */
#define ISP35_STAT_RAWAWB       ISP3X_STAT_RAWAWB
#define ISP35_STAT_RAWAF        ISP3X_STAT_RAWAF
#define ISP35_STAT_RAWAE0       ISP3X_STAT_RAWAE0
#define ISP35_STAT_RAWAE3       ISP3X_STAT_RAWAE3
#define ISP35_STAT_RAWHST0      ISP3X_STAT_RAWHST0
#define ISP35_STAT_RAWHST3      ISP3X_STAT_RAWHST3
#define ISP35_STAT_INFO2DDR     ISP33_STAT_INFO2DDR
#define ISP35_STAT_BAY3D        ISP33_STAT_BAY3D
#define ISP35_STAT_ENH          ISP33_STAT_ENH
#define ISP35_STAT_HIST         ISP33_STAT_HIST
#define ISP35_STAT_SHARP        ISP33_STAT_SHARP
#define ISP35_STAT_AIAWB        BIT(24)
#define ISP35_STAT_AWBSYNC      BIT(25)
#define ISP35_STAT_RTT_FST      ISP33_STAT_RTT_FST

#define ISP35_MESH_BUF_NUM      ISP3X_MESH_BUF_NUM

#define ISP35_LSC_GRAD_TBL_SIZE     ISP3X_LSC_GRAD_TBL_SIZE
#define ISP35_LSC_SIZE_TBL_SIZE     ISP3X_LSC_SIZE_TBL_SIZE
#define ISP35_LSC_DATA_TBL_SIZE     ISP3X_LSC_DATA_TBL_SIZE

#define ISP35_DEGAMMA_CURVE_SIZE    ISP3X_DEGAMMA_CURVE_SIZE

#define ISP35_GAIN_IDX_NUM      ISP3X_GAIN_IDX_NUM
#define ISP35_GAIN_LUT_NUM      ISP3X_GAIN_LUT_NUM

#define ISP35_RAWAWB_WEIGHT_NUM     ISP3X_RAWAWB_WEIGHT_NUM
#define ISP35_RAWAWB_HSTBIN_NUM     ISP3X_RAWAWB_HSTBIN_NUM
#define ISP35_RAWAWB_SUM_NUM        4
#define ISP35_RAWAWB_EXCL_STAT_NUM  4

#define ISP35_RAWAEBIG_SUBWIN_NUM   2

#define ISP35_RAWHIST_WEIGHT_NUM    225

#define ISP35_RAWAF_CURVE_NUM       ISP3X_RAWAF_CURVE_NUM
#define ISP35_RAWAF_HIIR_COE_NUM    ISP3X_RAWAF_HIIR_COE_NUM
#define ISP35_RAWAF_VFIR_COE_NUM    ISP3X_RAWAF_VFIR_COE_NUM
#define ISP35_RAWAF_WIN_NUM     ISP3X_RAWAF_WIN_NUM
#define ISP35_RAWAF_LINE_NUM        ISP3X_RAWAF_LINE_NUM
#define ISP35_RAWAF_GAMMA_NUM       ISP3X_RAWAF_GAMMA_NUM
#define ISP35_RAWAF_SUMDATA_NUM     ISP3X_RAWAF_SUMDATA_NUM
#define ISP35_RAWAF_VIIR_COE_NUM    3
#define ISP35_RAWAF_GAUS_COE_NUM    9

#define ISP35_DPCC_PDAF_POINT_NUM   ISP3X_DPCC_PDAF_POINT_NUM

#define ISP35_HDRMGE_WGT_NUM        17

#define ISP35_GIC_SIGMA_Y_NUM       ISP33_GIC_SIGMA_Y_NUM
#define ISP35_GIC_LUMA_DX_NUM       ISP33_GIC_LUMA_DX_NUM
#define ISP35_GIC_THRED_Y_NUM       ISP33_GIC_THRED_Y_NUM

#define ISP35_CCM_CURVE_NUM     18
#define ISP35_CCM_HF_FACTOR_NUM     17

#define ISP35_HSV_1DLUT_NUM     ISP33_HSV_1DLUT_NUM
#define ISP35_HSV_2DLUT_ROW     ISP33_HSV_2DLUT_ROW
#define ISP35_HSV_2DLUT_COL     ISP33_HSV_2DLUT_COL

#define ISP35_LDCH_BIC_NUM      ISP33_LDCH_BIC_NUM

#define ISP35_GAMMA_OUT_MAX_SAMPLES     ISP3X_GAMMA_OUT_MAX_SAMPLES

#define ISP35_ENH_LUMA_NUM      ISP33_ENH_LUMA_NUM
#define ISP35_ENH_DETAIL_NUM        ISP33_ENH_DETAIL_NUM
#define ISP35_ENH_IIR_ROW_MAX       ISP33_ENH_IIR_ROW_MAX
#define ISP35_ENH_IIR_COL_MAX       ISP33_ENH_IIR_COL_MAX

#define ISP35_HIST_ALPHA_NUM        ISP33_HIST_ALPHA_NUM
#define ISP35_HIST_THUMB_ROW_MAX    ISP33_HIST_THUMB_ROW_MAX
#define ISP35_HIST_THUMB_COL_MAX    ISP33_HIST_THUMB_COL_MAX
#define ISP35_HIST_IIR_NUM      ISP33_HIST_IIR_NUM
#define ISP35_HIST_IIR_BLK_MAX      ISP33_HIST_IIR_BLK_MAX

#define ISP35_DRC_Y_NUM         ISP3X_DRC_Y_NUM

#define ISP35_CNR_SIGMA_Y_NUM       ISP3X_CNR_SIGMA_Y_NUM
#define ISP35_CNR_GAUS_COE_NUM      6
#define ISP35_CNR_GAUS_SIGMAR_NUM   8
#define ISP35_CNR_WGT_SIGMA_Y_NUM   13
#define ISP35_CNR_CURVE_NUM     10

#define ISP35_YNR_XY_NUM        ISP3X_YNR_XY_NUM
#define ISP35_YNR_HI_GAUS1_COE_NUM  ISP33_YNR_HI_GAUS1_COE_NUM
#define ISP35_YNR_ADJ_NUM       ISP33_YNR_ADJ_NUM
#define ISP35_YNR_HI_GAUS_COE_NUM   4
#define ISP35_YNR_TEX2WGT_NUM       9

#define ISP35_BAY3D_XY_NUM      16
#define ISP35_BAY3D_TNRSIG_NUM      20
#define ISP35_BAY3D_LPF_COEFF_NUM   9
#define ISP35_BAY3D_FILT_COEFF_NUM  6

#define ISP35_AI_SIGMA_NUM      33
#define ISP35_VPSL_SIGMA_NUM           81

#define ISP35_SHARP_X_NUM       ISP33_SHARP_X_NUM
#define ISP35_SHARP_Y_NUM       ISP33_SHARP_Y_NUM
#define ISP35_SHARP_KERNEL_NUM      ISP33_SHARP_KERNEL_NUM
#define ISP35_SHARP_EDGE_KERNEL_NUM ISP33_SHARP_EDGE_KERNEL_NUM
#define ISP35_SHARP_EDGE_WGT_NUM    ISP33_SHARP_EDGE_WGT_NUM
#define ISP35_SHARP_LUMA_STRG_NUM   ISP33_SHARP_LUMA_STRG_NUM
#define ISP35_SHARP_CONTRAST_STRG_NUM   ISP33_SHARP_CONTRAST_STRG_NUM
#define ISP35_SHARP_TEX_CLIP_NUM    ISP33_SHARP_TEX_CLIP_NUM
#define ISP35_SHARP_LUM_CLIP_NUM    ISP33_SHARP_LUM_CLIP_NUM
#define ISP35_SHARP_HUE_NUM     ISP33_SHARP_HUE_NUM
#define ISP35_SHARP_DISATANCE_NUM   ISP33_SHARP_DISATANCE_NUM
#define ISP35_SHARP_TEX_NUM     ISP33_SHARP_HITEX_NUM
#define ISP35_SHARP_NOISE_CURVE_NUM ISP33_SHARP_NOISE_CURVE_NUM
#define ISP35_SHARP_SATURATION_NUM  9
#define ISP35_SHARP_LOCAL_STRG_NUM  4

#define ISP35_CAC_PSF_NUM       ISP33_CAC_PSF_NUM

#define ISP35_CSM_COEFF_NUM     ISP3X_CSM_COEFF_NUM

#define ISP35_DEBAYER_LUMA_NUM      7
#define ISP35_DEBAYER_DRCT_OFFSET_NUM   8
#define ISP35_DEBAYER_VSIGMA_NUM    8

#define ISP35_RGBIR_SCALE_NUM       4
#define ISP35_RGBIR_LUMA_POINT_NUM  17
#define ISP35_RGBIR_SCALE_MAP_NUM   17

#define ISP35_MEAN_BLK_X_NUM        15
#define ISP35_MEAN_BLK_Y_NUM        15

#define ISP35_AIAWB_FLT_COE_NUM     5

#define ISP35_AWBSYNC_WIN_MAX       3

struct isp35_bls_cfg
{
    uint8_t enable_auto;
    uint8_t en_windows;
    uint8_t bls1_en;

    uint8_t bls_samples;

    struct isp2x_window bls_window1;
    struct isp2x_window bls_window2;
    struct isp2x_bls_fixed_val fixed_val;
    struct isp2x_bls_fixed_val bls1_val;

    uint16_t isp_ob_offset;
    uint16_t isp_ob_offset1;
    uint16_t isp_ob_predgain;
    uint32_t isp_ob_max;
} __attribute__((packed));

struct isp35_hdrmge_cfg
{
    /* CTRL */
    uint8_t short_base_en;
    uint8_t frame_mode;
    uint8_t dbg_mode;
    uint8_t channel_detection_en;
    uint8_t s_base_mode;
    /* GAIN0 */
    uint16_t short_gain;
    uint16_t short_inv_gain;
    /* GAIN1 */
    uint16_t medium_gain;
    uint16_t medium_inv_gain;
    /* GAIN2 */
    uint8_t long_gain;
    /* LIGHTZ */
    uint8_t ms_diff_scale;
    uint8_t ms_diff_offset;
    uint8_t lm_diff_scale;
    uint8_t lm_diff_offset;
    /* MS_DIFF */
    uint16_t ms_abs_diff_scale;
    uint16_t ms_abs_diff_thred_min_limit;
    uint16_t ms_adb_diff_thred_max_limit;
    /* LM_DIFF */
    uint16_t lm_abs_diff_scale;
    uint16_t lm_abs_diff_thred_min_limit;
    uint16_t lm_abs_diff_thred_max_limit;
    /* DIFF_Y */
    uint16_t ms_luma_diff2wgt[ISP35_HDRMGE_WGT_NUM];
    uint16_t lm_luma_diff2wgt[ISP35_HDRMGE_WGT_NUM];
    /* OVER_Y */
    uint16_t luma2wgt[ISP35_HDRMGE_WGT_NUM];
    uint16_t ms_raw_diff2wgt[ISP35_HDRMGE_WGT_NUM];
    uint16_t lm_raw_diff2wgt[ISP35_HDRMGE_WGT_NUM];
    /* EACH_GAIN */
    uint16_t channel_detn_short_gain;
    uint16_t channel_detn_medium_gain;
    /* FORCE_LONG0 */
    uint16_t mid_luma_scale;
    /* FORCE_LONG1 */
    uint16_t mid_luma_thred_max_limit;
    uint16_t mid_luma_thred_min_limit;
} __attribute__((packed));

struct isp35_hsv_cfg
{
    uint8_t hsv_1dlut0_en;
    uint8_t hsv_1dlut1_en;
    uint8_t hsv_2dlut0_en;
    uint8_t hsv_2dlut1_en;
    uint8_t hsv_2dlut2_en;
    uint8_t hsv_2dlut12_cfg;

    uint8_t hsv_1dlut0_idx_mode;
    uint8_t hsv_1dlut1_idx_mode;
    uint8_t hsv_2dlut0_idx_mode;
    uint8_t hsv_2dlut1_idx_mode;
    uint8_t hsv_2dlut2_idx_mode;
    uint8_t hsv_1dlut0_item_mode;
    uint8_t hsv_1dlut1_item_mode;
    uint8_t hsv_2dlut0_item_mode;
    uint8_t hsv_2dlut1_item_mode;
    uint8_t hsv_2dlut2_item_mode;

    uint16_t lut0_1d[ISP35_HSV_1DLUT_NUM];
    uint16_t lut1_1d[ISP35_HSV_1DLUT_NUM];
    uint16_t lut0_2d[ISP35_HSV_2DLUT_ROW][ISP35_HSV_2DLUT_COL];
    uint16_t lut1_2d[ISP35_HSV_2DLUT_ROW][ISP35_HSV_2DLUT_COL];
    uint16_t lut2_2d[ISP35_HSV_2DLUT_ROW][ISP35_HSV_2DLUT_COL];
} __attribute__((packed));

struct isp35_debayer_cfg
{
    /* CONTROL */
    uint8_t bypass;
    uint8_t g_out_flt_en;
    uint8_t cnt_flt_en;
    /* LUMA_DX */
    uint8_t luma_dx[ISP35_DEBAYER_LUMA_NUM];
    /* G_INTERP */
    uint8_t g_interp_clip_en;
    uint8_t hi_texture_thred;
    uint8_t hi_drct_thred;
    uint8_t lo_drct_thred;
    uint8_t drct_method_thred;
    uint8_t g_interp_sharp_strg_max_limit;
    /* G_INTERP_FILTER1 */
    int8_t lo_drct_flt_coeff1;
    int8_t lo_drct_flt_coeff2;
    int8_t lo_drct_flt_coeff3;
    int8_t lo_drct_flt_coeff4;
    /* G_INTERP_FILTER2 */
    int8_t hi_drct_flt_coeff1;
    int8_t hi_drct_flt_coeff2;
    int8_t hi_drct_flt_coeff3;
    int8_t hi_drct_flt_coeff4;
    /* G_INTERP_OFFSET_ALPHA */
    uint16_t g_interp_sharp_strg_offset;
    uint8_t grad_lo_flt_alpha;
    /* G_INTERP_DRCT_OFFSET */
    uint16_t drct_offset[ISP35_DEBAYER_DRCT_OFFSET_NUM];
    /* G_FILTER_MODE_OFFSET */
    uint8_t gflt_mode;
    uint16_t gflt_ratio;
    uint16_t gflt_offset;
    /* G_FILTER_FILTER */
    int8_t gflt_coe0;
    int8_t gflt_coe1;
    int8_t gflt_coe2;
    /* G_FILTER_VSIGMA */
    uint16_t gflt_vsigma[ISP35_DEBAYER_VSIGMA_NUM];
    /* C_FILTER_GUIDE_GAUS */
    uint8_t cnr_lo_guide_lpf_coe0;
    uint8_t cnr_lo_guide_lpf_coe1;
    uint8_t cnr_lo_guide_lpf_coe2;
    /* C_FILTER_CE_GAUS */
    uint8_t cnr_pre_flt_coe0;
    uint8_t cnr_pre_flt_coe1;
    uint8_t cnr_pre_flt_coe2;
    /* C_FILTER_ALPHA_GAUS */
    uint8_t cnr_alpha_lpf_coe0;
    uint8_t cnr_alpha_lpf_coe1;
    uint8_t cnr_alpha_lpf_coe2;
    /* C_FILTER_LOG_OFFSET */
    uint16_t cnr_log_grad_offset;
    uint16_t cnr_log_guide_offset;
    uint8_t cnr_trans_en;
    /* C_FILTER_ALPHA */
    uint16_t cnr_moire_alpha_offset;
    uint32_t cnr_moire_alpha_scale;
    /* C_FILTER_EDGE */
    uint16_t cnr_edge_alpha_offset;
    uint32_t cnr_edge_alpha_scale;
    /* C_FILTER_IIR_0 */
    uint8_t cnr_lo_flt_strg_inv;
    uint8_t cnr_lo_flt_strg_shift;
    uint16_t cnr_lo_flt_wgt_slope;
    /* C_FILTER_IIR_1 */
    uint8_t cnr_lo_flt_wgt_max_limit;
    uint8_t cnr_lo_flt_wgt_min_thred;
    /* C_FILTER_BF */
    uint16_t cnr_hi_flt_vsigma;
    uint8_t cnr_hi_flt_wgt_min_limit;
    uint8_t cnr_hi_flt_cur_wgt;
} __attribute__((packed));

struct isp35_bay3d_cfg
{
    /* BAY3D_CTRL */
    uint8_t bypass_en;
    uint8_t iir_wr_src;
    uint8_t out_use_pre_mode;
    uint8_t motion_est_en;
    uint8_t iir_rw_fmt;
    /* BAY3D_CTRL1 */
    uint8_t transf_bypass_en;
    uint8_t tnrsigma_curve_double_en;
    uint8_t md_large_lo_use_mode;
    uint8_t md_large_lo_min_filter_bypass_en;
    uint8_t md_large_lo_gauss_filter_bypass_en;
    uint8_t md_large_lo_md_wgt_bypass_en;
    uint8_t pre_pix_out_mode;
    uint8_t motion_detect_bypass_en;
    uint8_t lpf_hi_bypass_en;
    uint8_t lo_diff_vfilt_bypass_en;
    uint8_t lpf_lo_bypass_en;
    uint8_t lo_wgt_hfilt_en;
    uint8_t lo_diff_hfilt_en;
    uint8_t sig_hfilt_en;
    uint8_t lo_detection_bypass_en;
    uint8_t lo_mge_wgt_mode;
    uint8_t pre_spnr_out_en;
    uint8_t md_only_lo_en;
    uint8_t cur_spnr_out_en;
    uint8_t md_wgt_out_en;
    /* BAY3D_CTRL2 */
    uint8_t cur_spnr_filter_bypass_en;
    uint8_t pre_spnr_hi_filter_gic_en;
    uint8_t pre_spnr_hi_filter_gic_enhance_en;
    uint8_t spnr_presigma_use_en;
    uint8_t pre_spnr_lo_filter_bypass_en;
    uint8_t pre_spnr_hi_filter_bypass_en;
    uint8_t pre_spnr_sigma_curve_double_en;
    uint8_t pre_spnr_hi_guide_filter_bypass_en;
    uint8_t pre_spnr_sigma_idx_filt_bypass_en;
    uint8_t pre_spnr_sigma_idx_filt_mode;
    uint8_t pre_spnr_hi_noise_ctrl_en;
    uint8_t pre_spnr_hi_filter_wgt_mode;
    uint8_t pre_spnr_lo_filter_wgt_mode;
    uint8_t pre_spnr_hi_filter_rb_wgt_mode;
    uint8_t pre_spnr_lo_filter_rb_wgt_mode;
    uint8_t pre_hi_gic_lp_en;
    uint8_t pre_hi_bf_lp_en;
    uint8_t pre_lo_avg_lp_en;
    uint8_t pre_spnr_dpc_flt_en;
    uint8_t pre_spnr_dpc_nr_bal_mode;
    uint8_t pre_spnr_dpc_flt_mode;
    uint8_t pre_spnr_dpc_flt_prewgt_en;
    /* BAY3D_CTRL3 */
    uint8_t transf_mode;
    uint8_t wgt_cal_mode;
    uint8_t mge_wgt_ds_mode;
    uint8_t kalman_wgt_ds_mode;
    uint8_t mge_wgt_hdr_sht_thred;
    uint8_t sigma_calc_mge_wgt_hdr_sht_thred;
    /* BAY3D_TRANS0 */
    uint16_t transf_mode_offset;
    uint8_t transf_mode_scale;
    uint16_t itransf_mode_offset;
    /* BAY3D_TRANS1 */
    uint32_t transf_data_max_limit;
    /* BAY3D_PREHI_SIGSCL */
    uint16_t pre_spnr_sigma_ctrl_scale;
    /* BAY3D_PREHI_SIGOF */
    uint8_t pre_spnr_hi_guide_out_wgt;
    /* BAY3D_CURHISPW */
    uint8_t cur_spnr_filter_coeff[ISP35_BAY3D_FILT_COEFF_NUM];
    /* BAY3D_IIRSX */
    uint16_t pre_spnr_luma2sigma_x[ISP35_BAY3D_XY_NUM];
    /* BAY3D_IIRSY */
    uint16_t pre_spnr_luma2sigma_y[ISP35_BAY3D_XY_NUM];
    /* BAY3D_PREHI_SIGSCL */
    uint16_t pre_spnr_hi_sigma_scale;
    /* BAY3D_PREHI_WSCL */
    uint8_t pre_spnr_hi_wgt_calc_scale;
    /* BAY3D_PREHIWMM */
    uint8_t pre_spnr_hi_filter_wgt_min_limit;
    uint8_t pre_spnr_hi_wgt_calc_offset;
    /* BAY3D_PREHISIGOF */
    uint8_t pre_spnr_hi_filter_out_wgt;
    uint8_t pre_spnr_sigma_offset;
    uint8_t pre_spnr_sigma_hdr_sht_offset;
    /* BAY3D_PREHISIGSCL */
    uint16_t pre_spnr_sigma_scale;
    uint16_t pre_spnr_sigma_hdr_sht_scale;
    /* BAY3D_PREHISPW */
    uint8_t pre_spnr_hi_filter_coeff[ISP35_BAY3D_FILT_COEFF_NUM];
    /* BAY3D_PRELOSIGCSL */
    uint16_t pre_spnr_lo_sigma_scale;
    /* BAY3D_PRELOSIGOF */
    uint8_t pre_spnr_lo_wgt_calc_offset;
    uint8_t pre_spnr_lo_wgt_calc_scale;
    /* BAY3D_PREHI_NRCT */
    uint16_t pre_spnr_hi_noise_ctrl_scale;
    uint8_t pre_spnr_hi_noise_ctrl_offset;
    /* BAY3D_TNRSX */
    uint16_t tnr_luma2sigma_x[ISP35_BAY3D_TNRSIG_NUM];
    /* BAY3D_TNRSY */
    uint16_t tnr_luma2sigma_y[ISP35_BAY3D_TNRSIG_NUM];
    /* BAY3D_HIWD */
    uint16_t lpf_hi_coeff[ISP35_BAY3D_LPF_COEFF_NUM];
    /* BAY3D_LOWD */
    uint16_t lpf_lo_coeff[ISP35_BAY3D_LPF_COEFF_NUM];
    /* BAY3D_GF */
    uint8_t sigma_idx_filt_coeff[ISP35_BAY3D_FILT_COEFF_NUM];
    uint16_t lo_wgt_cal_first_line_sigma_scale;
    /* BAY3D_VIIR */
    uint8_t lo_diff_vfilt_wgt;
    uint8_t lo_wgt_vfilt_wgt;
    uint8_t sig_first_line_scale;
    uint8_t lo_diff_first_line_scale;
    /* BAY3D_LFSCL */
    uint16_t lo_wgt_cal_offset;
    uint16_t lo_wgt_cal_scale;
    /* BAY3D_LFSCLTH */
    uint16_t lo_wgt_cal_max_limit;
    uint16_t mode0_base_ratio;
    /* BAY3D_DSWGTSCL */
    uint16_t lo_diff_wgt_cal_offset;
    uint16_t lo_diff_wgt_cal_scale;
    /* BAY3D_WGTLASTSCL */
    uint16_t lo_mge_pre_wgt_offset;
    uint16_t lo_mge_pre_wgt_scale;
    /* BAY3D_WGTSCL0 */
    uint16_t mode0_lo_wgt_scale;
    uint16_t mode0_lo_wgt_hdr_sht_scale;
    /* BAY3D_WGTSCL1 */
    uint16_t mode1_lo_wgt_scale;
    uint16_t mode1_lo_wgt_hdr_sht_scale;
    /* BAY3D_WGTSCL2 */
    uint16_t mode1_wgt_scale;
    uint16_t mode1_wgt_hdr_sht_scale;
    /* BAY3D_WGTOFF */
    uint16_t mode1_lo_wgt_offset;
    uint16_t mode1_lo_wgt_hdr_sht_offset;
    /* BAY3D_WGT1OFF */
    uint16_t auto_sigma_count_wgt_thred;
    uint16_t mode1_wgt_min_limit;
    uint16_t mode1_wgt_offset;
    /* BAY3D_SIGORG */
    uint32_t tnr_out_sigma_sq;
    /* BAY3D_WGTLO_L */
    uint16_t lo_wgt_clip_min_limit;
    uint16_t lo_wgt_clip_hdr_sht_min_limit;
    /* BAY3D_WGTLO_H */
    uint16_t lo_wgt_clip_max_limit;
    uint16_t lo_wgt_clip_hdr_sht_max_limit;
    /* BAY3D_STH_SCL */
    uint16_t lo_pre_gg_soft_thresh_scale;
    uint16_t lo_pre_rb_soft_thresh_scale;
    /* BAY3D_STH_LIMIT */
    uint16_t lo_pre_soft_thresh_max_limit;
    uint16_t lo_pre_soft_thresh_min_limit;
    /* BAY3D_HIKEEP */
    uint8_t cur_spnr_hi_wgt_min_limit;
    uint8_t pre_spnr_hi_wgt_min_limit;
    uint16_t motion_est_lo_wgt_thred;
    /* BAY3D_PIXMAX */
    uint16_t pix_max_limit;
    /* BAY3D_SIGNUMTH */
    uint32_t sigma_num_th;
    /* BAY3D_MONR */
    uint16_t out_use_hi_noise_bal_nr_strg;
    uint16_t out_use_md_noise_bal_nr_strg;
    uint8_t gain_out_max_limit;
    /* BAY3D_SIGSCL */
    uint16_t sigma_scale;
    uint16_t sigma_hdr_sht_scale;
    /* BAY3D_DSOFF */
    uint16_t lo_wgt_vfilt_offset;
    uint16_t lo_diff_vfilt_offset;
    uint8_t lo_wgt_cal_first_line_vfilt_wgt;
    /* BAY3D_DSSCL */
    uint8_t lo_wgt_vfilt_scale;
    uint8_t lo_diff_vfilt_scale_bit;
    uint8_t lo_diff_vfilt_scale;
    uint8_t lo_diff_first_line_vfilt_wgt;
    /* BAY3D_ME0 */
    uint16_t motion_est_up_mvx_cost_offset;
    uint16_t motion_est_up_mvx_cost_scale;
    uint8_t motion_est_sad_vert_wgt0;
    /* BAY3D_ME1 */
    uint16_t motion_est_up_left_mvx_cost_offset;
    uint16_t motion_est_up_left_mvx_cost_scale;
    uint8_t motion_est_sad_vert_wgt1;
    /* BAY3D_ME2 */
    uint16_t motion_est_up_right_mvx_cost_offset;
    uint16_t motion_est_up_right_mvx_cost_scale;
    uint8_t motion_est_sad_vert_wgt2;
    /* BAY3D_WGTMAX */
    uint16_t lo_wgt_clip_motion_max_limit;
    /* BAY3D_WGT1MAX */
    uint16_t mode1_wgt_max_limit;
    /* BAY3D_WGTM0 */
    uint16_t mode0_wgt_out_max_limit;
    uint16_t mode0_wgt_out_offset;
    /* BAY3D_LOCOEF0 */
    uint8_t lo_wgt_hflt_coeff2;
    uint8_t lo_wgt_hflt_coeff1;
    uint8_t lo_wgt_hflt_coeff0;
    uint8_t sig_hflt_coeff2;
    uint8_t sig_hflt_coeff1;
    uint8_t sig_hflt_coeff0;
    /* BAY3D_LOCOEF1 */
    uint8_t lo_dif_hflt_coeff2;
    uint8_t lo_dif_hflt_coeff1;
    uint8_t lo_dif_hflt_coeff0;
    /* BAY3D_DPC0 */
    uint8_t pre_spnr_dpc_bright_str;
    uint8_t pre_spnr_dpc_dark_str;
    uint8_t pre_spnr_dpc_str;
    uint8_t pre_spnr_dpc_wk_scale;
    uint8_t pre_spnr_dpc_wk_offset;
    /* BAY3D_DPC1 */
    uint16_t pre_spnr_dpc_nr_bal_str;
    uint16_t pre_spnr_dpc_soft_thr_scale;
    /* BAY3D_PRELOWGT */
    uint8_t pre_spnr_lo_val_wgt_out_wgt;
    uint8_t pre_spnr_lo_filter_out_wgt;
    uint8_t pre_spnr_lo_filter_wgt_min;
    /* BAY3D_MIDBIG0 */
    uint8_t md_large_lo_md_wgt_offset;
    uint16_t md_large_lo_md_wgt_scale;
    /* BAY3D_MIDBIG1 */
    uint16_t md_large_lo_wgt_cut_offset;
    uint16_t md_large_lo_wgt_add_offset;
    /* BAY3D_MIDBIG2 */
    uint16_t md_large_lo_wgt_scale;
    /* BAY3D_MONROFF */
    uint16_t out_use_hi_noise_bal_nr_off;
    uint16_t out_use_md_noise_bal_nr_off;

    /* B3DLDC_CTRL */
    uint8_t btnr_ldc_en;
    uint8_t b3dldcv_map13p3_en;
    uint8_t b3dldcv_force_map_en;
    /* B3DLDC_ADR_STS */
    uint8_t b3dldch_en;
    uint8_t b3dldch_map13p3_en;
    uint8_t b3dldch_force_map_en;
    /* B3DLDC_EXTBOUND1 */
    uint8_t btnr_ldcltp_mode;
    uint16_t btnr_ldc_wrap_ext_bound_offset;
    /* lut_ldch:offset data_oft; lut_ldcv:offset data1_oft */
    int32_t lut_buf_fd;
} __attribute__((packed));

struct isp35_ai_cfg
{
    /* CTRL */
    uint8_t aiisp_raw12_msb;
    uint8_t aiisp_gain_mode;
    uint8_t aiisp_curve_en;
    uint8_t aipre_iir_en;
    uint8_t aipre_iir2ddr_en;
    uint8_t aipre_gain_en;
    uint8_t aipre_gain2ddr_en;
    uint8_t aipre_luma2gain_dis;
    uint8_t aipre_nl_ddr_mode;
    uint8_t aipre_yraw_sel;
    uint8_t aipre_gain_bypass;
    uint8_t aipre_gain_mode;
    uint8_t aipre_narmap_inv;
    /* SIGMA_Y */
    uint16_t aiisp_sigma_y[ISP35_AI_SIGMA_NUM];
    /* AIPRE_NL_PRE */
    uint8_t aipre_scale;
    int8_t aipre_zp;
    uint16_t aipre_black_lvl;
    /* AIPRE_GAIN_PARA */
    uint8_t aipre_gain_alpha;
    uint8_t aipre_global_gain;
    uint16_t aipre_gain_ratio;
    /* AIPRE_SIGMA_CURVE */
    uint16_t aipre_sigma_y[ISP35_AI_SIGMA_NUM];
    /* AIPRE_NOISE0 */
    uint8_t aipre_noise_mot_offset;
    int8_t aipre_noise_mot_gain;
    uint16_t aipre_noise_luma_offset;
    /* AIPRE_NOISE1 */
    uint16_t aipre_noise_luma_gain;
    uint16_t aipre_noise_luma_clip;
    uint8_t aipre_noise_luma_static;
    /* AIPRE_NOISE2 */
    uint8_t aipre_nar_manual;
    uint8_t aipre_nar_manual_alpha;
    /* VPSL_PYR_CTRL */
    uint8_t pyr_yraw_mode;
    uint8_t pyr_sigma_en;
    uint8_t pyr_yraw_sel;
    uint8_t pyr_gain_leftshift;
    uint8_t pyr_blacklvl_sig;
    /* VPSL_PYR_SIGMA_LUT */
    uint8_t pyr_sigma_y[ISP35_VPSL_SIGMA_NUM];
} __attribute__((packed));

struct isp35_ynr_cfg
{
    /* GLOBAL_CTRL */
    uint8_t hi_spnr_bypass;
    uint8_t mi_spnr_bypass;
    uint8_t lo_spnr_bypass;
    uint8_t rnr_en;
    uint8_t tex2lo_strg_en;
    uint8_t hi_lp_en;
    uint8_t dsfilt_bypass;
    uint8_t tex2wgt_en;
    /* GAIN_CTRL */
    uint16_t global_set_gain;
    uint8_t gain_merge_alpha;
    uint8_t local_gain_scale;
    /* GAIN_ADJ */
    uint16_t lo_spnr_gain2strg[ISP35_YNR_ADJ_NUM];
    /* RNR_MAX_R */
    uint16_t rnr_max_radius;
    /* RNR_CENTER_COOR */
    uint16_t rnr_center_h;
    uint16_t rnr_center_v;
    /* RNR_STRENGTH */
    uint8_t radius2strg[ISP35_YNR_XY_NUM];
    /* SGM_DX */
    uint16_t luma2sima_x[ISP35_YNR_XY_NUM];
    /* SGM_Y */
    uint16_t luma2sima_y[ISP35_YNR_XY_NUM];
    /* MI_TEX2WGT_SCALE */
    uint8_t mi_spnr_tex2wgt_scale[ISP35_YNR_TEX2WGT_NUM];
    /* LO_TEX2WGT_SCALE */
    uint8_t lo_spnr_tex2wgt_scale[ISP35_YNR_TEX2WGT_NUM];
    /* HI_SIGMA_GAIN */
    uint16_t hi_spnr_sigma_min_limit;
    uint8_t hi_spnr_local_gain_alpha;
    uint16_t hi_spnr_strg;
    /* HI_GAUS_COE */
    uint8_t hi_spnr_filt_coeff[ISP35_YNR_HI_GAUS_COE_NUM];
    /* HI_WEIGHT */
    uint16_t hi_spnr_filt_wgt_offset;
    uint16_t hi_spnr_filt_center_wgt;
    /* HI_GAUS1_COE */
    uint16_t hi_spnr_filt1_coeff[ISP35_YNR_HI_GAUS1_COE_NUM];
    /* HI_TEXT */
    uint16_t hi_spnr_filt1_tex_thred;
    uint16_t hi_spnr_filt1_tex_scale;
    uint16_t hi_spnr_filt1_wgt_alpha;
    /* MI_GAUS_COE */
    uint8_t mi_spnr_filt_coeff0;
    uint8_t mi_spnr_filt_coeff1;
    uint8_t mi_spnr_filt_coeff2;
    uint8_t mi_spnr_filt_coeff3;
    uint8_t mi_spnr_filt_coeff4;
    /* MI_STRG_DETAIL */
    uint16_t mi_spnr_strg;
    uint16_t mi_spnr_soft_thred_scale;
    /* MI_WEIGHT */
    uint8_t mi_spnr_wgt;
    uint8_t mi_ehance_scale_en;
    uint8_t mi_ehance_scale;
    uint16_t mi_spnr_filt_center_wgt;
    /* DSIIR_COE */
    uint16_t dsfilt_diff_offset;
    uint16_t dsfilt_center_wgt;
    uint16_t dsfilt_strg;
    /* LO_STRG_DETAIL */
    uint16_t lo_spnr_strg;
    uint16_t lo_spnr_soft_thred_scale;
    /* LO_LIMIT_SCALE */
    uint16_t lo_spnr_thumb_thred_scale;
    uint16_t tex2lo_strg_mantissa;
    uint8_t tex2lo_strg_exponent;
    /* LO_WEIGHT */
    uint8_t lo_spnr_wgt;
    uint16_t lo_spnr_filt_center_wgt;
    uint8_t lo_enhance_scale;
    /* LO_TEXT_THRED */
    uint16_t tex2lo_strg_upper_thred;
    uint16_t tex2lo_strg_lower_thred;
    /* FUSION_WEIT_ADJ */
    uint8_t lo_gain2wgt[ISP35_YNR_ADJ_NUM];
} __attribute__((packed));

struct isp35_cnr_cfg
{
    /* CNR_CTRL */
    uint8_t exgain_bypass;
    uint8_t yuv422_mode;
    uint8_t thumb_mode;
    uint8_t uv_dis;
    uint8_t hiflt_wgt0_mode;
    uint8_t local_alpha_dis;
    uint8_t loflt_coeff;
    uint8_t hsv_alpha_en;
    /* CNR_EXGAIN */
    uint16_t global_gain;
    uint8_t global_gain_alpha;
    uint8_t local_gain_scale;
    /* CNR_THUMB1 */
    uint16_t lobfflt_vsigma_uv;
    uint16_t lobfflt_vsigma_y;
    /* CNR_THUMB_BF_RATIO */
    uint16_t lobfflt_alpha;
    /* CNR_LBF_WEITD */
    uint8_t thumb_bf_coeff0;
    uint8_t thumb_bf_coeff1;
    uint8_t thumb_bf_coeff2;
    uint8_t thumb_bf_coeff3;
    /* CNR_IIR_PARA1 */
    uint8_t loflt_uv_gain;
    uint8_t loflt_vsigma;
    uint8_t exp_x_shift_bit;
    uint16_t loflt_wgt_slope;
    /* CNR_IIR_PARA2 */
    uint8_t loflt_wgt_min_thred;
    uint8_t loflt_wgt_max_limit;
    /* CNR_GAUS_COE */
    uint8_t gaus_flt_coeff[ISP35_CNR_GAUS_COE_NUM];
    /* CNR_GAUS_RATIO */
    uint16_t gaus_flt_alpha;
    uint8_t hiflt_wgt_min_limit;
    uint16_t hiflt_alpha;
    /* CNR_BF_PARA1 */
    uint8_t hiflt_uv_gain;
    uint16_t hiflt_global_vsigma;
    uint8_t hiflt_cur_wgt;
    /* CNR_BF_PARA2 */
    uint16_t adj_offset;
    uint16_t adj_scale;
    /* CNR_SIGMA */
    uint8_t sgm_ratio[ISP35_CNR_SIGMA_Y_NUM];
    uint16_t bf_merge_max_limit;
    /* CNR_IIR_GLOBAL_GAIN */
    uint8_t loflt_global_sgm_ratio;
    uint8_t loflt_global_sgm_ratio_alpha;
    uint16_t bf_alpha_max_limit;
    /* CNR_WGT_SIGMA */
    uint8_t cur_wgt[ISP35_CNR_WGT_SIGMA_Y_NUM];
    /* GAUS_X_SIGMAR */
    uint16_t hiflt_vsigma_idx[ISP35_CNR_GAUS_SIGMAR_NUM];
    /* GAUS_Y_SIGMAR */
    uint16_t hiflt_vsigma[ISP35_CNR_GAUS_SIGMAR_NUM];
    /* IIR_SIGMAR */
    uint8_t lo_flt_vsigma[ISP35_CNR_WGT_SIGMA_Y_NUM];
    /* HSV_CURVE */
    uint8_t hsv_adj_alpha_table[ISP35_CNR_CURVE_NUM];
    /* SAT_CURVE */
    uint8_t sat_adj_alpha_table[ISP35_CNR_CURVE_NUM];
    /* GAIN_ADJ_CURVE */
    uint8_t gain_adj_alpha_table[ISP35_CNR_CURVE_NUM];
} __attribute__((packed));

struct isp35_sharp_cfg
{
    /* ctrl */
    uint8_t bypass;
    uint8_t local_gain_bypass;
    uint8_t tex_est_mode;
    uint8_t max_min_flt_mode;
    uint8_t detail_fusion_wgt_mode;
    uint8_t noise_calc_mode;
    uint8_t radius_step_mode;
    uint8_t noise_curve_mode;
    uint8_t gain_wgt_mode;
    uint8_t detail_lp_en;
    uint8_t debug_mode;
    /* TEXTURE0 */
    uint16_t fst_noise_scale;
    uint16_t fst_sigma_scale;
    /* TEXTURE1 */
    uint16_t fst_sigma_offset;
    uint16_t fst_wgt_scale;
    /* TEXTURE2 */
    uint8_t tex_wgt_mode;
    uint8_t noise_est_alpha;
    /* TEXTURE3 */
    uint16_t sec_noise_scale;
    uint16_t sec_sigma_scale;
    /* TEXTURE4 */
    uint16_t sec_sigma_offset;
    uint16_t sec_wgt_scale;
    /* HPF_KERNEL */
    uint8_t img_hpf_coeff[ISP35_SHARP_KERNEL_NUM];
    /* TEXFLT_KERNEL */
    uint8_t texWgt_flt_coeff0;
    uint8_t texWgt_flt_coeff1;
    uint8_t texWgt_flt_coeff2;
    /* DETAIL0 */
    uint8_t detail_in_alpha;
    uint8_t pre_bifilt_alpha;
    uint8_t fusion_wgt_min_limit;
    uint8_t fusion_wgt_max_limit;
    uint16_t pre_bifilt_slope_fix;
    /* LUMA_DX */
    uint8_t luma_dx[ISP35_SHARP_X_NUM];
    /* PBF_VSIGMA */
    uint16_t pre_bifilt_vsigma_inv[ISP35_SHARP_Y_NUM];
    /* PBF_KERNEL */
    uint8_t pre_bifilt_coeff0;
    uint8_t pre_bifilt_coeff1;
    uint8_t pre_bifilt_coeff2;
    /* DETAIL_KERNEL */
    uint8_t hi_detail_lpf_coeff[ISP35_SHARP_KERNEL_NUM];
    uint8_t mi_detail_lpf_coeff[ISP35_SHARP_KERNEL_NUM];
    /* GAIN */
    uint16_t global_gain;
    uint8_t gain_merge_alpha;
    uint8_t local_gain_scale;
    /* GAIN_ADJ0 */
    uint8_t edge_gain_max_limit;
    uint8_t edge_gain_min_limit;
    uint8_t detail_gain_max_limit;
    uint8_t detail_gain_min_limit;
    /* GAIN_ADJ1 */
    uint8_t hitex_gain_max_limit;
    uint8_t hitex_gain_min_limit;
    /* GAIN_ADJ2 */
    uint8_t edge_gain_slope;
    uint8_t detail_gain_slope;
    uint8_t hitex_gain_slope;
    /* GAIN_ADJ3 */
    uint16_t edge_gain_offset;
    uint16_t detail_gain_offset;
    uint16_t hitex_gain_offset;
    /* GAIN_ADJ4 */
    uint16_t edge_gain_sigma;
    uint16_t detail_gain_sigma;
    /* EDGE0 */
    uint16_t pos_edge_wgt_scale;
    uint16_t neg_edge_wgt_scale;
    /* EDGE1 */
    uint8_t pos_edge_strg;
    uint8_t neg_edge_strg;
    uint8_t overshoot_alpha;
    uint8_t undershoot_alpha;
    /* EDGE_KERNEL */
    uint8_t edge_bpf_coeff[ISP35_SHARP_EDGE_KERNEL_NUM];
    /* EDGE_WGT_VAL */
    uint16_t edge_wgt_val[ISP35_SHARP_EDGE_WGT_NUM];
    /* LUMA_ADJ_STRG */
    uint8_t luma2strg[ISP35_SHARP_LUMA_STRG_NUM];
    /* CENTER */
    uint16_t center_x;
    uint16_t center_y;
    /* OUT_LIMIT */
    uint16_t flat_max_limit;
    uint16_t edge_min_limit;
    /* TEX_X_INV_FIX */
    uint32_t tex_x_inv_fix0;
    uint32_t tex_x_inv_fix1;
    uint32_t tex_x_inv_fix2;
    /* LOCAL_STRG */
    uint16_t tex2loss_tex_in_hinr_strg[ISP35_SHARP_LOCAL_STRG_NUM];
    /* DETAIL_SCALE_TAB */
    uint8_t contrast2pos_strg[ISP35_SHARP_CONTRAST_STRG_NUM];
    uint8_t contrast2neg_strg[ISP35_SHARP_CONTRAST_STRG_NUM];
    uint8_t pos_detail_strg;
    uint8_t neg_detail_strg;
    /* DETAIL_TEX_CLIP */
    uint16_t tex2detail_pos_clip[ISP35_SHARP_TEX_CLIP_NUM];
    uint16_t tex2detail_neg_clip[ISP35_SHARP_TEX_CLIP_NUM];
    /* GRAIN_TEX_CLIP */
    uint16_t tex2grain_pos_clip[ISP35_SHARP_TEX_CLIP_NUM];
    uint16_t tex2grain_neg_clip[ISP35_SHARP_TEX_CLIP_NUM];
    /* DETAIL_LUMA_CLIP */
    uint16_t luma2detail_pos_clip[ISP35_SHARP_LUM_CLIP_NUM];
    uint16_t luma2detail_neg_clip[ISP35_SHARP_LUM_CLIP_NUM];
    /* GRAIN_STRG */
    uint8_t grain_strg;
    /* HUE_ADJ_TAB */
    uint16_t hue2strg[ISP35_SHARP_HUE_NUM];
    /* DISATANCE_ADJ */
    uint8_t distance2strg[ISP35_SHARP_DISATANCE_NUM];
    /* TEX2DETAIL_STRG */
    uint16_t tex2detail_strg[ISP35_SHARP_TEX_NUM];
    /* NOISE_SIGMA */
    uint16_t hi_tex_threshold[ISP35_SHARP_TEX_NUM];
    /* TEX2MFDETAIL_STRG */
    uint16_t tex2mf_detail_strg[ISP35_SHARP_TEX_NUM];
    /* LOSSTEXINHINR_STRG */
    uint8_t loss_tex_in_hinr_strg;
    /* NOISE_CURVE */
    uint16_t noise_curve_ext[ISP35_SHARP_NOISE_CURVE_NUM];
    uint8_t noise_count_thred_ratio;
    uint8_t noise_clip_scale;
    /* NOISE_CLIP */
    uint16_t noise_clip_min_limit;
    uint16_t noise_clip_max_limit;
    /* EDGEWGTFLT_KERNEL */
    uint8_t edge_wgt_flt_coeff0;
    uint8_t edge_wgt_flt_coeff1;
    uint8_t edge_wgt_flt_coeff2;
    /* EDGE_GLOBAL_CLIP */
    uint16_t edge_glb_clip_thred;
    uint16_t pos_edge_clip;
    uint16_t neg_edge_clip;
    /* MFDETAIL */
    uint8_t mf_detail_data_alpha;
    uint8_t pos_mf_detail_strg;
    uint8_t neg_mf_detail_strg;
    /* MFDETAIL_CLIP */
    uint16_t mf_detail_pos_clip;
    uint16_t sharp_mf_detail_neg_clip;
    /* SATURATION_STRG */
    uint8_t staturation2strg[ISP35_SHARP_SATURATION_NUM];
    uint16_t lo_saturation_strg;
} __attribute__((packed));

struct isp35_drc_cfg
{
    /* DRC_CTRL0 */
    uint8_t bypass_en;
    uint8_t cmps_byp_en;
    uint8_t gainx32_en;
    /* DRC_CTRL1 */
    uint16_t gain_idx_luma_scale;
    uint16_t comps_idx_luma_scale;
    uint8_t log_transform_offset_bits;
    /* DRC_LPRATIO */
    uint16_t lo_detail_ratio;
    uint16_t hi_detail_ratio;
    uint8_t adj_gain_idx_luma_scale;
    /* DRC_BILAT0 */
    uint8_t bifilt_wgt_offset;
    uint16_t thumb_thred_neg;
    uint8_t thumb_thred_en;
    uint8_t bifilt_cur_pixel_wgt;
    /* DRC_BILAT1 */
    uint8_t cmps_offset_bits;
    uint8_t cmps_mode;
    uint16_t filt_luma_soft_thred;
    /* DRC_BILAT2 */
    uint16_t thumb_max_limit;
    uint8_t thumb_scale;
    /* DRC_BILAT3 */
    uint16_t hi_range_inv_sigma;
    uint16_t lo_range_inv_sigma;
    /* DRC_BILAT4 */
    uint8_t bifilt_wgt;
    uint8_t bifilt_hi_wgt;
    uint16_t bifilt_soft_thred;
    uint8_t bifilt_soft_thred_en;
    /* DRC_GAIN_Y */
    uint16_t gain_y[ISP35_DRC_Y_NUM];
    /* DRC_COMPRES_Y */
    uint16_t compres_y[ISP35_DRC_Y_NUM];
    /* DRC_SCALE_Y */
    uint16_t scale_y[ISP35_DRC_Y_NUM];
    /* IIRWG_GAIN */
    uint16_t comps_gain_min_limit;
    /* SFTHD_Y */
    uint16_t sfthd_y[ISP35_DRC_Y_NUM];
    /* LUMA_MIX */
    uint8_t max_luma_wgt;
    uint8_t mid_luma_wgt;
    uint8_t min_luma_wgt;
} __attribute__((packed));

struct isp35_rawawb_meas_cfg
{
    uint8_t bls2_en;

    uint8_t rawawb_sel;
    uint8_t bnr2awb_sel;
    uint8_t drc2awb_sel;
    /* RAWAWB_CTRL */
    uint8_t uv_en0;
    uint8_t xy_en0;
    uint8_t yuv3d_en0;
    uint8_t yuv3d_ls_idx0;
    uint8_t yuv3d_ls_idx1;
    uint8_t yuv3d_ls_idx2;
    uint8_t yuv3d_ls_idx3;
    uint8_t in_rshift_to_12bit_en;
    uint8_t in_overexposure_check_en;
    uint8_t wind_size;
    uint8_t rawlsc_bypass_en;
    uint8_t light_num;
    uint8_t uv_en1;
    uint8_t xy_en1;
    uint8_t yuv3d_en1;
    uint8_t low12bit_val;
    /* RAWAWB_BLK_CTRL */
    uint8_t blk_measure_enable;
    uint8_t blk_measure_mode;
    uint8_t blk_measure_xytype;
    uint8_t blk_rtdw_measure_en;
    uint8_t blk_measure_illu_idx;
    uint8_t ds16x8_mode_en;
    uint8_t blk_with_luma_wei_en;
    uint8_t ovexp_2ddr_dis;
    uint8_t bnr_be_sel;
    uint16_t in_overexposure_threshold;
    /* RAWAWB_WIN_OFFS */
    uint16_t h_offs;
    uint16_t v_offs;
    /* RAWAWB_WIN_SIZE */
    uint16_t h_size;
    uint16_t v_size;
    /* RAWAWB_LIMIT_RG_MAX*/
    uint16_t r_max;
    uint16_t g_max;
    /* RAWAWB_LIMIT_BY_MAX */
    uint16_t b_max;
    uint16_t y_max;
    /* RAWAWB_LIMIT_RG_MIN */
    uint16_t r_min;
    uint16_t g_min;
    /* RAWAWB_LIMIT_BY_MIN */
    uint16_t b_min;
    uint16_t y_min;
    /* RAWAWB_WEIGHT_CURVE_CTRL */
    uint8_t wp_luma_wei_en0;
    uint8_t wp_luma_wei_en1;
    uint8_t wp_blk_wei_en0;
    uint8_t wp_blk_wei_en1;
    uint8_t wp_hist_xytype;
    /* RAWAWB_YWEIGHT_CURVE_XCOOR03 */
    uint8_t wp_luma_weicurve_y0;
    uint8_t wp_luma_weicurve_y1;
    uint8_t wp_luma_weicurve_y2;
    uint8_t wp_luma_weicurve_y3;
    /* RAWAWB_YWEIGHT_CURVE_XCOOR47 */
    uint8_t wp_luma_weicurve_y4;
    uint8_t wp_luma_weicurve_y5;
    uint8_t wp_luma_weicurve_y6;
    uint8_t wp_luma_weicurve_y7;
    /* RAWAWB_YWEIGHT_CURVE_XCOOR8 */
    uint8_t wp_luma_weicurve_y8;
    /* RAWAWB_YWEIGHT_CURVE_YCOOR03 */
    uint8_t wp_luma_weicurve_w0;
    uint8_t wp_luma_weicurve_w1;
    uint8_t wp_luma_weicurve_w2;
    uint8_t wp_luma_weicurve_w3;
    /* RAWAWB_YWEIGHT_CURVE_YCOOR47 */
    uint8_t wp_luma_weicurve_w4;
    uint8_t wp_luma_weicurve_w5;
    uint8_t wp_luma_weicurve_w6;
    uint8_t wp_luma_weicurve_w7;
    /* RAWAWB_YWEIGHT_CURVE_YCOOR8 */
    uint8_t wp_luma_weicurve_w8;
    uint16_t pre_wbgain_inv_r;
    /* RAWAWB_PRE_WBGAIN_INV */
    uint16_t pre_wbgain_inv_g;
    uint16_t pre_wbgain_inv_b;
    /* RAWAWB_UV_DETC_VERTEX0_0 */
    uint16_t vertex0_u_0;
    uint16_t vertex0_v_0;
    /* RAWAWB_UV_DETC_VERTEX1_0 */
    uint16_t vertex1_u_0;
    uint16_t vertex1_v_0;
    /* RAWAWB_UV_DETC_VERTEX2_0 */
    uint16_t vertex2_u_0;
    uint16_t vertex2_v_0;
    /* RAWAWB_UV_DETC_VERTEX3_0 */
    uint16_t vertex3_u_0;
    uint16_t vertex3_v_0;
    /* RAWAWB_UV_DETC_ISLOPE01_0 */
    uint32_t islope01_0;
    /* RAWAWB_UV_DETC_ISLOPE12_0 */
    uint32_t islope12_0;
    /* RAWAWB_UV_DETC_ISLOPE23_0 */
    uint32_t islope23_0;
    /* RAWAWB_UV_DETC_ISLOPE30_0 */
    uint32_t islope30_0;
    /* RAWAWB_UV_DETC_VERTEX0_1 */
    uint16_t vertex0_u_1;
    uint16_t vertex0_v_1;
    /* RAWAWB_UV_DETC_VERTEX1_1 */
    uint16_t vertex1_u_1;
    uint16_t vertex1_v_1;
    /* RAWAWB_UV_DETC_VERTEX2_1 */
    uint16_t vertex2_u_1;
    uint16_t vertex2_v_1;
    /* RAWAWB_UV_DETC_VERTEX3_1 */
    uint16_t vertex3_u_1;
    uint16_t vertex3_v_1;
    /* RAWAWB_UV_DETC_ISLOPE01_1 */
    uint32_t islope01_1;
    /* RAWAWB_UV_DETC_ISLOPE12_1 */
    uint32_t islope12_1;
    /* RAWAWB_UV_DETC_ISLOPE23_1 */
    uint32_t islope23_1;
    /* RAWAWB_UV_DETC_ISLOPE30_1 */
    uint32_t islope30_1;
    /* RAWAWB_UV_DETC_VERTEX0_2 */
    uint16_t vertex0_u_2;
    uint16_t vertex0_v_2;
    /* RAWAWB_UV_DETC_VERTEX1_2 */
    uint16_t vertex1_u_2;
    uint16_t vertex1_v_2;
    /* RAWAWB_UV_DETC_VERTEX2_2 */
    uint16_t vertex2_u_2;
    uint16_t vertex2_v_2;
    /* RAWAWB_UV_DETC_VERTEX3_2 */
    uint16_t vertex3_u_2;
    uint16_t vertex3_v_2;
    /* RAWAWB_UV_DETC_ISLOPE01_2 */
    uint32_t islope01_2;
    /* RAWAWB_UV_DETC_ISLOPE12_2 */
    uint32_t islope12_2;
    /* RAWAWB_UV_DETC_ISLOPE23_2 */
    uint32_t islope23_2;
    /* RAWAWB_UV_DETC_ISLOPE30_2 */
    uint32_t islope30_2;
    /* RAWAWB_UV_DETC_VERTEX0_3 */
    uint16_t vertex0_u_3;
    uint16_t vertex0_v_3;
    /* RAWAWB_UV_DETC_VERTEX1_3 */
    uint16_t vertex1_u_3;
    uint16_t vertex1_v_3;
    /* RAWAWB_UV_DETC_VERTEX2_3 */
    uint16_t vertex2_u_3;
    uint16_t vertex2_v_3;
    /* RAWAWB_UV_DETC_VERTEX3_3 */
    uint16_t vertex3_u_3;
    uint16_t vertex3_v_3;
    /* RAWAWB_UV_DETC_ISLOPE01_3 */
    uint32_t islope01_3;
    /* RAWAWB_UV_DETC_ISLOPE12_3 */
    uint32_t islope12_3;
    /* RAWAWB_UV_DETC_ISLOPE23_3 */
    uint32_t islope23_3;
    /* RAWAWB_UV_DETC_ISLOPE30_3 */
    uint32_t islope30_3;
    /* RAWAWB_YUV_RGB2ROTY_0 */
    uint16_t rgb2ryuvmat0_y;
    uint16_t rgb2ryuvmat1_y;
    /* RAWAWB_YUV_RGB2ROTY_1 */
    uint16_t rgb2ryuvmat2_y;
    uint16_t rgb2ryuvofs_y;
    /* RAWAWB_YUV_RGB2ROTU_0 */
    uint16_t rgb2ryuvmat0_u;
    uint16_t rgb2ryuvmat1_u;
    /* RAWAWB_YUV_RGB2ROTU_1 */
    uint16_t rgb2ryuvmat2_u;
    uint16_t rgb2ryuvofs_u;
    /* RAWAWB_YUV_RGB2ROTV_0 */
    uint16_t rgb2ryuvmat0_v;
    uint16_t rgb2ryuvmat1_v;
    /* RAWAWB_YUV_RGB2ROTV_1 */
    uint16_t rgb2ryuvmat2_v;
    uint16_t rgb2ryuvofs_v;
    /* RAWAWB_YUV_X_COOR_Y_0 */
    uint16_t coor_x1_ls0_y;
    uint16_t vec_x21_ls0_y;
    /* RAWAWB_YUV_X_COOR_U_0 */
    uint16_t coor_x1_ls0_u;
    uint16_t vec_x21_ls0_u;
    /* RAWAWB_YUV_X_COOR_V_0 */
    uint16_t coor_x1_ls0_v;
    uint16_t vec_x21_ls0_v;
    /* RAWAWB_YUV_X1X2_DIS_0 */
    uint8_t dis_x1x2_ls0;
    uint8_t rotu0_ls0;
    uint8_t rotu1_ls0;
    /* RAWAWB_YUV_INTERP_CURVE_UCOOR_0 */
    uint8_t rotu2_ls0;
    uint8_t rotu3_ls0;
    uint8_t rotu4_ls0;
    uint8_t rotu5_ls0;
    /* RAWAWB_YUV_INTERP_CURVE_TH0_0 */
    uint16_t th0_ls0;
    uint16_t th1_ls0;
    /* RAWAWB_YUV_INTERP_CURVE_TH1_0 */
    uint16_t th2_ls0;
    uint16_t th3_ls0;
    /* RAWAWB_YUV_INTERP_CURVE_TH2_0 */
    uint16_t th4_ls0;
    uint16_t th5_ls0;
    /* RAWAWB_YUV_X_COOR_Y_1 */
    uint16_t coor_x1_ls1_y;
    uint16_t vec_x21_ls1_y;
    /* RAWAWB_YUV_X_COOR_U_1 */
    uint16_t coor_x1_ls1_u;
    uint16_t vec_x21_ls1_u;
    /* RAWAWB_YUV_X_COOR_V_1 */
    uint16_t coor_x1_ls1_v;
    uint16_t vec_x21_ls1_v;
    /* RAWAWB_YUV_X1X2_DIS_1 */
    uint8_t dis_x1x2_ls1;
    uint8_t rotu0_ls1;
    uint8_t rotu1_ls1;
    /* YUV_INTERP_CURVE_UCOOR_1 */
    uint8_t rotu2_ls1;
    uint8_t rotu3_ls1;
    uint8_t rotu4_ls1;
    uint8_t rotu5_ls1;
    /* RAWAWB_YUV_INTERP_CURVE_TH0_1 */
    uint16_t th0_ls1;
    uint16_t th1_ls1;
    /* RAWAWB_YUV_INTERP_CURVE_TH1_1 */
    uint16_t th2_ls1;
    uint16_t th3_ls1;
    /* RAWAWB_YUV_INTERP_CURVE_TH2_1 */
    uint16_t th4_ls1;
    uint16_t th5_ls1;
    /* RAWAWB_YUV_X_COOR_Y_2 */
    uint16_t coor_x1_ls2_y;
    uint16_t vec_x21_ls2_y;
    /* RAWAWB_YUV_X_COOR_U_2 */
    uint16_t coor_x1_ls2_u;
    uint16_t vec_x21_ls2_u;
    /* RAWAWB_YUV_X_COOR_V_2 */
    uint16_t coor_x1_ls2_v;
    uint16_t vec_x21_ls2_v;
    /* RAWAWB_YUV_X1X2_DIS_2 */
    uint8_t dis_x1x2_ls2;
    uint8_t rotu0_ls2;
    uint8_t rotu1_ls2;
    /* YUV_INTERP_CURVE_UCOOR_2 */
    uint8_t rotu2_ls2;
    uint8_t rotu3_ls2;
    uint8_t rotu4_ls2;
    uint8_t rotu5_ls2;
    /* RAWAWB_YUV_INTERP_CURVE_TH0_2 */
    uint16_t th0_ls2;
    uint16_t th1_ls2;
    /* RAWAWB_YUV_INTERP_CURVE_TH1_2 */
    uint16_t th2_ls2;
    uint16_t th3_ls2;
    /* RAWAWB_YUV_INTERP_CURVE_TH2_2 */
    uint16_t th4_ls2;
    uint16_t th5_ls2;
    /* RAWAWB_YUV_X_COOR_Y_3 */
    uint16_t coor_x1_ls3_y;
    uint16_t vec_x21_ls3_y;
    /* RAWAWB_YUV_X_COOR_U_3 */
    uint16_t coor_x1_ls3_u;
    uint16_t vec_x21_ls3_u;
    /* RAWAWB_YUV_X_COOR_V_3 */
    uint16_t coor_x1_ls3_v;
    uint16_t vec_x21_ls3_v;
    /* RAWAWB_YUV_X1X2_DIS_3 */
    uint8_t dis_x1x2_ls3;
    uint8_t rotu0_ls3;
    uint8_t rotu1_ls3;
    /* RAWAWB_YUV_INTERP_CURVE_UCOOR_3 */
    uint8_t rotu2_ls3;
    uint8_t rotu3_ls3;
    uint8_t rotu4_ls3;
    uint8_t rotu5_ls3;
    /* RAWAWB_YUV_INTERP_CURVE_TH0_3 */
    uint16_t th0_ls3;
    uint16_t th1_ls3;
    /* RAWAWB_YUV_INTERP_CURVE_TH1_3 */
    uint16_t th2_ls3;
    uint16_t th3_ls3;
    /* RAWAWB_YUV_INTERP_CURVE_TH2_3 */
    uint16_t th4_ls3;
    uint16_t th5_ls3;
    /* CCM_COEFF0_R */
    uint16_t ccm_coeff0_r;
    uint16_t ccm_coeff1_r;
    /* CCM_COEFF1_R */
    uint16_t ccm_coeff2_r;
    /* CCM_COEFF0_G */
    uint16_t ccm_coeff0_g;
    uint16_t ccm_coeff1_g;
    /* CCM_COEFF1_G */
    uint16_t ccm_coeff2_g;
    /* CCM_COEFF0_B */
    uint16_t ccm_coeff0_b;
    uint16_t ccm_coeff1_b;
    /* CCM_COEFF1_B */
    uint16_t ccm_coeff2_b;
    /* RAWAWB_RGB2XY_WT01 */
    uint16_t wt0;
    uint16_t wt1;
    /* RAWAWB_RGB2XY_WT2 */
    uint16_t wt2;
    /* RAWAWB_RGB2XY0_MAT */
    uint16_t mat0_x;
    uint16_t mat0_y;
    /* RAWAWB_RGB2XY_MAT1_XY */
    uint16_t mat1_x;
    uint16_t mat1_y;
    /* RAWAWB_RGB2XY_MAT2_XY */
    uint16_t mat2_x;
    uint16_t mat2_y;
    /* RAWAWB_XY_DETC_NOR_X_0 */
    uint16_t nor_x0_0;
    uint16_t nor_x1_0;
    /* RAWAWB_XY_DETC_NOR_Y_0 */
    uint16_t nor_y0_0;
    uint16_t nor_y1_0;
    /* RAWAWB_XY_DETC_BIG_X_0 */
    uint16_t big_x0_0;
    uint16_t big_x1_0;
    /* RAWAWB_XY_DETC_BIG_Y_0 */
    uint16_t big_y0_0;
    uint16_t big_y1_0;
    /* RAWAWB_XY_DETC_NOR_X_1 */
    uint16_t nor_x0_1;
    uint16_t nor_x1_1;
    /* RAWAWB_XY_DETC_NOR_Y_1 */
    uint16_t nor_y0_1;
    uint16_t nor_y1_1;
    /* RAWAWB_XY_DETC_BIG_X_1 */
    uint16_t big_x0_1;
    uint16_t big_x1_1;
    /* RAWAWB_XY_DETC_BIG_Y_1 */
    uint16_t big_y0_1;
    uint16_t big_y1_1;
    /* RAWAWB_XY_DETC_NOR_X_2 */
    uint16_t nor_x0_2;
    uint16_t nor_x1_2;
    /* RAWAWB_XY_DETC_NOR_Y_2 */
    uint16_t nor_y0_2;
    uint16_t nor_y1_2;
    /* RAWAWB_XY_DETC_BIG_X_2 */
    uint16_t big_x0_2;
    uint16_t big_x1_2;
    /* RAWAWB_XY_DETC_BIG_Y_2 */
    uint16_t big_y0_2;
    uint16_t big_y1_2;
    /* RAWAWB_XY_DETC_NOR_X_3 */
    uint16_t nor_x0_3;
    uint16_t nor_x1_3;
    /* RAWAWB_XY_DETC_NOR_Y_3 */
    uint16_t nor_y0_3;
    uint16_t nor_y1_3;
    /* RAWAWB_XY_DETC_BIG_X_3 */
    uint16_t big_x0_3;
    uint16_t big_x1_3;
    /* RAWAWB_XY_DETC_BIG_Y_3 */
    uint16_t big_y0_3;
    uint16_t big_y1_3;
    /* RAWAWB_MULTIWINDOW_EXC_CTRL */
    uint8_t exc_wp_region0_excen;
    uint8_t exc_wp_region0_measen;
    uint8_t exc_wp_region0_domain;
    uint8_t exc_wp_region1_excen;
    uint8_t exc_wp_region1_measen;
    uint8_t exc_wp_region1_domain;
    uint8_t exc_wp_region2_excen;
    uint8_t exc_wp_region2_measen;
    uint8_t exc_wp_region2_domain;
    uint8_t exc_wp_region3_excen;
    uint8_t exc_wp_region3_measen;
    uint8_t exc_wp_region3_domain;
    uint8_t exc_wp_region4_excen;
    uint8_t exc_wp_region4_domain;
    uint8_t exc_wp_region5_excen;
    uint8_t exc_wp_region5_domain;
    uint8_t exc_wp_region6_excen;
    uint8_t exc_wp_region6_domain;
    uint8_t multiwindow_en;
    /* RAWAWB_MULTIWINDOW0_OFFS */
    uint16_t multiwindow0_h_offs;
    uint16_t multiwindow0_v_offs;
    /* RAWAWB_MULTIWINDOW0_SIZE */
    uint16_t multiwindow0_h_size;
    uint16_t multiwindow0_v_size;
    /* RAWAWB_MULTIWINDOW1_OFFS */
    uint16_t multiwindow1_h_offs;
    uint16_t multiwindow1_v_offs;
    /* RAWAWB_MULTIWINDOW1_OFFS */
    uint16_t multiwindow1_h_size;
    uint16_t multiwindow1_v_size;
    /* RAWAWB_MULTIWINDOW2_OFFS */
    uint16_t multiwindow2_h_offs;
    uint16_t multiwindow2_v_offs;
    /* RAWAWB_MULTIWINDOW2_SIZE */
    uint16_t multiwindow2_h_size;
    uint16_t multiwindow2_v_size;
    /* RAWAWB_MULTIWINDOW3_OFFS */
    uint16_t multiwindow3_h_offs;
    uint16_t multiwindow3_v_offs;
    /* RAWAWB_MULTIWINDOW3_SIZE */
    uint16_t multiwindow3_h_size;
    uint16_t multiwindow3_v_size;
    /* RAWAWB_EXC_WP_REGION0_XU */
    uint16_t exc_wp_region0_xu0;
    uint16_t exc_wp_region0_xu1;
    /* RAWAWB_EXC_WP_REGION0_YV */
    uint16_t exc_wp_region0_yv0;
    uint16_t exc_wp_region0_yv1;
    /* RAWAWB_EXC_WP_REGION1_XU */
    uint16_t exc_wp_region1_xu0;
    uint16_t exc_wp_region1_xu1;
    /* RAWAWB_EXC_WP_REGION1_YV */
    uint16_t exc_wp_region1_yv0;
    uint16_t exc_wp_region1_yv1;
    /* RAWAWB_EXC_WP_REGION2_XU */
    uint16_t exc_wp_region2_xu0;
    uint16_t exc_wp_region2_xu1;
    /* RAWAWB_EXC_WP_REGION2_YV */
    uint16_t exc_wp_region2_yv0;
    uint16_t exc_wp_region2_yv1;
    /* RAWAWB_EXC_WP_REGION3_XU */
    uint16_t exc_wp_region3_xu0;
    uint16_t exc_wp_region3_xu1;
    /* RAWAWB_EXC_WP_REGION3_YV */
    uint16_t exc_wp_region3_yv0;
    uint16_t exc_wp_region3_yv1;
    /* RAWAWB_EXC_WP_REGION4_XU */
    uint16_t exc_wp_region4_xu0;
    uint16_t exc_wp_region4_xu1;
    /* RAWAWB_EXC_WP_REGION4_YV */
    uint16_t exc_wp_region4_yv0;
    uint16_t exc_wp_region4_yv1;
    /* RAWAWB_EXC_WP_REGION5_XU */
    uint16_t exc_wp_region5_xu0;
    uint16_t exc_wp_region5_xu1;
    /* RAWAWB_EXC_WP_REGION5_YV */
    uint16_t exc_wp_region5_yv0;
    uint16_t exc_wp_region5_yv1;
    /* RAWAWB_EXC_WP_REGION6_XU */
    uint16_t exc_wp_region6_xu0;
    uint16_t exc_wp_region6_xu1;
    /* RAWAWB_EXC_WP_REGION6_YV */
    uint16_t exc_wp_region6_yv0;
    uint16_t exc_wp_region6_yv1;
    /* RAWAWB_EXC_WP_WEIGHT0_3 */
    uint8_t exc_wp_region0_weight;
    uint8_t exc_wp_region1_weight;
    uint8_t exc_wp_region2_weight;
    uint8_t exc_wp_region3_weight;
    /* RAWAWB_EXC_WP_WEIGHT4_6 */
    uint8_t exc_wp_region4_weight;
    uint8_t exc_wp_region5_weight;
    uint8_t exc_wp_region6_weight;
    /* RAWAWB_WRAM_DATA */
    uint8_t wp_blk_wei_w[ISP35_RAWAWB_WEIGHT_NUM];

    struct isp2x_bls_fixed_val bls2_val;
} __attribute__((packed));

struct isp35_aiawb_meas_cfg
{
    uint8_t bls3_en;
    /* CTRL0 */
    uint8_t ds_mode_config_en;
    uint8_t ds_mode;
    uint8_t rgb2w_mode;
    uint8_t rawout_sel;
    uint8_t path_sel;
    uint8_t in_shift;
    /* CTRL1 */
    uint8_t exp1_check_en;
    uint8_t exp_thr;
    uint16_t saturation_hthr;
    uint16_t saturation_lthr;
    /* WIN_OFFS */
    uint16_t h_offs;
    uint16_t v_offs;
    /* WIN_SIZE */
    uint16_t h_size;
    uint16_t v_size;
    /* FLT_COE */
    int8_t flt_coe[ISP35_AIAWB_FLT_COE_NUM];
    /* WBGAIN_INV0 */
    uint16_t wbgain_inv_g;
    uint16_t wbgain_inv_b;
    /* WBGAIN_INV1 */
    uint16_t wbgain_inv_r;
    uint16_t expand;
    /* MATRIX_SCALE */
    uint16_t ms00;
    uint16_t ms01;
    /* MATRIX_ROT0 */
    uint16_t mr00;
    uint16_t mr01;
    /* MATRIX_ROT1 */
    uint16_t mr10;
    uint16_t mr11;

    struct isp2x_bls_fixed_val bls3_val;
} __attribute__((packed));

struct isp35_awbsync_meas_cfg
{
    /* CTRL */
    uint8_t sumval_check_en;
    uint8_t sumval_mode;
    /* SCL */
    uint16_t scl_b;
    uint16_t scl_g;
    uint16_t scl_r;
    /* SUMVAL_MIN */
    uint16_t sumval_minb;
    uint16_t sumval_ming;
    uint16_t sumval_minr;
    /* SUMVAL_MAX */
    uint16_t sumval_maxb;
    uint16_t sumval_maxg;
    uint16_t sumval_maxr;
    /* WINDOW0_OFFS */
    uint16_t win0_h_offs;
    uint16_t win0_v_offs;
    /* WINDOW0_RD_COOR */
    uint16_t win0_r_coor;
    uint16_t win0_d_coor;
    /* WINDOW1_OFFS */
    uint16_t win1_h_offs;
    uint16_t win1_v_offs;
    /* WINDOW1_RD_COOR */
    uint16_t win1_r_coor;
    uint16_t win1_d_coor;
    /* WINDOW2_OFFS */
    uint16_t win2_h_offs;
    uint16_t win2_v_offs;
    /* WINDOW2_RD_COOR */
    uint16_t win2_r_coor;
    uint16_t win2_d_coor;
} __attribute__((packed));

struct isp35_rawaf_meas_cfg
{
    uint8_t rawaf_sel;
    uint8_t num_afm_win;
    uint8_t bnr2af_sel;

    /* CTRL */
    uint8_t gamma_en;
    uint8_t gaus_en;
    uint8_t hiir_en;
    uint8_t viir_en;
    uint8_t ldg_en;
    uint8_t h1_fv_mode;
    uint8_t h2_fv_mode;
    uint8_t v1_fv_mode;
    uint8_t v2_fv_mode;
    uint8_t ae_mode;
    uint8_t y_mode;
    uint8_t vldg_sel;
    uint8_t v_dnscl_mode;
    uint8_t from_ynr;
    uint8_t bnr_be_sel;
    uint8_t hiir_left_border_mode;
    uint8_t avg_ds_en;
    uint8_t avg_ds_mode;
    uint8_t h1_acc_mode;
    uint8_t h2_acc_mode;
    uint8_t v1_acc_mode;
    uint8_t v2_acc_mode;

    /* WINA_B */
    struct isp2x_window win[ISP39_RAWAF_WIN_NUM];

    /* CTRL1 */
    int16_t bls_offset;
    uint8_t bls_en;
    uint8_t aehgl_en;
    uint8_t hldg_dilate_num;
    uint8_t tnrin_shift;

    /* HVIIR_VAR_SHIFT */
    uint8_t h1iir_shift_wina;
    uint8_t h2iir_shift_wina;
    uint8_t v1iir_shift_wina;
    uint8_t v2iir_shift_wina;
    uint8_t h1iir_shift_winb;
    uint8_t h2iir_shift_winb;
    uint8_t v1iir_shift_winb;
    uint8_t v2iir_shift_winb;

    /* GAUS_COE */
    int8_t gaus_coe[ISP39_RAWAF_GAUS_COE_NUM];

    /* GAMMA_Y */
    uint16_t gamma_y[ISP39_RAWAF_GAMMA_NUM];
    /* HIIR_THRESH */
    uint16_t h_fv_thresh;
    uint16_t v_fv_thresh;
    struct isp3x_rawaf_curve curve_h[ISP39_RAWAF_CURVE_NUM];
    struct isp3x_rawaf_curve curve_v[ISP39_RAWAF_CURVE_NUM];
    int16_t h1iir1_coe[ISP39_RAWAF_HIIR_COE_NUM];
    int16_t h1iir2_coe[ISP39_RAWAF_HIIR_COE_NUM];
    int16_t h2iir1_coe[ISP39_RAWAF_HIIR_COE_NUM];
    int16_t h2iir2_coe[ISP39_RAWAF_HIIR_COE_NUM];
    int16_t v1iir_coe[ISP39_RAWAF_VIIR_COE_NUM];
    int16_t v2iir_coe[ISP39_RAWAF_VIIR_COE_NUM];
    int16_t v1fir_coe[ISP39_RAWAF_VFIR_COE_NUM];
    int16_t v2fir_coe[ISP39_RAWAF_VFIR_COE_NUM];
    /* HIGHLIT_THRESH */
    uint16_t highlit_thresh;

    /* CORING_H */
    uint16_t h_fv_limit;
    uint16_t h_fv_slope;
    /* CORING_V */
    uint16_t v_fv_limit;
    uint16_t v_fv_slope;
} __attribute__((packed));

struct isp35_rawae_meas_cfg
{
    uint8_t rawae_sel;
    uint8_t bnr2ae_sel;

    uint8_t wnd_num;
    uint8_t wnd1_en;
    uint8_t debug_en;
    uint8_t bnr_be_sel;

    uint16_t win0_h_offset;
    uint16_t win0_v_offset;
    uint16_t win0_h_size;
    uint16_t win0_v_size;
    uint16_t win1_h_offset;
    uint16_t win1_v_offset;
    uint16_t win1_h_size;
    uint16_t win1_v_size;
} __attribute__((packed));

struct isp35_rawhist_meas_cfg
{
    uint8_t stepsize;
    uint8_t debug_en;
    uint8_t mode;
    uint8_t data_sel;
    uint8_t wnd_num;
    uint16_t waterline;

    uint8_t rcc;
    uint8_t gcc;
    uint8_t bcc;
    uint8_t off;

    uint16_t h_offset;
    uint16_t v_offset;
    uint16_t h_size;
    uint16_t v_size;

    uint8_t weight[ISP35_RAWHIST_WEIGHT_NUM];
} __attribute__((packed));

struct isp35_isp_other_cfg
{
    struct isp39_rgbir_cfg rgbir_cfg;
    struct isp35_bls_cfg bls_cfg;
    struct isp32_awb_gain_cfg awb_gain_cfg;
    struct isp39_dpcc_cfg dpcc_cfg;
    struct isp35_hdrmge_cfg hdrmge_cfg;
    struct isp3x_gain_cfg gain_cfg;
    struct isp35_bay3d_cfg bay3d_cfg;
    struct isp35_ai_cfg ai_cfg;

    struct isp33_cac_cfg cac_cfg;
    struct isp3x_lsc_cfg lsc_cfg;

    struct isp35_debayer_cfg debayer_cfg;
    struct isp35_drc_cfg drc_cfg;
    struct isp33_ccm_cfg ccm_cfg;
    struct isp3x_gammaout_cfg gammaout_cfg;
    struct isp35_hsv_cfg hsv_cfg;
    struct isp21_csm_cfg csm_cfg;
    struct isp33_gic_cfg gic_cfg;
    struct isp35_cnr_cfg cnr_cfg;
    struct isp35_ynr_cfg ynr_cfg;
    struct isp35_sharp_cfg sharp_cfg;
    struct isp33_enh_cfg enh_cfg;
    struct isp33_hist_cfg hist_cfg;
    struct isp32_ldch_cfg ldch_cfg;
    struct isp21_cgc_cfg cgc_cfg;
    struct isp2x_cproc_cfg cproc_cfg;
} __attribute__((packed));

struct isp35_isp_meas_cfg
{
    struct isp35_rawae_meas_cfg rawae0;
    struct isp35_rawhist_meas_cfg rawhist0;
    struct isp35_rawae_meas_cfg rawae3;
    struct isp35_rawhist_meas_cfg rawhist3;
    struct isp35_rawawb_meas_cfg rawawb;
    struct isp35_rawaf_meas_cfg rawaf;
    struct isp35_aiawb_meas_cfg aiawb;
    struct isp35_awbsync_meas_cfg awbsync;
} __attribute__((packed));

struct isp35_isp_params_cfg
{
    uint64_t module_en_update;
    uint64_t module_ens;
    uint64_t module_cfg_update;

    uint32_t frame_id;
    struct isp35_isp_meas_cfg meas;
    struct isp35_isp_other_cfg others;
    struct sensor_exposure_cfg exposure;
} __attribute__((packed));

struct rkisp35_thunderboot_resmem_head
{
    struct rkisp_thunderboot_resmem_head head;
    struct isp35_isp_params_cfg cfg;
} __attribute__((packed));

struct isp35_awbsync_stat
{
    uint64_t sumr[ISP35_AWBSYNC_WIN_MAX];
    uint64_t sumg[ISP35_AWBSYNC_WIN_MAX];
    uint64_t sumb[ISP35_AWBSYNC_WIN_MAX];
    uint64_t sump[ISP35_AWBSYNC_WIN_MAX];
} __attribute__((packed));

struct isp35_stat
{
    /* mean to ddr */
    struct isp33_rawae_stat rawae3;
    struct isp33_rawhist_stat rawhist3;
    struct isp33_rawae_stat rawae0;
    struct isp33_rawhist_stat rawhist0;
    struct isp39_rawaf_stat rawaf;
    struct isp33_rawawb_stat rawawb;
    /* ahb read reg */
    struct isp33_bay3d_stat bay3d;
    struct isp33_sharp_stat sharp;
    struct isp33_enh_stat enh;
    struct isp33_hist_stat hist;
    struct isp35_awbsync_stat awbsync;
    struct isp32_info2ddr_stat info2ddr;

    int buf_aiawb_index;
    int buf_bay3d_iir_index;
    int buf_bay3d_ds_index;
    int buf_bay3d_wgt_index;
    int buf_gain_index;
    int buf_aipre_gain_index;
    int buf_vpsl_index;
} __attribute__((packed));

struct rkisp35_stat_buffer
{
    struct isp35_stat stat;
    uint32_t meas_type;
    uint32_t frame_id;
    uint32_t params_id;
} __attribute__((packed));
#endif /* _UAPI_RK_ISP35_CONFIG_H */
