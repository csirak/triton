#include "lib/types.h"
#include "lib/instruction.h"
#include "types.h"
#include "lib/arrays.h"

#ifndef PARSER_H
#define PARSER_H

ptr_array *parser_parse(ptr_array *tokens);
token *parser_get_next(parser_context *ctx);

void parser_parse_instruction(parser_context *ctx);
void parser_parse_label_def(parser_context *ctx);

void parser_parse_cflow(parser_context *ctx);
void parser_parse_math(parser_context *ctx);
void parser_parse_sysacc(parser_context *ctx);

#endif // PARSER_H