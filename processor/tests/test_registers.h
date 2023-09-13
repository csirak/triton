#include "minunit.h"
#include <stdlib.h>

#include "../include/registers.h"

static word regIdx = 7;
static word regValue = 4;

void test_reg_setup(void)
{
}

void test_reg_teardown(void)
{
  /* Nothing */
}

MU_TEST(test_registers_init)
{
  printf("test_registers_init\n");
  register_file *regs = registers_create();
  for (int i = 0; i < REGISTERS_COUNT; i++)
  {
    mu_assert_int_eq(0, registers_get(regs, i));
  }
  registers_free(regs);
}

MU_TEST(test_registers_access)
{
  printf("test_registers_access\n");
  register_file *regs = registers_create();

  registers_set(regs, regIdx, regValue);
  mu_assert_int_eq(regValue, registers_get(regs, regIdx));
  registers_free(regs);
}

MU_TEST(test_registers_set)
{
  printf("test_registers_set\n");
  register_file *regs = registers_create();

  registers_set(regs, regIdx, regValue);
  mu_assert(0 != registers_get(regs, regIdx), "registers_set failed");
  registers_free(regs);
}

MU_TEST_SUITE(test_reg_suite)
{
  printf("test_reg_suite\n");
  MU_SUITE_CONFIGURE(&test_reg_setup, &test_reg_teardown);

  MU_RUN_TEST(test_registers_init);
  MU_RUN_TEST(test_registers_access);
  MU_RUN_TEST(test_registers_set);
}
