
#include "stdio.h"

#include "../include/cpu.h"
#include "../include/execute.h"

void sysacc_execute(cpu *cpu, instruction *instruction)
{
  switch (instruction->opcode)
  {
  case LOAD:
  {
    word memory_address = cpu_read_reg(cpu, instruction->parameters.reg.r1);
    word memory_value = cpu_read_mem(cpu, memory_address);
    cpu_write_reg(cpu, instruction->parameters.reg.r0, memory_value);
    break;
  }
  case STR:
  {
    word memory_address = cpu_read_reg(cpu, instruction->parameters.reg.r0);
    word memory_value = cpu_read_reg(cpu, instruction->parameters.reg.r1);
    cpu_write_mem(cpu, memory_address, memory_value);
    break;
  }
  case SETU:
  {
    word register_value = cpu_read_reg(cpu, instruction->parameters.reg.r0);
    register_value |= (instruction->parameters.imm.imm << 16 & 0xFFFF0000);
    cpu_write_reg(cpu, instruction->parameters.imm.r0, register_value);
    break;
  }
  case SETL:
  {
    word register_value = cpu_read_reg(cpu, instruction->parameters.reg.r0);
    register_value |= (instruction->parameters.imm.imm & 0x0000FFFF);
    cpu_write_reg(cpu, instruction->parameters.imm.r0, register_value);
    break;
  }
  case SETR:
  {
    word register_value = cpu_read_reg(cpu, instruction->parameters.reg.r1);
    cpu_write_reg(cpu, instruction->parameters.imm.r0, register_value);
    break;
  }

  case IRQ:
  {
    // undef  for now
  }

  case SYSCALL:
  {
    // undef  for now
  }

  default:
    break;
  }
}
