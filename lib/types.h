#ifndef TYPES_H
#define TYPES_H

typedef enum
{
  false = 0,
  true = 1
} bool;

typedef struct
{
  void **data;
  int size;
  int capacity;
} ptr_array;

typedef enum token_type
{
  INSTRUCTION,
  REGISTER,
  VALUE,
  LABEL_DEF,
  LABEL_CALL
} token_type;

typedef struct string
{
  char *data;
  int length;
} string;

typedef struct string_arr
{
  string *data;
  int length;
} string_arr;

typedef struct token
{
  token_type type;
  int value;

} token;

typedef struct Lexer
{
  string *value;
  int start;
  int current;
} Lexer;

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
  JUMP,
  JEQ,
  LOAD,
  STR,
  SETU,
  SETL,
  SETR,
  IRQ,
  SYSCALL,
} Instructions;

typedef unsigned char byte;
typedef unsigned int word;
typedef byte u8;

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
  UNKNOWN
} op_type;

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

typedef enum named_registers
{
  Z_REG,
  RA_REG,
  SP_REG,
  GP_REG,
  TP_REG,
  PC_REG,
  FP_REG,
  FG_REG,
  PFG_REG,
  T1_REG
} named_registers;
#endif // TYPES_H