#ifndef TYPES_H
#define TYPES_H
#define MEMORY_SIZE 1024
#define REGISTERS_COUNT (32)

typedef unsigned char byte;
typedef unsigned int word;
typedef byte u8;

typedef struct register_file
{
  word *regs;
  long size;
} register_file;

typedef struct memory
{
  word *memory;
  long size;
} memory;

typedef struct cpu
{
  register_file *registers;
  memory *memory;

} cpu;

typedef enum named_registers
{
  Z_REG,
  RA_REG,
  SP_REG,
  GP_REG,
  TP_REG,
  PC_REG,
  FP_REG,
  FG_REG
} named_registers;

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
#endif // TYPES_H