#include "test_memory.h"
#include "test_registers.h"
#include "test_cpu.h"
#include "test_bits.h"
#include "test_instructions.h"

int main(int argc, char *argv[])
{
  MU_RUN_SUITE(test_memory_suite);
  MU_RUN_SUITE(test_reg_suite);
  MU_RUN_SUITE(test_cpu_suite);
  MU_RUN_SUITE(test_bits_suite);
  MU_RUN_SUITE(test_instruction_suite);
  MU_REPORT();
  return MU_EXIT_CODE;
}
