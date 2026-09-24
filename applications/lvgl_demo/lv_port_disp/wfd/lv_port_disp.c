/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
*/

#include <stdlib.h>

#include <rtthread.h>

#include <wfd.h>
#include <wfdext.h>

#include "lv_port_disp.h"

#define MAX_DEVICES             1
#define MAX_BUFFER_COUNT        2
#define NUMBER_TEST_LOOPS       1
#define SIZE_DEV_ATTRIBS        3
#define DEFAULT_DISPLAY_ID      1

#define BORDER_COLOR            0x00FFFFFF /* (RRGGBBXX) */

#define MAX_PORTS_SUPPORTED         4
#define MAX_PIPELINES_SUPPORTED     8
#define MAX_PIPELINE_FMTS_SUPPORTED 16

#ifdef RT_LV_COLOR_DEPTH_32
#define DEFAULT_RGB_PIXEL_FORMAT    WFD_FORMAT_RGBA8888
#elif defined(RT_LV_COLOR_DEPTH_16)
#define DEFAULT_RGB_PIXEL_FORMAT    WFD_FORMAT_RGB565
#else
#error "Only support 16-bits or 32-bits"
#endif

#define DEFAULT_YUV_PIXEL_FORMAT    WFD_FORMAT_NV12

#define CHECK_RESULT(x, log, tag) {if (!(x)) {rt_kprintf(log"\n"); goto tag;}}
//#define CHECK_RESULT(x, log, tag) RT_ASSERT(x)

struct wfd_display
{
    int id;
    WFDDevice dev;
    WFDPort port;
    int width;
    int height;
    int connected;
    int type;
    int pipeline_cnt;
};

struct wfd_win
{
    WFDPipeline pipeline;
    int pipeline_id;
    int format;
    int stride_pix;
    int src_x;
    int src_y;
    int src_w;
    int src_h;
    int dst_x;
    int dst_y;
    int dst_w;
    int dst_h;
    WFDEGLImage eglImage[MAX_BUFFER_COUNT];
    win_image_t *image[MAX_BUFFER_COUNT];
    WFDSource source[MAX_BUFFER_COUNT];
    int commitSourceIdx;
};

struct wfd_lv_ctx
{
    /* For WFD */
    struct wfd_display *display;
    struct wfd_win *win;
    void *disp_buf;
    int disp_buf_stride;

    /* For LVGL */
    lv_disp_draw_buf_t draw_buf_dsc;
    lv_disp_drv_t disp_drv;
    void *lv_buf;
};

static struct wfd_lv_ctx lv_ctx;

