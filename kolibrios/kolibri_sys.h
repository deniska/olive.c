#ifndef _KOLIBRI_H_
#define _KOLIBRI_H_

#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char

#ifndef NULL
#define NULL ((void *)0)
#endif

extern void kolibri_main(void);
extern const void *_kolibri_stack;
extern const void *_kolibri_program_end;
extern const void *_kolibri_required_memory;
extern const void *_kolibri_top_of_the_stack;

void _kolibri_start(void);
void kolibri_terminate_process(void);
void kolibri_create_window(u32 x, u32 y, u32 xsize, u32 ysize, u32 color, const char * title);
void kolibri_start_draw(void);
void kolibri_end_draw(void);
int kolibri_wait_event(void);
int kolibri_check_event(void);
void kolibri_wait_for_vsync(void);

typedef struct {
    bool has_key;
    bool has_hotkey;
    u8 ascii;
    u8 scancode;
    u16 modifiers;
} KolibriKeyEvent;

KolibriKeyEvent kolibri_get_key(void);

typedef enum {
    KOLIBRI_EVENT_REDRAW = 1,
    KOLIBRI_EVENT_KEYBOARD = 2,
    KOLIBRI_EVENT_BUTTON = 3,
    KOLIBRI_EVENT_BACKGROUND_REDRAW_FINISHED = 5,
    KOLIBRI_EVENT_MOUSE = 6,
    KOLIBRI_EVENT_IPC = 7,
    KOLIBRI_EVENT_NETWORK = 8,
    KOLIBRI_EVENT_DEBUG = 9,
} kolibri_event;

void kolibri_blit(
        void* pixels, u32 pixels_bytes,
        int src_x, int src_y, u32 src_w, u32 src_h,
        int dst_x, int dst_y, u32 dst_w, u32 dst_h);

void kolibri_put_image(u8* pixels_bgr, u16 width, u16 height, u16 x, u16 y);
void kolibri_sleep100(int hundredth_seconds);

// libc-ish stuff

void *memset(void *s, int c, u32 n);

// math

float sqrtf(float val);
float sinf(float val);
float cosf(float val);
float atan2f(float y, float x);
void sincosf(float x, float *sin, float *cos);
#endif

