#include "../include/parser.h"
#include <stdlib.h>
#include <stdio.h>

token *parser_get_next(parser_context *ctx)
{
  ++ctx->current_index;
  return ptr_array_get(ctx->tokens, ctx->current_index);
}

parser_context *parser_parse(ptr_array *tokens)
{

  ptr_array *labels = ptr_array_new();
  parser_context *context = malloc(sizeof(parser_context));

  context->current_index = 0;
  context->current_label = NULL;
  context->labels = labels;
  context->tokens = tokens;

  while (context->current_index < context->tokens->size)
  {
    token *current_token = ptr_array_get(context->tokens, context->current_index);

    switch (current_token->type)
    {
    case INSTRUCTION:
    {
      parser_parse_instruction(context);
      break;
    }
    case LABEL_DEF:
    {
      parser_parse_label_def(context);
      break;
    }
    default:
      printf("FAIL: %d", current_token->type);
      // throw error
      return labels;
      break;
    }
  }

  return context;
}

void parser_parse_instruction(parser_context *ctx)
{

  token *current_token = ptr_array_get(ctx->tokens, ctx->current_index);

  int current_token_value = current_token->value;
  if (current_token_value >= ADD && current_token_value <= EQ)
  {
    return parser_parse_math(ctx);
  }
  else if (current_token_value == JUMP || current_token_value == JEQ)
  {
    return parser_parse_cflow(ctx);
  }
  else if (current_token_value >= LOAD && current_token_value <= SYSCALL)
  {
    return parser_parse_sysacc(ctx);
  }
  else
  {
    // throw error
  }
}

void parser_parse_label_def(parser_context *ctx)
{
  token *current_token = (token *)ptr_array_get(ctx->tokens, ctx->current_index);

  ptr_array *new_label_scope = ptr_array_new();
  ctx->current_label = new_label_scope;
  ++ctx->current_label_index;
  ptr_array_push(ctx->labels, ctx->current_label);
  ptr_array_push(ctx->labels, current_token->value);
  ++ctx->current_index;
}

void parser_parse_math(parser_context *ctx)
{
  token *current_token = (token *)ptr_array_get(ctx->tokens, ctx->current_index);

  instruction inst;
  inst.opcode = current_token->value;
  inst.type = MATH;
  inst.param_type = REG;

  token *storage_register = parser_get_next(ctx);
  token *operation_parameter = parser_get_next(ctx);

  if (!storage_register->type != REGISTER || !operation_parameter->type != REGISTER)
  {
    // throw error
  }
  inst.parameters.reg.r0 = storage_register->value;
  inst.parameters.reg.r1 = operation_parameter->value;
  if (inst.opcode != NOT)
  {
    token *operation_parameter_2 = parser_get_next(ctx);
    if (!storage_register->type != REGISTER || !operation_parameter->type != REGISTER || !operation_parameter_2->type != REGISTER)
    {
      // throw error
    }
    inst.parameters.reg.r2 = operation_parameter_2->value;
  }

  word encoded_instruction = instruction_encode_to_word(&inst);
  ptr_array_push(ctx->current_label, (void *)encoded_instruction);
  ++ctx->current_index;
}

void parser_parse_cflow(parser_context *ctx)
{
  token *current_token = (token *)ptr_array_get(ctx->tokens, ctx->current_index);
  instruction inst;

  inst.opcode = current_token->value;
  inst.type = CFLOW;
  inst.param_type = REG;

  token *jump_label = parser_get_next(ctx);
  token *comparision_left;
  token *comparision_right;
  inst.parameters.reg.r0 = T1_REG;
  if (jump_label->type != LABEL_CALL)
  {
  }

  if (inst.opcode == JEQ)
  {
    comparision_left = parser_get_next(ctx);
    comparision_right = parser_get_next(ctx);
    if (!comparision_left->type != REGISTER || !comparision_right->type != REGISTER)
    {
      // throw error
    }

    inst.parameters.reg.r1 = comparision_left->value;
    inst.parameters.reg.r2 = comparision_right->value;
  }

  word encoded_instruction = instruction_encode_to_word(&inst);
  ptr_array_push(ctx->current_label, encoded_instruction);
  ptr_array_push(ctx->current_label, jump_label->value);
  // left empty will be replaced by instruction
  ptr_array_push(ctx->current_label, 0);

  ++ctx->current_index;
}

void parser_parse_sysacc(parser_context *ctx)
{
  token *current_token = (token *)ptr_array_get(ctx->tokens, ctx->current_index);
  instruction inst;
  inst.opcode = current_token->value;
  inst.type = SYSACC;
  inst.param_type = REG;
  if (inst.opcode == IRQ || inst.opcode == SYSCALL)
  {
    inst.parameters.reg.r0 = parser_get_next(ctx)->value;
  }
  else if (inst.opcode == SETU || inst.opcode == SETL)
  {
    inst.param_type = IMM;
    token *storage_register = parser_get_next(ctx);
    token *imm_value = parser_get_next(ctx);

    inst.parameters.imm.r0 = storage_register->value;
    inst.parameters.imm.imm = imm_value->value;
  }
  else
  {
    token *storage_register = parser_get_next(ctx);
    token *data_register = parser_get_next(ctx);

    inst.parameters.reg.r0 = storage_register->value;
    inst.parameters.reg.r1 = data_register->value;
  }

  word encoded_instruction = instruction_encode_to_word(&inst);
  ptr_array_push(ctx->current_label, (void *)encoded_instruction);
  ++ctx->current_index;
}
