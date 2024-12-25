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

#endif
