#include "bits.h"

word pushWord(word in_word, word to_push, int offset)
{
  return in_word << offset | to_push;
}