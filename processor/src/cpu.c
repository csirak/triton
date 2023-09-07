#include "../lib/types.h"
#include "../include/cpu.h"
#include <stdlib.h>
#include "../include/instruction.h"

void cpu_init(cpu *cpu)
{
  cpu->registers = malloc(sizeof(register_file));
  cpu->memory = malloc(sizeof(memory));
  registers_init(cpu->registers);
  memory_init(cpu->memory);
}
void cpu_free(cpu *cpu)
{
  free(cpu->registers);
  free(cpu->memory);
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
void cpu_step(cpu *cpu)
{
  word encoded_instruction = memory_get(cpu->memory, GET_REG(cpu, PC_REG));
  instruction *inst = instruction_decode(encoded_instruction);
  instruction_execute(cpu, inst);
}

void cpu_run(cpu *cpu)
{
  while (1)
  {
    cpu_step(cpu);
  }
}
