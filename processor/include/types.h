#include "lib/types.h"

#ifndef PROC_TYPES_H
#define PROC_TYPES_H
#define MEMORY_SIZE 0xFFFFFF
#define REGISTERS_COUNT (32)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define VIDEO_MEMORY_START 0x00010000

typedef struct register_file
{
  word *regs;
  long size;
} register_file;

typedef struct memory
{
  word *memory;
  long size;
} memory;

typedef struct Screen
{
  void *window;
  void *image;
  void *texture;
  void *sprite;
} Screen;

typedef struct cpu
{
  register_file *registers;
  memory *memory;
  Screen *screen;
} cpu;



#endif // PROC_TYPES_H
