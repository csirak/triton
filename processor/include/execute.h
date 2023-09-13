#include "../lib/types.h"

#ifndef CLFOW_H
#define CLFOW_H

#define MATH_OPERATION_CASE(opcode, operation)                       \
  {                                                                  \
  case opcode:                                                       \
  {                                                                  \
                                                                     \
    word r1 = cpu_read_reg(cpu, instruction->parameters.reg.r1);     \
    word r2 = cpu_read_reg(cpu, instruction->parameters.reg.r2);     \
    cpu_write_reg(cpu, instruction->parameters.reg.r0, (operation)); \
    break;                                                           \
  }                                                                  \
  }

// External functions
void math_execute(cpu *cpu, instruction *instruction);
void cflow_execute(cpu *cpu, instruction *instruction);
void sysacc_execute(cpu *cpu, instruction *instruction);

#endif // CLFOW_H
