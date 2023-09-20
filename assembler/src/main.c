#include "../include/lexer.h"
#include "../include/parser.h"
#include "lib/strings.h"
#include "lib/arrays.h"
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
    // printf("Type: %s ", types[tok->type]);
    // printf("value: 0x%x\n", tok->value);
  }

  ptr_array *labels = parser_parse(tokens);

  for (int i = 0; i < labels->size; i += 2)
  {
    ptr_array *current_label = ptr_array_get(labels, i);
    int current_label_value = (int)ptr_array_get(labels, i + 1);
    printf("label: 0x%x\n", current_label_value);

    for (int i = 0; i < current_label->size; i++)
    {
      instruction *inst = instruction_decode(ptr_array_get(current_label, i));
      instruction_log(inst);
      if (inst->type == CFLOW)
      {

        ++i;
        printf("jump label: 0x%x\n", ptr_array_get(current_label, i));
      }
      printf("\n");
    }
  }

  return 0;
}