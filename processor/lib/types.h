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

#endif // TYPES_H