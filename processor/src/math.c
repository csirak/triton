#include "../include/math.h"
#include "../include/cpu.h"

void math_execute(cpu *cpu, instruction *instruction)
{
  switch (instruction->opcode)
  {
    MATH_OPERATION_CASE(ADD, r1 + r2)
    MATH_OPERATION_CASE(SUB, r1 - r2)
    MATH_OPERATION_CASE(MUL, r1 * r2)
  case DIV:
  {

    word r1 = cpu_read_reg(cpu, instruction->parameters.reg.r1);
    word r2 = cpu_read_reg(cpu, instruction->parameters.reg.r2);
    if (r1 == 0 || r2 == 0)
    {
      cpu_write_reg(cpu, instruction->parameters.reg.r0, 0);
      cpu_write_reg(cpu, FG_REG, 0x69);
      break;
    }
    cpu_write_reg(cpu, instruction->parameters.reg.r0, (r1 / r2));
    break;
  }
    MATH_OPERATION_CASE(MOD, r1 % r2)
    MATH_OPERATION_CASE(SLL, r1 << r2)
    MATH_OPERATION_CASE(SRL, ((unsigned int)r1) >> r2)
    MATH_OPERATION_CASE(SRA, (signed int)((signed int)r1) >> r2)
    MATH_OPERATION_CASE(AND, r1 & r2)
    MATH_OPERATION_CASE(OR, r1 | r2)
    MATH_OPERATION_CASE(XOR, r1 ^ r2)
    MATH_OPERATION_CASE(NOT, ~r1)
    MATH_OPERATION_CASE(SLT, (signed int)r1 < (signed int)r2)
    MATH_OPERATION_CASE(SLTU, ((unsigned int)r1) < ((unsigned int)r2))
    MATH_OPERATION_CASE(EQ, r1 == r2)
  default:
    break;
  }
}
