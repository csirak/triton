#include "../include/lexer.h"
#include "../include/parser.h"
#include "../lib/strings.h"
#include "../lib/arrays.h"
#include <stdio.h>
#include <stdlib.h>

const char *types[] = {
    "INSTRUCTION",
    "REGISTER",
    "VALUE",
    "LABEL"};

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Usage: assembler <file>\n");
    return 1;
  }

  string *source = string_from_file(argv[1]);
  ptr_array *tokens = lexer_tokenize(source);

  for (int i = 0; i < tokens->size; i++)
  {
    token *tok = (token *)ptr_array_get(tokens, i);
    printf("Type: %s ", types[tok->type]);
    printf("value: 0x%x\n", tok->value);
  }

  ptr_array *intstructions = parser_parse(tokens);
  return 0;
}