static rt_err_t wfd_setup(struct wfd_lv_ctx *ctx)
{
    struct wfd_display *display = NULL;
    struct wfd_win *win = NULL;

    WFDint             numDevs         = 0;
    WFDint             numPorts        = 0;
    WFDint             numPipelines    = 0;
    WFDint             numPipelineFmts = 0;
    WFDint             numPortModes    = 0;
    WFDint             phy_width       = 0;
    WFDint             phy_height      = 0;
    WFDint             rect[4]         = { 0, 0, 0, 0 };
    WFDint             iBorderColor    = BORDER_COLOR;
    WFDint             attribValue     = 0;
    WFDErrorCode       eError          = WFD_ERROR_NONE;

    WFDint             usage           = WFD_USAGE_WRITE;

    WFDint             devIds[1];
    WFDint             portIds[MAX_PORTS_SUPPORTED];
    WFDint             pipelineIds[MAX_PIPELINES_SUPPORTED];
    WFDint             pipelineFmts[MAX_PIPELINE_FMTS_SUPPORTED];
    WFDPortMode        portModes[MAX_PORTS_SUPPORTED];
    WFDPipeline        pipeline;

    display = calloc(1, sizeof(*display));
    CHECK_RESULT(display != NULL, "create display error", err);

    win = calloc(1, sizeof(*win));
    CHECK_RESULT(win != NULL, "create win error", err);

    display->id = DEFAULT_DISPLAY_ID;
    win->format = DEFAULT_RGB_PIXEL_FORMAT;

    numDevs = wfdEnumerateDevices(NULL, 0, NULL);
    if (numDevs)
    {
        wfdEnumerateDevices(devIds, numDevs, NULL);
        for (int i = 0; i < numDevs; i++)
        {
            rt_kprintf("devIds[%ld]=%ld", i, devIds[i]);
        }
    }

    display->dev = wfdCreateDevice(WFD_DEFAULT_DEVICE_ID, NULL);
    CHECK_RESULT(display->dev != WFD_INVALID_HANDLE,
                 "create device failed", err);

    attribValue = wfdGetDeviceAttribi(display->dev, WFD_DEVICE_ID);
    rt_kprintf("device attribi = %d\n", attribValue);

    numPorts = wfdEnumeratePorts(display->dev, NULL, 0, NULL);
    CHECK_RESULT(numPorts > 0, "get ports failed", err);

    wfdEnumeratePorts(display->dev, portIds, numPorts, NULL);
    for (int i = 0; i < numPorts; i++)
    {
        rt_kprintf("portIds[%ld]=%ld\n", i, portIds[i]);
    }

    display->port = wfdCreatePort(display->dev, portIds[0], NULL);
    CHECK_RESULT(display->port != WFD_INVALID_HANDLE,
                 "create ports failed", err);

    numPortModes = wfdGetPortModes(display->dev, display->port, NULL, 0);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "get modes failed", err);

    wfdGetPortModes(display->dev, display->port, portModes, numPortModes);
    wfdSetPortMode(display->dev, display->port, portModes[0]);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "set modes failed", err);

    phy_width = wfdGetPortModeAttribi(display->dev, display->port,
                                      portModes[0], WFD_PORT_MODE_WIDTH);
    phy_height = wfdGetPortModeAttribi(display->dev, display->port,
                                       portModes[0], WFD_PORT_MODE_HEIGHT);

    display->width = phy_width;
    display->height = phy_height;
    win->src_w = phy_width;
    win->dst_w = win->src_w;
    win->src_h = phy_height;
    win->dst_h = win->src_h;

    wfdSetPortAttribi(display->dev, display->port, WFD_PORT_POWER_MODE,
                      WFD_POWER_MODE_ON);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "set power on failed", err);

    wfdSetPortAttribi(display->dev, display->port, WFD_PORT_BACKGROUND_COLOR,
                      iBorderColor);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "set bg color failed", err);

    numPipelines = wfdGetPortAttribi(display->dev, display->port,
                                     WFD_PORT_PIPELINE_ID_COUNT);
    wfdGetPortAttribiv(display->dev, display->port,
                       WFD_PORT_BINDABLE_PIPELINE_IDS,
                       numPipelines, pipelineIds);
    rt_kprintf("numPipelines=%ld\n", numPipelines);

    for (int i = 0; i < numPipelines; i++)
    {
        rt_kprintf("pipelineIds[%ld]=%ld\n", i, pipelineIds[i]);
        pipeline = wfdCreatePipeline(display->dev, pipelineIds[i], NULL);
        CHECK_RESULT(pipeline != WFD_INVALID_HANDLE,
                     "create pipeline failed", err);
        numPipelineFmts = wfdGetPipelineAttribi(display->dev, pipeline,
                                                WFD_PIPELINE_FORMAT_COUNT_ROCKCHIP);
        wfdGetPipelineAttribiv(display->dev, pipeline,
                               WFD_PIPELINE_FORMATS_ROCKCHIP,
                               numPipelineFmts, pipelineFmts);
        for (int j = 0; j < numPipelineFmts; j++)
        {
            rt_kprintf("pipelineFmts[%ld]=%ld\n", j, pipelineFmts[j]);
            if (win->format == pipelineFmts[j])
            {
                win->pipeline = pipeline;
                break;
            }
        }

        if (win->pipeline)
            break;

        wfdDestroyPipeline(display->dev, pipeline);
    }

    wfdBindPipelineToPort(display->dev, display->port, win->pipeline);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "bind pipeline failed", err);

    for (int i = 0; i < MAX_BUFFER_COUNT; i++)
    {
        /* Create RGB EGL image */
        wfdCreateWFDEGLImages(display->dev, win->src_w, win->src_h,
                              win->format, usage, 1, &(win->eglImage[i]));
        eError = wfdGetError(display->dev);
        CHECK_RESULT(eError == WFD_ERROR_NONE, "create image failed", err);

        win->image[i] = (win_image_t *)(win->eglImage[i]);
        CHECK_RESULT(win->image[i] != NULL, "eglImage is NULL", err);

        /* Create RGB source */
        win->source[i] = wfdCreateSourceFromImage(display->dev, win->pipeline,
                         win->image[i], NULL);
        CHECK_RESULT(win->source[i] != WFD_INVALID_HANDLE,
                     "create source failed", err);
    }

    ctx->disp_buf = malloc(win->image[0]->size);
    CHECK_RESULT(ctx->disp_buf != NULL, "create disp_buf failed", err);
    ctx->disp_buf_stride = win->image[0]->strides[0] / (LV_COLOR_DEPTH >> 3);

    wfdDeviceCommit(display->dev, WFD_COMMIT_ENTIRE_PORT, display->port);
    eError = wfdGetError(display->dev);
    CHECK_RESULT(eError == WFD_ERROR_NONE, "commit failed", err);

    rect[0] = 0;
    rect[1] = 0;
    rect[2] = win->src_w;
    rect[3] = win->src_h;
    wfdSetPipelineAttribiv(display->dev, win->pipeline,
                           WFD_PIPELINE_SOURCE_RECTANGLE, 4, rect);
    CHECK_RESULT(eError == WFD_ERROR_NONE,
                 "set source rectangle failed", err);

    rect[0] = 0;
    rect[1] = 0;
    rect[2] = win->dst_w;
    rect[3] = win->dst_h;
    wfdSetPipelineAttribiv(display->dev, win->pipeline,
                           WFD_PIPELINE_DESTINATION_RECTANGLE, 4, rect);
    CHECK_RESULT(eError == WFD_ERROR_NONE,
                 "set destination rectangle failed", err);

    ctx->display = display;
    ctx->win = win;

    return RT_EOK;

