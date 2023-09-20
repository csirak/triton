#include "lib/minunit.h"

#include <stdlib.h>

#include "../include/memory.h"

#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

void test_mem_setup(void)
{
}

void test_mem_teardown(void)
{
}

MU_TEST(test_memory_init)
{
  printf("test_memory_init\n");
  memory *mem = memory_create();
  memory_free(mem);
}

MU_TEST(test_memory_access)
{
  printf("test_memory_access\n");
  memory *mem = memory_create();
  word address = 0x013d;
  word value = 1231423;
  memory_set(mem, address, value);
  mu_assert(value == memory_get(mem, address), "memory_get failed");
  memory_free(mem);
}

MU_TEST(test_memory_set)
{
  printf("test_memory_set\n");
  memory *mem = memory_create();
  word address = 0x013d;
  word value = 1231423;
  memory_set(mem, address, value);
  mu_assert(0 != memory_get(mem, address), "memory_set failed");
  memory_free(mem);
}

MU_TEST_SUITE(test_memory_suite)
{
  printf("test_memory_suite\n");
  MU_SUITE_CONFIGURE(&test_mem_setup, &test_mem_teardown);
  MU_RUN_TEST(test_memory_init);
  MU_RUN_TEST(test_memory_access);
  MU_RUN_TEST(test_memory_set);
}
#endif // TEST_MEMORY_H