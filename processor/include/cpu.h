#include "../lib/types.h"
#include "registers.h"
#include "memory.h"
#include "../lib/bits.h"

#ifndef CPU_H
#define CPU_H


// Register Macros
#define GET_REG(cpu, REG_NAME) registers_get(cpu->registers, REG_NAME)
#define SET_REG(cpu, tag, value) registers_set(cpu->registers, tag, value)

void cpu_init(cpu *cpu);
void cpu_free(cpu *cpu);
void cpu_step(cpu *cpu);

void cpu_free(cpu *cpu);
void cpu_write_reg(cpu *cpu, u8 reg, word data);
word cpu_read_reg(cpu *cpu, u8 reg);
void cpu_write_mem(cpu *cpu, word address, word data);
word cpu_read_mem(cpu *cpu, word address);

#endif // CPU_H

ifdf