#include "minunit.h"
#include "../include/instruction.h"

#ifndef TEST_INSTRUCTION_H
#define TEST_INSTRUCTION_H
#define GET_DECODE_TEST_NAME(opcode) MU_RUN_TEST(test_instructions_decode_##opcode);
#define GET_EXEC_TEST_NAME(op_tag, op_code) MU_RUN_TEST(test_instructions_exec_##op_code##op_tag);
typedef enum test_type
{
  STD,
  OVFLW,
  ZERO,
} test_type;

#define REG_OPCODE_DECODE_TEST(op_type, op_code, r0_value, r1_value, r2_value)                     \
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

#define IMM_OPCODE_DECODE_TEST(op_type, op_code, r0_value, imm_value)                                 \
                                                                                                      \
  MU_TEST(test_instructions_decode_##op_code)                                                         \
  {                                                                                                   \
    printf("test_instructions_decode_%s\n", #op_code);                                                \
    instruction test_##op_code = {op_type, op_code, IMM};                                             \
    test_##op_code.parameters.imm.r0 = r0_value;                                                      \
    test_##op_code.parameters.imm.imm = imm_value;                                                    \
    word encoded_instruction = instruction_encode_to_word(&test_##op_code);                           \
    instruction *decoded_instruction = instruction_decode(encoded_instruction);                       \
    mu_assert(decoded_instruction->opcode == op_code, "Instruction decode failed");                   \
    mu_assert(decoded_instruction->type == op_type, "Operation decode failed");                       \
    mu_assert(decoded_instruction->parameters.imm.r0 == r0_value, "Register param decode failed");    \
    mu_assert(decoded_instruction->parameters.imm.imm == imm_value, "Immediate param decode failed"); \
  }

#define REG_OPCODE_EXECUTE_TEST(op_tag, op_code, r1_value, r2_value, value_com)            \
                                                                                           \
  MU_TEST(test_instructions_exec_##op_code##op_tag)                                        \
  {                                                                                        \
    printf("test_instruction_exec_%s_%s\n", #op_code, #op_tag);                            \
    cpu *cpu = malloc(sizeof(cpu));                                                        \
    cpu_init(cpu);                                                                         \
    cpu_write_reg(cpu, 2, r1_value);                                                       \
    cpu_write_reg(cpu, 3, r2_value);                                                       \
    instruction test_add = {MATH, op_code, REG, {{1, 2, 3}}};                              \
    instruction_execute(cpu, &test_add);                                                   \
    mu_assert(cpu_read_reg(cpu, 1) value_com, sprintf("%s %s failed", #op_code, #op_tag)); \
  }

void test_instruction_setup(void)
{
}

void test_instruction_teardown(void)
{
  /* Nothing */
}

// MATH
REG_OPCODE_DECODE_TEST(MATH, ADD, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SUB, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, MUL, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, DIV, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, MOD, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SLL, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SRL, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SRA, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, AND, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, OR, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, XOR, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, NOT, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SLT, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, SLTU, 1, 2, 3)
REG_OPCODE_DECODE_TEST(MATH, EQ, 1, 2, 3)

// CFLOW
REG_OPCODE_DECODE_TEST(CFLOW, JUMP, 1, 2, 3)
REG_OPCODE_DECODE_TEST(CFLOW, JEQ, 1, 2, 3)

// SYSACC
REG_OPCODE_DECODE_TEST(SYSACC, LOAD, 1, 2, 3)
REG_OPCODE_DECODE_TEST(SYSACC, STR, 1, 2, 3)
REG_OPCODE_DECODE_TEST(SYSACC, SETR, 1, 2, 3)
REG_OPCODE_DECODE_TEST(SYSACC, IRQ, 1, 2, 3)
REG_OPCODE_DECODE_TEST(SYSACC, SYSCALL, 1, 2, 3)

// IMM SYSACC
IMM_OPCODE_DECODE_TEST(SYSACC, SETU, 1, 213)
IMM_OPCODE_DECODE_TEST(SYSACC, SETL, 1, 213)

// STACK
REG_OPCODE_DECODE_TEST(STACK, PUSH, 1, 2, 3)
REG_OPCODE_DECODE_TEST(STACK, POP, 1, 2, 3)

REG_OPCODE_EXECUTE_TEST(STD, ADD, 0x21, 0x48, == 0x69)
REG_OPCODE_EXECUTE_TEST(STD, SUB, 0x69, 0x48, == 0x21)
REG_OPCODE_EXECUTE_TEST(STD, MUL, 0x69, 0x48, == 0x69 * 0x48)
REG_OPCODE_EXECUTE_TEST(STD, MOD, 0x69, 0x48, == 0x69 % 0x48)
REG_OPCODE_EXECUTE_TEST(STD, DIV, 0x69, 0x48, == (0x69 / 0x48))
REG_OPCODE_EXECUTE_TEST(STD, SLL, 0x69, 2, == 0x69 << 2)
REG_OPCODE_EXECUTE_TEST(STD, SRL, 0x69, 2, == 0x69 >> 2)
REG_OPCODE_EXECUTE_TEST(STD, SRA, (-69), 2, == (-69) >> 2)
REG_OPCODE_EXECUTE_TEST(STD, AND, 0x21, 0x48, == (0x21 & 0x48))
REG_OPCODE_EXECUTE_TEST(STD, OR, 0x21, 0x48, == (0x21 | 0x48))
REG_OPCODE_EXECUTE_TEST(STD, XOR, 0x21, 0x48, == (0x21 ^ 0x48))
REG_OPCODE_EXECUTE_TEST(STD, NOT, 0x21, 0, == ~0x21)
REG_OPCODE_EXECUTE_TEST(STD, SLT, -21, 0, == 1)
REG_OPCODE_EXECUTE_TEST(STD, SLTU, 21, 48, == 1)

REG_OPCODE_EXECUTE_TEST(ZERO, ADD, 21, (-21), == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SUB, 0x69, 0x69, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, MUL, 0x69, 0, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, DIV, 0x69, 0, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, MOD, 0x69, 0x69, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SLL, 0, 2, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SRL, 100, 10, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SRA, (0b111), 3, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, AND, 0x21, 0, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, OR, 0, 0, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, XOR, 1, 1, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, NOT, 0xFFFFFFFF, 0, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SLT, 21, -48, == 0)
REG_OPCODE_EXECUTE_TEST(ZERO, SLTU, 21, 0, == 0)

REG_OPCODE_EXECUTE_TEST(OVFLW, ADD, 0xFFFFFFFF, 0xFFFFFFF, < 0xFFFFFFFF)
REG_OPCODE_EXECUTE_TEST(OVFLW, MUL, 0xFFFFFFFF, 4, < 0xFFFFFFFF)
REG_OPCODE_EXECUTE_TEST(OVFLW, SLL, 0xFFFFFFFF, 0xFF, == 0xFFFFFF00)

// ADD
// SUB
// MUL
// DIV
// MOD
// SLL
// SRL
// SRA
// AND
// OR
// XOR
// NOT
// SLT
// SLTU
// EQ

MU_TEST_SUITE(test_instruction_suite)
{
  printf("test_instruction_suite\n");
  MU_SUITE_CONFIGURE(&test_instruction_setup, &test_instruction_teardown);

  // REGISTER INSTRUCTIONS
  GET_DECODE_TEST_NAME(ADD);
  GET_DECODE_TEST_NAME(SUB);
  GET_DECODE_TEST_NAME(MUL);
  GET_DECODE_TEST_NAME(DIV);
  GET_DECODE_TEST_NAME(MOD);
  GET_DECODE_TEST_NAME(SLL);
  GET_DECODE_TEST_NAME(SRL);
  GET_DECODE_TEST_NAME(SRA);
  GET_DECODE_TEST_NAME(AND);
  GET_DECODE_TEST_NAME(OR);
  GET_DECODE_TEST_NAME(XOR);
  GET_DECODE_TEST_NAME(NOT);
  GET_DECODE_TEST_NAME(SLT);
  GET_DECODE_TEST_NAME(SLTU);
  GET_DECODE_TEST_NAME(EQ);
  GET_DECODE_TEST_NAME(JUMP);
  GET_DECODE_TEST_NAME(JEQ);
  GET_DECODE_TEST_NAME(LOAD);
  GET_DECODE_TEST_NAME(STR);
  GET_DECODE_TEST_NAME(SETR);
  GET_DECODE_TEST_NAME(IRQ);
  GET_DECODE_TEST_NAME(SYSCALL);
  GET_DECODE_TEST_NAME(PUSH);
  GET_DECODE_TEST_NAME(POP);

  // IMMEDIATE INSTRUCTIONS
  GET_DECODE_TEST_NAME(SETU);
  GET_DECODE_TEST_NAME(SETL);

  // EXECUTE MATH STD
  GET_EXEC_TEST_NAME(STD, ADD);
  GET_EXEC_TEST_NAME(STD, SUB);
  GET_EXEC_TEST_NAME(STD, MUL);
  GET_EXEC_TEST_NAME(STD, DIV);
  GET_EXEC_TEST_NAME(STD, SLL);
  GET_EXEC_TEST_NAME(STD, SRL);
  GET_EXEC_TEST_NAME(STD, SRA);
  GET_EXEC_TEST_NAME(STD, AND);
  GET_EXEC_TEST_NAME(STD, OR);
  GET_EXEC_TEST_NAME(STD, XOR);
  GET_EXEC_TEST_NAME(STD, NOT);
  GET_EXEC_TEST_NAME(STD, SLT);
  GET_EXEC_TEST_NAME(STD, SLTU);

  // EXECUTE MATH ZERO EXPECTED
  GET_EXEC_TEST_NAME(ZERO, ADD);
  GET_EXEC_TEST_NAME(ZERO, SUB);
  GET_EXEC_TEST_NAME(ZERO, MUL);
  GET_EXEC_TEST_NAME(ZERO, DIV);
  GET_EXEC_TEST_NAME(ZERO, SLL);
  GET_EXEC_TEST_NAME(ZERO, SRL);
  GET_EXEC_TEST_NAME(ZERO, SRA);
  GET_EXEC_TEST_NAME(ZERO, AND);
  GET_EXEC_TEST_NAME(ZERO, OR);
  GET_EXEC_TEST_NAME(ZERO, XOR);
  GET_EXEC_TEST_NAME(ZERO, NOT);
  GET_EXEC_TEST_NAME(ZERO, SLT);
  GET_EXEC_TEST_NAME(ZERO, SLTU);

  GET_EXEC_TEST_NAME(OVFLW, ADD);
  GET_EXEC_TEST_NAME(OVFLW, MUL);
}
#endif // TEST_INSTRUCTION_H