err:
    if (eError != WFD_ERROR_NONE)
        rt_kprintf("eError=0x%08x\n", eError);

    if (ctx->disp_buf)
    {
        free(ctx->disp_buf);
    }
    if (win)
    {
        if (win->pipeline)
        {
            wfdDestroyPipeline(display->dev, win->pipeline);
        }
        free(win);
    }
    if (display)
    {
        if (display->dev)
        {
            for (int i = 0; i < MAX_BUFFER_COUNT; i++)
            {
                if (win->source[i])
                    wfdDestroySource(display->dev, win->source[i]);

                if (win->eglImage[i])
                    wfdDestroyWFDEGLImages(display->dev, 1, &(win->eglImage[i]));
            }
            if (display->port)
            {
                wfdDestroyPort(display->dev, display->port);
            }
            wfdDestroyDevice(display->dev);
        }
        free(display);
    }

    return -RT_ERROR;
}

static rt_err_t wfd_exit(struct wfd_lv_ctx *ctx)
{
    struct wfd_display *display = ctx->display;
    struct wfd_win *win = ctx->win;
    WFDErrorCode eError;

    if (!display || !win)
    {
        return -RT_ERROR;
    }

    wfdBindSourceToPipeline(display->dev, win->pipeline, WFD_INVALID_HANDLE,
                            WFD_TRANSITION_AT_VSYNC, NULL);
    eError = wfdGetError(display->dev);
    if (eError != WFD_ERROR_NONE)
        rt_kprintf("wfdBindSourceToPipeline eError=0x%08x", eError);

    wfdSetPortAttribi(display->dev, display->port, WFD_PORT_POWER_MODE,
                      WFD_POWER_MODE_OFF);
    eError = wfdGetError(display->dev);
    if (eError != WFD_ERROR_NONE)
        rt_kprintf("set power mode failed, eError=0x%08x", eError);

    wfdDeviceCommit(display->dev, WFD_COMMIT_ENTIRE_PORT, display->port);
    eError = wfdGetError(display->dev);
    if (eError != WFD_ERROR_NONE)
        rt_kprintf("commit failed, eError=0x%08x", eError);

    if (ctx->disp_buf)
    {
        free(ctx->disp_buf);
    }

    if (win->pipeline)
    {
        wfdDestroyPipeline(display->dev, win->pipeline);
    }

    if (display->dev)
    {
        for (int i = 0; i < MAX_BUFFER_COUNT; i++)
        {
            if (win->source[i])
                wfdDestroySource(display->dev, win->source[i]);

            if (win->eglImage[i])
                wfdDestroyWFDEGLImages(display->dev, 1, &(win->eglImage[i]));
        }
        if (display->port)
        {
            wfdDestroyPort(display->dev, display->port);
        }
        wfdDestroyDevice(display->dev);
    }

    free(win);
    free(display);

    return RT_EOK;
}

