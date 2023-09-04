#include "types.h"

#ifndef BITS_H
#define BITS_H

#define BIT(in_word, idx) ((in_word >> idx) & 1)
#define BIT6(in_word, idx) ((in_word >> (idx * 6)) & 0x3F)

#define BYTE(in_word, idx) ((in_word >> (idx * 8)) & 0xFF)
#define BYTES2(in_word, idx) ((in_word >> (idx * 16)) & 0xFFFF)

word pushWord(word in_word, word to_push, int offset);

#endif // BITS_H