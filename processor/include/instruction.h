#include "../lib/types.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum param_type
{
  REG,
  IMM
} param_type;

typedef enum op_type
{
  MATH,
  CFLOW,
  SYSACC,
  STACK,
  UNKNOWN
} op_type;

typedef enum Instructions
{
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  SLL,
  SRL,
  SRA,
  AND,
  OR,
  XOR,
  NOT,
  SLT,
  SLTU,
  EQ,
  MATH_END,
  JUMP,
  JEQ,
  CFLOW_END,
  LOAD,
  STR,
  SETU,
  SETL,
  SETR,
  IRQ,
  SYSCALL,
  SYSACC_END,
  PUSH,
  POP,
  STACK_END,
} Instructions;

typedef struct register_parameters
{
  byte r0;
  byte r1;
  byte r2;
} register_parameters;

typedef struct imm_parameters
{
  byte r0;
  word imm;
} imm_parameters;

typedef struct instruction
{
  op_type type;
  byte opcode;
  param_type param_type;
  union parameters
  {
    register_parameters reg;
    imm_parameters imm;
  } parameters;

} instruction;

word instruction_encode_to_word(instruction *inst);
word instruction_encode_reg(instruction *inst);
word instruction_encode_imm(instruction *inst);

instruction *instruction_decode(word);
void instruction_decode_math(instruction *inst, word encoded_instruction);
void instruction_decode_cflow(instruction *inst, word encoded_instruction);
void instruction_decode_sysacc(instruction *inst, word encoded_instruction);
void instruction_decode_stack(instruction *inst, word encoded_instruction);

void instruction_load_register_params(instruction *inst, word encoded_instruction);
void instruction_load_immediate_params(instruction *inst, word encoded_instruction);

void instruction_log(instruction *inst);

#endif // INSTRUCTION_H
