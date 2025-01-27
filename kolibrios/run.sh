#!/bin/sh

set -xe

PATH=/home/denis/Apps/qemu-8.2.7/bin:$PATH

qemu-system-i386 -enable-kvm -m 256 \
    -boot a \
    -cpu host \
    -fda /home/denis/strange/kolibri/kolibri.img \
    -hda programs.img

