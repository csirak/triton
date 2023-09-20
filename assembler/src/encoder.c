#include "../include/encoder.h"
#include "lib/instruction.h"
#include <stdlib.h>
#include <stdio.h>

int get_label_index(parser_context *ctx, int label_value)
{
  for (int i = 1; i < (ctx->labels->size); i += 2)
  {
    if (ptr_array_get(ctx->labels, i) == label_value)
    {
      return i / 2;
    }
  }
  return -1;
}

int get_label_offset(parser_context *ctx, int label_index)
{
  int offset = 0;
  for (int i = 0; i < label_index; i += 2)
  {
    ptr_array *current_label = ptr_array_get(ctx->labels, i);
    offset += current_label->size;
  }
  return offset;
}

int get_context_buffer_size(parser_context *ctx)
{
  int offset = 0;
  for (int i = 0; i < ctx->labels->size; i += 2)
  {
    ptr_array *current_label = ptr_array_get(ctx->labels, i);
    offset += current_label->size;
  }
  return offset;
}

void encoder_clean_context(parser_context *ctx)
{
  for (int i = 0; i < (ctx->labels->size); i += 2)
  {
    ptr_array *current_label = ptr_array_get(ctx->labels, i);
    for (int j = 0; j < current_label->size; j++)
    {
      word encoded_instruction = ptr_array_get(current_label, j);
      instruction *decoded_instruction = instruction_decode(encoded_instruction);
      if (decoded_instruction->opcode == JEQ || decoded_instruction->opcode == JUMP)
      {
        int label_value = ptr_array_get(current_label, j + 1);
        int label_index = get_label_index(ctx, label_value);
        int label_offset = get_label_offset(ctx, label_index);
        // CLEAR JUMP TARGET REGISTER
        instruction set_zero;
        set_zero.type = SYSACC;
        set_zero.opcode = SETR;
        set_zero.param_type = REG;
        set_zero.parameters.reg.r0 = T1_REG;
        set_zero.parameters.reg.r1 = 0;
        word set_zero_encoded = instruction_encode_to_word(&set_zero);

        instruction load_jump_address;
        load_jump_address.type = SYSACC;
        load_jump_address.opcode = SETL;
        load_jump_address.param_type = IMM;
        load_jump_address.parameters.imm.r0 = T1_REG;
        load_jump_address.parameters.imm.imm = label_offset;

        word load_jump_address_encoded = instruction_encode_to_word(&load_jump_address);
        ptr_array_set(current_label, j, set_zero_encoded);
        ptr_array_set(current_label, j + 1, load_jump_address_encoded);
        ptr_array_set(current_label, j + 2, encoded_instruction);
        j += 2;
      }
    }
  }
}

void encoder_encode_to_bin_file(parser_context *intermediate_representation, char *filename)
{
  encoder_clean_context(intermediate_representation);
  int size = get_context_buffer_size(intermediate_representation);

  FILE *file = fopen(filename, "wb"); // Open the file in binary write mode

  if (!file)
  {
    perror("Failed to open file");
    return;
  }

  for (int i = 0; i < intermediate_representation->labels->size; i += 2)
  {
    ptr_array *current_label = ptr_array_get(intermediate_representation->labels, i);
    for (int j = 0; j < current_label->size; j++)
    {
      word line = ptr_array_get(current_label, j);
      fwrite(&line, sizeof(int), 1, file);
    }
  }

  fclose(file);
  return;
}

void encoder_encode_to_txt_file(parser_context *intermediate_representation, char *filename)
{
  encoder_clean_context(intermediate_representation);
  int size = get_context_buffer_size(intermediate_representation);
  FILE *file = fopen(filename, "w"); // Open the file in text mode

  if (!file)
  {
    perror("Failed to open file");
    return;
  }

  for (int i = 0; i < intermediate_representation->labels->size; i += 2)
  {
    ptr_array *current_label = ptr_array_get(intermediate_representation->labels, i);
    for (int j = 0; j < current_label->size; j++)
    {
      word line = ptr_array_get(current_label, j);

      // Write the integer as a 32-bit hex value
      fprintf(file, "0x%08x\n", line);
    }
  }
  fclose(file);
  return;
}

void encoder_encode(parser_context *intermediate_representation, char *filename, output_mode mode)
{
  switch (mode)
  {
  case BIN:
    encoder_encode_to_bin_file(intermediate_representation, filename);
    break;
  case HEX:
    encoder_encode_to_txt_file(intermediate_representation, filename);
    break;
  default:
    break;
  }
}
