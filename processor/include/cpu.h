#include "../lib/types.h"
#include "../lib/bits.h"

#include "registers.h"
#include "memory.h"

#ifndef CPU_H
#define CPU_H

// Register Macros
#define GET_REG(cpu, REG_NAME) registers_get(cpu->registers, REG_NAME)
#define SET_REG(cpu, tag, value) registers_set(cpu->registers, tag, value)

cpu *cpu_create();
void cpu_free(cpu *cpu);

void cpu_write_reg(cpu *cpu, u8 reg, word data);
void cpu_write_mem(cpu *cpu, word address, word data);

word cpu_read_reg(cpu *cpu, u8 reg);
word cpu_read_mem(cpu *cpu, word address);

void cpu_vram_to_screen(cpu *cpu);

void cpu_start(cpu *cpu);
void cpu_step(cpu *cpu);
void cpu_run(cpu *cpu);

#endif // CPU_H