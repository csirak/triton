#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/encoder.h"
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
  if (argc < 3)
  {
    printf("Usage: assembler <file>\n");
    return 1;
  }

  string *source = string_from_file(argv[1]);
  ptr_array *tokens = lexer_tokenize(source);

  parser_context *ctx = parser_parse(tokens);
  encoder_encode(ctx, argv[2], BIN);
  ptr_array *labels = ctx->labels;

  return 0;
}