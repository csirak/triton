#include "lib/types.h"

#ifndef PARSER_TYPES
#define PARSER_TYPES
typedef struct parser_context
{
  ptr_array *labels;
  ptr_array *tokens;
  int current_index;
  ptr_array *current_label;
  int *current_label_index;
} parser_context;
#endif // PARSER_TYPES