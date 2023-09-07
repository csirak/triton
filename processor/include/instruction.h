#include "../lib/types.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

word instruction_encode_to_word(instruction *inst);
word instruction_encode_reg(instruction *inst);
word instruction_encode_imm(instruction *inst);
word instruction_execute(cpu *cpu, instruction *inst);

instruction *instruction_decode(word);
void instruction_decode_math(instruction *inst, word encoded_instruction);
void instruction_decode_cflow(instruction *inst, word encoded_instruction);
void instruction_decode_sysacc(instruction *inst, word encoded_instruction);
void instruction_decode_stack(instruction *inst, word encoded_instruction);

void instruction_load_register_params(instruction *inst, word encoded_instruction);
void instruction_load_immediate_params(instruction *inst, word encoded_instruction);

void instruction_log(instruction *inst);

#endif // INSTRUCTION_H
