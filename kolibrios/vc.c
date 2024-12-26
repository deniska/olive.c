#include "kolibri_sys.h"
#include "../olive.c"

void draw_window(void) {
    kolibri_start_draw();
    kolibri_create_window(0, 0, 320, 240, 0x000000FF, "Hello world");
    kolibri_end_draw();
}

void kolibri_main(void) {
    draw_window();
    while (true) {
        int event;
        while (event = kolibri_check_event()) {
            if (event == KOLIBRI_EVENT_BUTTON) {
                // only one button (exit) in the window so far
                return;
            } else if (event == KOLIBRI_EVENT_REDRAW) {
                draw_window();
            } else if (event == KOLIBRI_EVENT_KEYBOARD) {
                KolibriKeyEvent key_event = kolibri_get_key();
            }
        }
        kolibri_wait_for_vsync();
        draw_window();
        vc_render(0.033f);
    }
}
