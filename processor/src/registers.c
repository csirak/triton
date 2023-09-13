#include <stdlib.h>
#include <stdio.h>

#include "../include/registers.h"

register_file *registers_create()
{
  register_file *registers = malloc_with_retry(sizeof(register_file));
  registers->regs = malloc_with_retry(sizeof(word) * REGISTERS_COUNT);
  registers->size = REGISTERS_COUNT;
  for (int i = 0; i < REGISTERS_COUNT; i++)
  {
    registers_set(registers, i, 0);
  }
  return registers;
}

void registers_free(register_file *registers)
{
  free(registers->regs);
  registers->size = 0;
  free(registers);
}

word registers_get(register_file *registers, u8 idx)
{
  return registers->regs[(int)(idx)];
}

void print_registers(register_file *registers)
{
  for (int i = 0; i < REGISTERS_COUNT; i++)
  {
    printf("Register %d: 0x%x\n", i, registers->regs[(int)(i)]);
  }
}

void registers_set(register_file *registers, u8 idx, word data)
{
  // don't set zp
  if (idx == 0)
    return;

  registers->regs[(int)(idx)] = data;
}
