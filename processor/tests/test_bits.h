#include "minunit.h"

#include "../lib/bits.h"
#include "../lib/types.h"

#ifndef TEST_BITS_H
#define TEST_BITS_H

void test_bits_setup(void)
{
}

void test_bits_teardown(void)
{
}

MU_TEST(test_bits6)
{
  printf("test_bits6\n");
  word base = 0x3f;
  word w = base;
  for (int i = 0; i < 5; i++)
  {
    mu_assert(BIT6(w, i) == base, "");
    w = w << 6;
  }
}

MU_TEST(test_bit)
{
  printf("test_bit\n");
  word base = 0xFF;
  word w = base;
  for (int i = 0; i < 8; i++)
  {
    mu_assert(BIT(w, i) == 1, "");
    w = w << 1;
  }
}

MU_TEST(test_byte)
{
  printf("test_byte\n");
  word base = 0xFFFFFFFF;
  word w = base;
  for (int i = 0; i < 3; i++)
  {
    mu_assert(BYTE(w, i) == 0xFF, "");
    w = w << 8;
  }
}

MU_TEST(test_bytes2)
{
  printf("test_bytes2\n");
  word base = 0xFFFFFFFF;
  word w = base;
  for (int i = 0; i < 2; i++)
  {
    mu_assert(BYTES2(w, i) == 0xFFFF, "");
    w = w << 1;
  }
}

MU_TEST(test_pushword)
{
  word a = 0xFF;
  a = pushWord(a, 0xAFAF, 16);
  mu_assert(a == 0xFFAFAF, "Faild to push word");

  a = 0xFF;
  a = pushWord(a, 0x0f, 6);
  mu_assert(BIT6(a, 0) == 0x0f, "Faild to push word");
}

MU_TEST_SUITE(test_bits_suite)
{
  printf("test_bits_suite\n");
  MU_SUITE_CONFIGURE(&test_bits_setup, &test_bits_teardown);

  MU_RUN_TEST(test_bit);
  MU_RUN_TEST(test_bits6);
  MU_RUN_TEST(test_byte);
  MU_RUN_TEST(test_bytes2);
  MU_RUN_TEST(test_pushword);
}
#endif // TEST_BITS_H