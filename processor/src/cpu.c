#include <stdlib.h>
#include <stdio.h>

#include "../lib/types.h"
#include "../include/cpu.h"

#include "../include/instruction.h"
#include "../include/screen.h"

cpu *cpu_create()
{
  cpu *cpu = malloc_with_retry(sizeof(cpu));
  cpu->registers = registers_create();
  cpu->memory = memory_create();
  cpu->screen = screen_create(SCREEN_WIDTH, SCREEN_HEIGHT);

  return cpu;
}

void cpu_free(cpu *cpu)
{
  registers_free(cpu->registers);
  memory_free(cpu->memory);
  screen_free(cpu->screen);
  free(cpu);
}

// Register Accessors
void cpu_write_reg(cpu *cpu, u8 reg, word data)
{
  registers_set(cpu->registers, reg, data);
}

word cpu_read_reg(cpu *cpu, u8 reg)
{
  return registers_get(cpu->registers, reg);
}

// Memory Accessors
void cpu_write_mem(cpu *cpu, word address, word data)
{
  memory_set(cpu->memory, address, data);
}

word cpu_read_mem(cpu *cpu, word address)
{
  return memory_get(cpu->memory, address);
}

// Execution

void cpu_start(cpu *cpu)
{
  cpu_write_reg(cpu, SP_REG, 0x00000FFF);
  cpu_write_reg(cpu, PC_REG, 0x00001000);
}

void cpu_vram_to_screen(cpu *cpu)
{
  screen_write_buffer(cpu->screen, &cpu->memory->memory[VIDEO_MEMORY_START], SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool cpu_step(cpu *cpu)
{
  word pc_value = cpu_read_reg(cpu, PC_REG);
  word encoded_instruction = cpu_read_mem(cpu, pc_value);
  cpu_write_reg(cpu, PC_REG, pc_value + 1);
  instruction *inst = instruction_decode(encoded_instruction);
  instruction_execute(cpu, inst);
  free(inst);
  return false;
}

void cpu_run(cpu *cpu)
{

  bool running = true;
  bool changed = true;
  sfEvent event;
  while (running)
  {
    while (sfRenderWindow_pollEvent(cpu->screen->window, &event))
    {
      if (event.type == sfEvtClosed)
      {
        running = false;
      }
      if (changed)
      {
        screen_display(cpu->screen);
        changed = false;
      }
      changed = cpu_step(cpu);
    }
  }
}
