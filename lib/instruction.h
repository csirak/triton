#include "types.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

instruction *instruction_new(word);
instruction *instruction_decode(word);

Instructions instruction_decode_opcode(word);

void instruction_log(instruction *inst);

word instruction_encode_reg(instruction *inst);
word instruction_encode_imm(instruction *inst);
word instruction_encode_to_word(instruction *inst);

void instruction_load_register_params(instruction *inst, word encoded_instruction);
void instruction_load_immediate_params(instruction *inst, word encoded_instruction);

#endif // INSTRUCTION_H
