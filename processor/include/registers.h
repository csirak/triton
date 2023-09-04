#include "../lib/types.h"

#ifndef REGISTERS_H
#define REGISTERS_H

void registers_init(register_file *registers);
void register_free(register_file *registers);
word registers_get(register_file *registers, u8 idx);
void print_registers(register_file *registers);
void registers_set(register_file *registers, u8 idx, word data);

#endif // REGISTERS_H
