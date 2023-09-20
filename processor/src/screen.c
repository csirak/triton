#include "SFML/Graphics.h"

#include "../include/screen.h"

Screen *screen_create(int width, int height)
{
  Screen *screen = malloc(sizeof(Screen));
  if (!screen)
  {
    return NULL;
  }

  screen->window = sfRenderWindow_create((sfVideoMode){width, height, 32}, "CSFML Screen", sfClose, NULL);
  if (!screen->window)
  {
    free(screen);
    return NULL;
  }

  screen->image = sfImage_create(width, height);
  screen->texture = sfTexture_create(width, height);
  screen->sprite = sfSprite_create();

  return screen;
}

sfColor word_to_sfColor(word data)
{
  sfColor color;
  color.r = (data & 0xFF000000) >> 24;
  color.g = (data & 0x00FF0000) >> 16;
  color.b = (data & 0x0000FF00) >> 8;
  color.a = (data & 0x000000FF);
  return color;
}

void screen_set_pixel(Screen *screen, int x, int y, word color)
{
  sfImage_setPixel(screen->image, x, y, word_to_sfColor(color));
  sfTexture_updateFromImage(screen->texture, screen->image, 0, 0);
}

void screen_write_buffer(Screen *screen, word *buffer, int width, int height)
{
  screen->image = sfImage_createFromPixels(width, height, (sfUint8 *)buffer);
  sfTexture_updateFromImage(screen->texture, screen->image, 0, 0);
}

void screen_display(Screen *screen)
{
  sfSprite_setTexture(screen->sprite, screen->texture, sfTrue);
  sfRenderWindow_drawSprite(screen->window, screen->sprite, NULL);
  sfRenderWindow_display(screen->window);
}

void screen_free(Screen *screen)
{
  if (screen)
  {
    if (screen->sprite)
    {
      sfSprite_destroy(screen->sprite);
    }
    if (screen->texture)
    {
      sfTexture_destroy(screen->texture);
    }
    if (screen->image)
    {
      sfImage_destroy(screen->image);
    }
    if (screen->window)
    {
      sfRenderWindow_destroy(screen->window);
    }
    free(screen);
  }
}
