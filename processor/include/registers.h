#include "../include/types.h"
#include "lib/bits.h"

#ifndef REGISTERS_H
#define REGISTERS_H

register_file *registers_create();
void registers_free(register_file *registers);

word registers_get(register_file *registers, u8 idx);
void registers_set(register_file *registers, u8 idx, word data);

void print_registers(register_file *registers);

#endif // REGISTERS_H
