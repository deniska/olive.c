#!/bin/sh

set -xe

export PATH=/home/denis/sdk/gcc-13.2.0/bin:$PATH

CFLAGS="-DVC_PLATFORM=3 -O3 -march=pentium3 -m32 -nostdlib -std=c2x -fno-stack-protector -fno-asynchronous-unwind-tables"

gcc $CFLAGS -c kolibri_header.s
gcc $CFLAGS -c kolibri_sys.c
gcc $CFLAGS -c arith64.c

build_demo() {
    gcc $CFLAGS -I../build -I.. -I. "-DVC_TITLE=\"$1 demo\"" -c ../demos/$1.c
    /home/denis/private/kolibri/prefix/bin/i686-kolibri-ld -o $1.kex $1.o kolibri_sys.o arith64.o
    mcopy -i programs.img -D o $1.kex ::/$1.kex
}

build_demo cup3d
build_demo dots3d
build_demo penger3d
build_demo squish
build_demo teapot3d
build_demo triangle3d
build_demo triangle3dTex
build_demo triangle
build_demo triangleTex

./run.sh
