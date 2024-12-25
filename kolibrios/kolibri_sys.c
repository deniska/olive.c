#include "kolibri_sys.h"

/*
typedef struct {
	char signature[8];
	unsigned version;
	void *start;
	void* program_end;
	void* required_memory;
	void *top_of_the_stack;
	void *args;
	void *exe_path;
} _KolibriHeader;
*/

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
    x = x * 65536 + xsize;
    y = y * 65536 + ysize;
    color &= 0x00FFFFFF;
    color |= 0x33000000; // with a skin, resizeable, has title, client rect
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
