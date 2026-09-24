# Provenance

This repository is a fork of the **Rockchip RT-Thread** tree (RT-Thread **4.1.1** plus
Rockchip's `bsp/rockchip` board-support packages) for **RK3576**.

- Upstream RTOS: <https://github.com/RT-Thread/rt-thread> (Apache-2.0, see `LICENSE`)
- Source of this tree (not publicly hosted by Rockchip): extracted from the
  **Forlinx OK3576 Linux SDK** (`OK3576-linux-source/rtos`).
- Target use: the **Linux + Cortex-M0 RT-Thread** AMP combination on RK3576
  (`rtos/bsp/rockchip/rk3576-mcu`), consumed by the `zenith` project's
  LubanCat SDK patch stack via `.repo/local_manifests`.

## Changes relative to the extracted vendor tree

- Pruned `bsp/*` down to `bsp/rockchip` (dropped unrelated-vendor BSPs to keep the repo small).
- Removed Forlinx-specific demo applications under
  `bsp/rockchip/rk3576-mcu/applications/` (`forlinx_*.c`, `fl_rpmsg_test.c`).
- Fixed a genuine bug in `bsp/rockchip/common/drivers/drv_pwm.c`: `rt_kprintf(device, ...)`
  passed a device pointer as the format string (rejected as an error by GCC >= 14).

## Build (Cortex-M0 BSP)

```sh
cd bsp/rockchip/rk3576-mcu
export RTT_ROOT=$PWD/../../..
export RTT_CC=gcc
export RTT_EXEC_PATH=/usr/bin        # dir containing arm-none-eabi-gcc
scons -j8
```

A public **Arm GNU toolchain for `arm-none-eabi`** (e.g. 10-2020-q4-major / the Ubuntu
`gcc-arm-none-eabi` package) is sufficient; no vendor-patched compiler is required.

> Note: `bsp/rockchip/common/hal` is a symlink to `../../../../hal`. When checked out inside
> the LubanCat SDK it resolves to `<SDK>/hal`, which is provided by the sibling
> `rk3576-hal` repository.
