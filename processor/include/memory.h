#include "../include/types.h"
#include "lib/bits.h"

#ifndef MEMORY_H
#define MEMORY_H

memory *memory_create();
void memory_free(memory *mem);

word memory_get(memory *mem, word address);
void memory_set(memory *mem, word address, word data);

word *memory_get_address_pointer(memory *mem, word address);
int memory_validate_address(word address, long size);

#endif // MEMORY_H
