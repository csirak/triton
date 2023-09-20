#include "../include/parser.h"
#include <stdlib.h>

ptr_array *parser_parse(ptr_array *tokens)
{
  ptr_array *instructions = ptr_array_new();
  int current_token;
  while (current_token < tokens->size)
  {
  }
}

bool token_is_register(token *token)
{
  return token->type != REGISTER;
}

int *parser_parse_math(token *current_token, ptr_array *tokens, ptr_array *instructions, int current_token_index)
{
  if (current_token->value == NOT)
  {
    token *storage_register = ptr_array_get(tokens, current_token + 1);
    token *operation_parameter_1 = ptr_array_get(tokens, current_token + 2);
    if (!token_is_register(storage_register) || !token_is_register(operation_parameter_1))
    {
      // throw error
    }
  }
}

int *parser_parse_cflow(token *current_token, ptr_array *tokens, ptr_array *instructions, int current_token_index) {}

int *parser_parse_sysacc(token *current_token, ptr_array *tokens, ptr_array *instructions, int current_token_index) {}
