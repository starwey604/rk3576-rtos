#! /bin/bash

export LC_ALL=C.UTF-8
export LANG=C.UTF-8

CUR_DIR=$(pwd)
TOOLS=$CUR_DIR/../tools
IMAGE=$(pwd)/Image

usage() {
    echo "usage: ./mkfirmware.sh <setting.ini>"
}

echo ""
echo "==========================================="
echo "============== make Firmware =============="
echo "==========================================="
echo ""

if [ ! -n "$1" ] ;then
    usage
    exit
fi

if [ ! -f "$1" ] || [[ "$1" != *.ini ]] ;then
    usage
    exit
fi

# clean *.img *.bin Firmware* #
echo "clean *.img *.bin Firmware* ..."
rm -rf $IMAGE/*.img $IMAGE/*.bin $IMAGE/Firmware*

# pack rk2118_idb_no_ddr.img & MiniLoaderAll.bin #
../tools/sign_tool/bin/boot_merger ./Image/rk2118_no_ddr.ini

# pack rtt.img tfm.img load.img #
./package_image.py $1
if [ ! $? -eq 0 ] ;then
    echo "mkimage fail"
    exit
fi

# make .ini #
./mkini.py $1
if [ ! $? -eq 0 ] ;then
    exit
fi

# pack firmware #
setting_file=$(echo "$1" | sed 's/setting.ini/.ini/')
$TOOLS/firmware_merger/firmware_merger -p $setting_file $IMAGE/
