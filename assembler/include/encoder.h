#include "lib/arrays.h"
#include "types.h"

#ifndef ENCODER_H
#define ENCODER_H

void encoder_encode(parser_context *intermediate_representation, char *filename, output_mode mode);
void encoder_encode_to_bin_file(parser_context *intermediate_representation, char *filename);
void encoder_encode_to_txt_file(parser_context *intermediate_representation, char *filename);

#endif // ENCODER_H