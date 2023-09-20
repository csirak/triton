#include "../include/types.h"
#include <stdlib.h>

#ifndef SCREEN_H
#define SCREEN_H

Screen *screen_create(int width, int height);
void screen_set_pixel(Screen *screen, int x, int y, word color);
void screen_write_buffer(Screen *screen, word *buffer, int width, int height);
void screen_display(Screen *screen);
void screen_free(Screen *screen);

#endif // SCREEN_H
