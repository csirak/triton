#include <stdlib.h>
#include <stdio.h>

#include "lib/instruction.h"

#include "../include/execute.h"

bool instruction_execute(cpu *cpu, instruction *inst)
{
  switch (inst->type)
  {
  case MATH:
    return math_execute(cpu, inst);

  case CFLOW:
    return cflow_execute(cpu, inst);

  case SYSACC:
    return sysacc_execute(cpu, inst);
  }
  return false;
}