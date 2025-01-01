#!/bin/sh

set -xe

qemu-system-i386 -enable-kvm -m 256 \
    -boot a \
    -cpu host \
    -fda /home/denis/strange/kolibri/kolibri.img \
    -hda programs.img

