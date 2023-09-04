#include "minunit.h"
#include "../include/instruction.h"

#ifndef TEST_INSTRUCTION_H
#define TEST_INSTRUCTION_H
#define GET_TEST_NAME(opcode) MU_RUN_TEST(test_instructions_decode_##opcode);

#define REG_OPCODE_TEST(op_type, op_code, r0_value, r1_value, r2_value)                            \
                                                                                                   \
  MU_TEST(test_instructions_decode_##op_code)                                                      \
  {                                                                                                \
    printf("test_instructions_decode_%s\n", #op_code);                                             \
    instruction test_##op_code = {op_type, op_code, REG, {{r0_value, r1_value, r2_value}}};        \
    word encoded_instruction = instruction_encode_to_word(&test_##op_code);                        \
    instruction *decoded_instruction = instruction_decode(encoded_instruction);                    \
    mu_assert(decoded_instruction->opcode == op_code, "Instruction decode failed");                \
    mu_assert(decoded_instruction->type == op_type, "Operation decode failed");                    \
    mu_assert(decoded_instruction->parameters.reg.r0 == r0_value, "Register param decode failed"); \
    mu_assert(decoded_instruction->parameters.reg.r1 == r1_value, "Register param decode failed"); \
    mu_assert(decoded_instruction->parameters.reg.r2 == r2_value, "Register param decode failed"); \
  }

void test_instruction_setup(void)
{
}

void test_instruction_teardown(void)
{
  /* Nothing */
}

// MATH
REG_OPCODE_TEST(MATH, ADD, 1, 2, 3)
REG_OPCODE_TEST(MATH, SUB, 1, 2, 3)
REG_OPCODE_TEST(MATH, MUL, 1, 2, 3)
REG_OPCODE_TEST(MATH, DIV, 1, 2, 3)
REG_OPCODE_TEST(MATH, MOD, 1, 2, 3)
REG_OPCODE_TEST(MATH, SLL, 1, 2, 3)
REG_OPCODE_TEST(MATH, SRL, 1, 2, 3)
REG_OPCODE_TEST(MATH, SRA, 1, 2, 3)
REG_OPCODE_TEST(MATH, AND, 1, 2, 3)
REG_OPCODE_TEST(MATH, OR, 1, 2, 3)
REG_OPCODE_TEST(MATH, XOR, 1, 2, 3)
REG_OPCODE_TEST(MATH, NOT, 1, 2, 3)
REG_OPCODE_TEST(MATH, SLT, 1, 2, 3)
REG_OPCODE_TEST(MATH, SLTU, 1, 2, 3)
REG_OPCODE_TEST(MATH, EQ, 1, 2, 3)

// CFLOW
REG_OPCODE_TEST(CFLOW, JUMP, 1, 2, 3)
REG_OPCODE_TEST(CFLOW, JEQ, 1, 2, 3)

// SYSACC
REG_OPCODE_TEST(SYSACC, LOAD, 1, 2, 3)
REG_OPCODE_TEST(SYSACC, STR, 1, 2, 3)
REG_OPCODE_TEST(SYSACC, SETR, 1, 2, 3)
REG_OPCODE_TEST(SYSACC, IRQ, 1, 2, 3)
REG_OPCODE_TEST(SYSACC, SYSCALL, 1, 2, 3)

// STACK
REG_OPCODE_TEST(STACK, PUSH, 1, 2, 3)
REG_OPCODE_TEST(STACK, POP, 1, 2, 3)

MU_TEST_SUITE(test_instruction_suite)
{
  printf("test_instruction_suite\n");
  MU_SUITE_CONFIGURE(&test_instruction_setup, &test_instruction_teardown);
  GET_TEST_NAME(ADD);

  GET_TEST_NAME(ADD);
  GET_TEST_NAME(SUB);
  GET_TEST_NAME(MUL);
  GET_TEST_NAME(DIV);
  GET_TEST_NAME(MOD);
  GET_TEST_NAME(SLL);
  GET_TEST_NAME(SRL);
  GET_TEST_NAME(SRA);
  GET_TEST_NAME(AND);
  GET_TEST_NAME(OR);
  GET_TEST_NAME(XOR);
  GET_TEST_NAME(NOT);
  GET_TEST_NAME(SLT);
  GET_TEST_NAME(SLTU);
  GET_TEST_NAME(EQ);
  GET_TEST_NAME(JUMP);
  GET_TEST_NAME(JEQ);
  GET_TEST_NAME(LOAD);
  GET_TEST_NAME(STR);
  GET_TEST_NAME(SETR);
  GET_TEST_NAME(IRQ);
  GET_TEST_NAME(SYSCALL);
  GET_TEST_NAME(PUSH);
  GET_TEST_NAME(POP);

  // IMM
  // GET_TEST_NAME(SETU);
  // GET_TEST_NAME(SETL);
}
#endif // TEST_INSTRUCTION_H