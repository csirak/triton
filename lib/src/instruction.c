#include "../instruction.h"
#include "../bits.h"
#include <stdio.h>

instruction *instruction_decode(word encoded_instruction)
{
  instruction *inst = malloc_with_retry(sizeof(instruction));
  inst->opcode = instruction_decode_opcode(encoded_instruction);
  if (inst->opcode <= EQ)
  {
    inst->type = MATH;
    inst->param_type = REG;
    instruction_load_register_params(inst, encoded_instruction);
  }
  else if (inst->opcode <= JEQ)
  {
    inst->type = CFLOW;
    inst->param_type = REG;
    instruction_load_register_params(inst, encoded_instruction);
  }
  else if (inst->opcode <= SYSCALL)
  {
    inst->type = SYSACC;
    if (inst->opcode == SETL || inst->opcode == SETU)
    {
      inst->param_type = IMM;
      instruction_load_immediate_params(inst, encoded_instruction);
    }
    else
    {
      inst->param_type = REG;
      instruction_load_register_params(inst, encoded_instruction);
    }
  }
  else
  {
    inst->type = UNKNOWN;
  }
  return inst;
}

Instructions instruction_decode_opcode(word encoded_instruction)
{
  return BIT6(encoded_instruction, 0);
}

void instruction_load_register_params(instruction *inst, word encoded_instruction)
{
  inst->parameters.reg.r0 = BIT6(encoded_instruction, 1);
  inst->parameters.reg.r1 = BIT6(encoded_instruction, 2);
  inst->parameters.reg.r2 = BIT6(encoded_instruction, 3);
}

void instruction_load_immediate_params(instruction *inst, word encoded_instruction)
{
  inst->parameters.imm.r0 = BIT6(encoded_instruction, 1);
  inst->parameters.imm.imm = popWord(encoded_instruction, 12);
}

word instruction_encode_to_word(instruction *inst)
{
  switch (inst->param_type)
  {
  case REG:
    return instruction_encode_reg(inst);
    break;
  case IMM:
    return instruction_encode_imm(inst);
    break;
  default:
    break;
  }
}

word instruction_encode_reg(instruction *inst)
{
  word encoded_instruction = inst->parameters.reg.r2;
  encoded_instruction = pushWord(encoded_instruction, inst->parameters.reg.r1, 6);
  encoded_instruction = pushWord(encoded_instruction, inst->parameters.reg.r0, 6);
  encoded_instruction = pushWord(encoded_instruction, inst->opcode, 6);
  return encoded_instruction;
}

word instruction_encode_imm(instruction *inst)
{
  word encoded_instruction = inst->parameters.imm.imm;
  encoded_instruction = pushWord(encoded_instruction, inst->parameters.reg.r0, 6);
  encoded_instruction = pushWord(encoded_instruction, inst->opcode, 6);
  return encoded_instruction;
}

const char *instruction_keywords[] = {
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "SLL",
    "SRL",
    "SRA",
    "AND",
    "OR",
    "XOR",
    "NOT",
    "SLT",
    "SLTU",
    "EQ",
    "JUMP",
    "JEQ",
    "LOAD",
    "STR",
    "SETU",
    "SETL",
    "SETR",
    "IRQ",
    "SYSCALL"};

const char *op_type_keywords[] = {
    "MATH",
    "CFLOW",
    "SYSACC",
    "UNKNOWN"};

const char *param_type_keywords[] = {
    "REG",
    "IMM"};

void instruction_log(instruction *inst)
{
  printf("Op Type: %s\n", op_type_keywords[inst->type]);
  printf("Op Code: %s\n", instruction_keywords[inst->opcode]);
  printf("Inst type: %s\n", param_type_keywords[inst->param_type]);
  if (inst->param_type == REG)
  {
    register_parameters *params = &inst->parameters.reg;
    printf("R0: %d\n", params->r0);
    printf("R1: %d\n", params->r1);
    printf("R2: %d\n", params->r2);
  }
  else
  {
    imm_parameters *params = &inst->parameters.imm;
    printf("R0: %d\n", params->r0);
    printf("IMM: %d\n", params->imm);
  }
}
