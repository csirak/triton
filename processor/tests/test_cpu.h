#include "minunit.h"

#include "../include/cpu.h"

#ifndef TEST_CPU_H
#define TEST_CPU_H

void test_cpu_setup(void)
{
}

void test_cpu_teardown(void)
{
}

MU_TEST(test_cpu_init)
{
  printf("test_cpu_init\n");
  cpu *core = cpu_create_test();
  cpu_free_test(core);
}

MU_TEST(test_cpu_memory_access)
{
  printf("test_cpu_memory_access\n");

  word address = 0x33d;
  word value = 12423;
  cpu *core = cpu_create_test();
  cpu_write_mem(core, address, value);
  mu_assert(value == cpu_read_mem(core, address), "Memory read/write failed");
  cpu_free_test(core);
}

MU_TEST(test_cpu_reg_access)
{
  printf("test_cpu_reg_access\n");
  cpu *core = cpu_create_test();
  word value = 1231423;
  for (u8 i = 1; i < REGISTERS_COUNT; i++)
  {
    cpu_write_reg(core, i, value);
    mu_assert(value == cpu_read_reg(core, i), "Register read/write failed");
  }
  cpu_free_test(core);
}

MU_TEST_SUITE(test_cpu_suite)
{
  printf("test_cpu_suite\n");
  MU_SUITE_CONFIGURE(&test_cpu_setup, &test_cpu_teardown);
  MU_RUN_TEST(test_cpu_init);
  MU_RUN_TEST(test_cpu_memory_access);
  MU_RUN_TEST(test_cpu_reg_access);
}
#endif // TEST_CPU_H