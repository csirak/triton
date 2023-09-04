#include "types.h"
#include "registers.h"
#include "memory.h"
#include "../lib/bits.h"

#ifndef CPU_H
#define CPU_H

// Registers Constants
#define Z_REG (0)
#define RA_REG (1)
#define SP_REG (2)
#define GP_REG (3)
#define TP_REG (4)
#define PC_REG (5)
#define FP_REG (6)
#define FG_REG (7)

// Flag Constants
#define CF_FLG (0)
#define ZF_FLG (1)
#define SF_FLG (2)
#define OF_FLG (3)
#define IF_FLG (4)
#define IOF_FLG (5)
#define MAF_FLG (6)

// Register Macros
#define GET_Z (cpu) registers_get(cpu->registers, Z_REG)
#define GET_RA(cpu) registers_get(cpu->registers, RA_REG)
#define GET_SP(cpu) registers_get(cpu->registers, SP_REG)
#define GET_GP(cpu) registers_get(cpu->registers, GP_REG)
#define GET_TP(cpu) registers_get(cpu->registers, TP_REG)
#define GET_PC(cpu) registers_get(cpu->registers, PC_REG)
#define GET_FP(cpu) registers_get(cpu->registers, FP_REG)
#define GET_FG(cpu) registers_get(cpu->registers, FG_REG)

// Flag Macros

#define GET_CF (cpu) BIT((GET_FG(cpu)), CF_FLG)
#define GET_ZF (cpu) BIT((GET_FG(cpu)), ZF_FLG)
#define GET_SF (cpu) BIT((GET_FG(cpu)), SF_FLG)
#define GET_OF (cpu) BIT((GET_FG(cpu)), OF_FLG)
#define GET_IF (cpu) BIT((GET_FG(cpu)), IF_FLG)
#define GET_IOF(cpu) BIT((GET_FG(cpu)), IOF_FLG)
#define GET_MAF(cpu) BIT((GET_FG(cpu)), MAF_FLG)

void cpu_init(cpu *cpu);
void cpu_free(cpu *cpu);
void cpu_step(cpu *cpu);

void cpu_free(cpu *cpu);
void cpu_write_reg(cpu *cpu, u8 reg, word data);
word cpu_read_reg(cpu *cpu, u8 reg);
void cpu_write_mem(cpu *cpu, word address, word data);
word cpu_read_mem(cpu *cpu, word address);

#endif // CPU_H
