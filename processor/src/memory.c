#include <stdio.h>
#include <stdlib.h>

#include "../include/memory.h"

memory *memory_create()
{
  memory *mem = malloc_with_retry(sizeof(memory));
  mem->memory = calloc(sizeof(word), MEMORY_SIZE);
  mem->size = MEMORY_SIZE;
  return mem;
}

void memory_free(memory *mem)
{
  free(mem->memory);
  mem->size = 0;
  free(mem);
}

word memory_get(memory *mem, word address)
{
  if (memory_validate_address(address, mem->size))
    return mem->memory[address];

  return 0;
}

void memory_set(memory *mem, word address, word data)
{
  if (memory_validate_address(address, mem->size))
  {
    mem->memory[address] = data;
  };
}

int memory_validate_address(word address, long size)
{
  if (address > size)
  {
    return 0;
  }
  return 1;
}