static void wfd_update(struct wfd_lv_ctx *ctx)
{
    struct wfd_display *display = ctx->display;
    struct wfd_win *win = ctx->win;
    WFDSource commitSource = win->source[win->commitSourceIdx];
    win_image_t *image = win->image[win->commitSourceIdx];
    WFDErrorCode eError;

    memcpy(image->vaddr, ctx->disp_buf, image->size);
    wfdBindSourceToPipeline(display->dev, win->pipeline, commitSource,
                            WFD_TRANSITION_AT_VSYNC, NULL);
    eError = wfdGetError(display->dev);
    if (eError != WFD_ERROR_NONE)
    {
        rt_kprintf("bind source failed eError=0x%08x", eError);
        return;
    }
    win->commitSourceIdx++;
    win->commitSourceIdx %= MAX_BUFFER_COUNT;
    wfdDeviceCommit(display->dev, WFD_COMMIT_ENTIRE_PORT, display->port);
    eError = wfdGetError(display->dev);
    if (eError != WFD_ERROR_NONE)
    {
        rt_kprintf("commit failed eError=0x%08x", eError);
        return;
    }
}

static void lv_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t x;
    int32_t y;
    lv_coord_t w = lv_area_get_width(area);
    int stride;
    struct wfd_lv_ctx *ctx = (struct wfd_lv_ctx *)disp_drv->user_data;

    x = area->x1;
    stride = ctx->disp_buf_stride;
    for (y = area->y1; y <= area->y2; y++)
    {
        lv_color_t *disp = (lv_color_t *)ctx->disp_buf + (y * stride + x);
        memcpy(disp, color_p, w * (LV_COLOR_DEPTH >> 3));
        color_p += w;
    }

    if (lv_disp_flush_is_last(disp_drv))
    {
        wfd_update(ctx);
    }
    lv_disp_flush_ready(disp_drv);
}

rt_err_t lv_port_disp_init(lv_disp_rot_t rotate_disp)
{
    lv_disp_draw_buf_t *draw_buf_dsc = &lv_ctx.draw_buf_dsc;
    lv_disp_drv_t *disp_drv = &lv_ctx.disp_drv;
    lv_coord_t lcd_w, lcd_h;
    uint32_t size_in_px_cnt;

    memset(&lv_ctx, 0, sizeof(lv_ctx));
    wfd_setup(&lv_ctx);

    lcd_w = lv_ctx.display->width;
    lcd_h = lv_ctx.display->height;
    size_in_px_cnt = lcd_w * lcd_h;
    lv_ctx.lv_buf = malloc(size_in_px_cnt * (LV_COLOR_DEPTH >> 3));
    lv_disp_draw_buf_init(draw_buf_dsc, lv_ctx.lv_buf, NULL, size_in_px_cnt);
    lv_disp_drv_init(disp_drv);
    disp_drv->hor_res = lcd_w;
    disp_drv->ver_res = lcd_h;
    disp_drv->flush_cb = lv_disp_flush;
    disp_drv->draw_buf = draw_buf_dsc;
    disp_drv->user_data = &lv_ctx;
    lv_disp_drv_register(disp_drv);

    return RT_EOK;
}

rt_err_t lv_port_disp_deinit(void)
{
    wfd_exit(&lv_ctx);

    return RT_EOK;
}

