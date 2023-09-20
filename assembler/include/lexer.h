#include "../lib/types.h"
#include "../lib/strings.h"

#ifndef LEXER_H
#define LEXER_H

bool lexer_is_symbol(char c);
bool lexer_is_whitespace(char c);

bool lexer_is_value(string *src);
bool lexer_is_label(string *src);
bool lexer_is_register(string *src);
bool lexer_is_hex_value(string *src);
bool lexer_is_dec_value(string *src);
bool lexer_is_instruction(string *src);
bool lexer_is_special_register(string *src);

int lexer_get_register(string *src);
int lexer_get_dec_value(string *src);
int lexer_get_hex_value(string *src);
int lexer_get_instruction(string *src);
int lexer_get_special_register(string *src);

token *lexer_get_token(string *src);

ptr_array *lexer_tokenize(string *src);

string *lexer_get_next_token_string(string *src);
string *lexer_clear_comment(string *src);
string *lexer_clear_whitespace(string *src);

int lexer_wait_for_next_char(string *src, char c);
int lexer_wait_for_next_string(string *src, string *key);

#endif // LEXER_H