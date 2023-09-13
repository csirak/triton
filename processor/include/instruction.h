#include "../lib/types.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

instruction *instruction_decode(word);
void instruction_log(instruction *inst);
void instruction_execute(cpu *cpu, instruction *inst);

word instruction_encode_reg(instruction *inst);
word instruction_encode_imm(instruction *inst);
word instruction_encode_to_word(instruction *inst);


void instruction_decode_math(instruction *inst, word encoded_instruction);
void instruction_decode_cflow(instruction *inst, word encoded_instruction);
void instruction_decode_sysacc(instruction *inst, word encoded_instruction);

void instruction_load_register_params(instruction *inst, word encoded_instruction);
void instruction_load_immediate_params(instruction *inst, word encoded_instruction);


#endif // INSTRUCTION_H
