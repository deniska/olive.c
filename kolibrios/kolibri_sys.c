#include "kolibri_sys.h"

void _kolibri_start(void) {
    kolibri_main();
    kolibri_terminate_process();
}

void kolibri_terminate_process(void) {
    __asm__ __volatile__ (
        "movl $0xFFFFFFFF, %%eax\n"
        "int $0x40\n"
        :
        :
        : "%eax"
    );
}

void kolibri_create_window(u32 x, u32 y, u32 xsize, u32 ysize, u32 color, const char * title) {
    int skin_height;
    __asm__ __volatile__ (
        "movl $48, %%eax\n"
        "movl $4, %%ebx\n"
        "int $0x40\n"
        "movl %%eax, %0"
        : "=g" (skin_height)
        :
        : "%eax", "%ebx"
    );
    xsize += 8; // window borders
    ysize += 4 + skin_height;
    x = x * 65536 + xsize;
    y = y * 65536 + ysize;
    color &= 0x00FFFFFF;
    // color |= 0x33000000; // with a skin, resizeable, has title, client rect
    color |= 0x34000000; // with a skin, resizeable, has title, client rect
    __asm__ __volatile__ (
        "movl $0, %%eax\n"
        "movl %0, %%ebx\n"
        "movl %1, %%ecx\n"
        "movl %2, %%edx\n"
        "movl %3, %%edi\n"
        "int $0x40\n"
        :
        : "g" (x), "g" (y), "g" (color), "g" ((u32) title)
        : "%eax", "%ebx", "%ecx", "%edx", "%edi"
    );
}

void kolibri_start_draw(void) {
    __asm__ __volatile__ (
        "movl $12, %%eax\n"
        "movl $1, %%ebx\n"
        "int $0x40\n"
        :
        :
        : "%eax", "%ebx"
    );
}

void kolibri_end_draw(void) {
    __asm__ __volatile__ (
        "movl $12, %%eax\n"
        "movl $2, %%ebx\n"
        "int $0x40\n"
        :
        :
        : "%eax", "%ebx"
    );
}

int kolibri_wait_event(void) {
    int result;
    __asm__ __volatile__ (
        "movl $10, %%eax\n"
        "int $0x40\n"
        "movl %%eax, %0\n"
        : "=r" (result)
        :
        : "%eax"
    );
    return result;
}

int kolibri_check_event(void) {
    int result;
    __asm__ __volatile__ (
        "movl $11, %%eax\n"
        "int $0x40\n"
        "movl %%eax, %0\n"
        : "=r" (result)
        :
        : "%eax"
    );
    return result;
}

KolibriKeyEvent kolibri_get_key(void) {
    u32 result;
    __asm__ __volatile__ (
        "movl $2, %%eax\n"
        "int $0x40\n"
        "movl %%eax, %0"
        : "=r" (result)
        :
        : "%eax"
    );
    KolibriKeyEvent key_event = {0};

    if (result & 0xff == 0) {
        key_event.has_key = true;
        key_event.ascii = (result >> 8) & 0xff;
        key_event.scancode = (result >> 16) & 0xff;
    } else if (result & 0xff == 2) {
        key_event.has_key = true;
        key_event.has_hotkey = true;
        key_event.scancode = (result >> 8) & 0xff;
        key_event.modifiers = (result >> 16);
    }

    return key_event;
}

void kolibri_wait_for_vsync(void) {
    __asm__ __volatile__ (
        "movl $18, %%eax\n"
        "movl $14, %%ebx\n"
        "int $0x40\n"
        :
        :
        : "%eax", "%ebx"
    );
}

void kolibri_blit(
        void* pixels, u32 pixels_bytes,
        int src_x, int src_y, u32 src_w, u32 src_h,
        int dst_x, int dst_y, u32 dst_w, u32 dst_h) {
    struct {
        int dst_x; int dst_y; u32 dst_w; u32 dst_h;
        int src_x; int src_y; u32 src_w; u32 src_h;
        void* pixels; u32 pixels_bytes;
    } params = {
        dst_x, dst_y, dst_w, dst_h, src_x, src_y, src_w, src_h,
        pixels, pixels_bytes
    };
    __asm__ __volatile__ (
        "movl $73, %%eax\n"
        "movl $0x00000000, %%ebx\n"
        "movl %0, %%ecx\n"
        "int $0x40\n"
        :
        : "r" (&params)
        : "%eax", "%ebx", "%ecx"
    );
}

void kolibri_put_image(u8* pixels_bgr, u16 width, u16 height, u16 x, u16 y) {
    u32 size = width * 65536 + height;
    u32 coord = x * 65536 + y;
    __asm__ __volatile__ (
        "movl $7, %%eax\n"
        "movl %0, %%ebx\n"
        "movl %1, %%ecx\n"
        "movl %2, %%edx\n"
        "int $0x40\n"
        :
        : "g" (pixels_bgr), "g" (size), "g" (coord)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
}

void kolibri_sleep100(int hundredth_seconds) {
    __asm__ __volatile__ (
        "movl $5, %%eax\n"
        "movl %0, %%ebx\n"
        "int $0x40\n"
        :
        : "g" (hundredth_seconds)
        : "%eax", "%ebx"
    );
}

// libc-ish stuff

void *memset(void *s, int c, u32 n) {
    char *p = s;
    while (n > 0) {
        *p = c;
        p++;
        n--;
    }
    return s;
}

// math

float sqrtf(float val) {
    float ret;
    __asm__ __volatile__ (
        "fld %1\n"
        "fsqrt\n"
        "fstp %0\n"
        : "=m" (ret)
        : "m" (val)
    );
    return ret;
}

float sinf(float val) {
    float ret;
    __asm__ __volatile__ (
        "fld %1\n"
        "fsin\n"
        "fstp %0\n"
        : "=m" (ret)
        : "m" (val)
    );
    return ret;
}

float cosf(float val) {
    float ret;
    __asm__ __volatile__ (
        "fld %1\n"
        "fcos\n"
        "fstp %0\n"
        : "=m" (ret)
        : "m" (val)
    );
    return ret;
}

float atan2f(float y, float x) {
    float ret;
    __asm__ __volatile__ (
        "fld %1\n"
        "fld %2\n"
        "fpatan\n"
        "fstp %0\n"
        : "=m" (ret)
        : "m" (y), "m" (x)
    );
    return ret;
}

void sincosf(float x, float *sin, float *cos) {
    float _sin, _cos;
    __asm__ __volatile__ (
        "fld %2\n"
        "fsincos\n"
        "fstp %0\n"
        "fstp %1\n"
        : "=m" (_sin), "=m" (_cos)
        : "m" (x)
    );
    *sin = _sin;
    *cos = _cos;
}
