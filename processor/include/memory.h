#include "../lib/types.h"

#ifndef MEMORY_H
#define MEMORY_H

void memory_init(memory *mem);
void memory_free(memory *mem);
word memory_get(memory *mem, word address);
void memory_set(memory *mem, word address, word data);
int validateAddress(word address, long size);

#endif // MEMORY_H
