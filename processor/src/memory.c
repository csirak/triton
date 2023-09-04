#include "../include/memory.h"
#include <stdlib.h>
#include <stdio.h>

void memory_init(memory *mem)
{
  mem->memory = malloc(sizeof(word) * MEMORY_SIZE);
  mem->size = MEMORY_SIZE;
}

void memory_free(memory *mem)
{
  free(mem->memory);
  mem->size = 0;
}

word memory_get(memory *mem, word address)
{
  if (validateAddress(address, mem->size))
    return mem->memory[address];

  return 0;
}

void memory_set(memory *mem, word address, word data)
{
  if (validateAddress(address, mem->size))
  {
    mem->memory[address] = data;
  };
}

int validateAddress(word address, long size)
{
  if (address >= size)
  {
    return 0;
  }
  return 1;
}
