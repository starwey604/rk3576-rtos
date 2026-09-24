#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause */
# Copyright (c) 2025 Rockchip Electronics Co., Ltd.

set -e

export LC_ALL=C.UTF-8
export LANG=C.UTF-8

usage() {
    echo "usage: ./mkimage.sh"
}

CUR_DIR=$(pwd)
TOOLS=$CUR_DIR/../tools
IMAGE=$(pwd)/Image
RKBIN=$(pwd)/rkbin

test -d $IMAGE || mkdir $IMAGE
rm Image/amp.img Image/hpmcu.img || true

if [ ! -n "$1" ] ;then
    cat $RKBIN/hpmcu_start.bin $CUR_DIR/rtthread.bin > $IMAGE/hpmcu.img
else
    case $1 in
        *"amp"*)
            cp -r $CUR_DIR/rtthread.bin $IMAGE/rtt.bin
            $TOOLS/mkimage -f $IMAGE/amp.its -E -p 0xe00 $IMAGE/hpmcu.img
            ln -sf $IMAGE/hpmcu.img $IMAGE/amp.img
            ;;
        *)
            usage
            exit
            ;;
    esac
fi

echo 'Image: hpmcu.img is ready.'
