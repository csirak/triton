#include "bits.h"

word pushWord(word in_word, word to_push, int offset)
{
  return in_word << offset | to_push;
}

word popWord(word in_word, int offset)
{
  return in_word >> offset;
}