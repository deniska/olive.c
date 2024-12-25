#!/bin/sh

set -xe

export PATH=/home/denis/sdk/gcc-13.2.0/bin:$PATH

CFLAGS="-m32 -nostdlib -std=c2x -fno-stack-protector -fno-asynchronous-unwind-tables"
LDFLAGS="-T kolibri_elf.ld"

gcc $CFLAGS -c kolibri_header.s
gcc $CFLAGS -c hello.c
gcc $CFLAGS -c kolibri_sys.c

gcc $CFLAGS $LDFLAGS -o hello.kex kolibri_header.o kolibri_sys.o hello.o
mcopy -i programs.img hello.kex ::/hello.kex
qemu-system-i386 -enable-kvm -m 256 \
    -boot a \
    -fda /home/denis/strange/kolibri/kolibri.img \
    -hda programs.img
