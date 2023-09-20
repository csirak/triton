#include "../include/cpu.h"
#include "../include/screen.h"
#include <stdio.h>

int main()
{
  cpu *cpu = cpu_create();
  cpu_start(cpu);
  int running = 1;
  for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
  {
    cpu_write_mem(cpu, 0x00010000 + i, 0xFF0000ff);
  }
  printf("test3\n");
  cpu_vram_to_screen(cpu);
  cpu_run(cpu);
  cpu_free(cpu);
}
