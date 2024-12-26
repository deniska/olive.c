#!/bin/sh

set -xe

export PATH=/home/denis/sdk/gcc-13.2.0/bin:$PATH

CFLAGS="-DVC_PLATFORM=VC_KOLIBRI_PLATFORM -m32 -nostdlib -std=c2x -fno-stack-protector -fno-asynchronous-unwind-tables"
LDFLAGS="-T kolibri_elf.ld"

gcc $CFLAGS -c kolibri_header.s
gcc $CFLAGS -c kolibri_sys.c

gcc $CFLAGS -I.. -c ../demos/triangle.c
gcc $CFLAGS $LDFLAGS -o triangle.kex kolibri_header.o kolibri_sys.o triangle.o


exit 0
mcopy -i programs.img vc.kex ::/vc.kex
qemu-system-i386 -enable-kvm -m 256 \
    -boot a \
    -fda /home/denis/strange/kolibri/kolibri.img \
    -hda programs.img
