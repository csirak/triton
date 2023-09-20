#include "../include/lexer.h"
#include "lib/arrays.h"
#include <stdio.h>
#include <stdlib.h>

const char SINGLE_LINE_COMMENT = '#';
const string MULTI_LINE_COMMENT_OPEN = {"/*", 2};
const string MULTI_LINE_COMMENT_CLOSE = {"*/", 2};

const char WHITESPACE[] = {
    ' ',
    '\t',
    '\n',
    '\v',
    '\f',
    '\r'};

const char *OPCODES[] = {
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "sll",
    "srl",
    "sra",
    "and",
    "or",
    "xor",
    "not",
    "slt",
    "sltu",
    "eq",
    "jump",
    "jeq",
    "load",
    "str",
    "setu",
    "setl",
    "setr",
    "irq",
    "syscall",
};

const char *SPECIAL_REGISTERS[] = {
    "z",
    "ra",
    "sp",
    "gp",
    "tp",
    "fp",
    "fg"};

const char *REGISTERS[] = {
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15",
    "r16",
    "r17",
    "r18",
    "r19",
    "r20",
    "r21",
    "r22",
    "r23",
    "r24",
    "r25",
    "r26",
    "r27",
    "r28",
    "r29",
    "r30",
    "r31",
};

const char *SYMBOLS[] = {
    ":",
    ",",
};

const char *TOKEN_TYPES[] = {
    "INSTRUCTION",
    "REGISTER",
    "VALUE",
    "LABEL_DEF",
    "LABEL_CALL"};

bool is_digit(char c)
{
  return c >= '0' && c <= '9';
}

bool is_hex_digit(char c)
{
  return is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

bool is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool is_alpha_num(char c)
{
  return is_alpha(c) || is_digit(c);
}

bool lexer_is_special_register(string *src)
{
  for (int i = 0; i < sizeof(SPECIAL_REGISTERS) / sizeof(SPECIAL_REGISTERS[0]); i++)
  {
    if (string_char_equals(src, SPECIAL_REGISTERS[i]))
    {
      return true;
    }
  }

  return false;
}

bool lexer_is_whitespace(char c)
{
  for (int i = 0; i < sizeof(WHITESPACE); i++)
  {
    if (c == WHITESPACE[i])
    {
      return true;
    }
  }
  return false;
}

bool lexer_is_symbol(char c)
{
  for (int i = 0; i < sizeof(SYMBOLS); i++)
  {
    if (c == SYMBOLS[i])
    {
      return true;
    }
  }
  return false;
}

bool lexer_is_label_def(string *src)
{
  return lexer_is_label_call(src) && string_get_char(src, src->length - 1) == ':';
}

bool lexer_is_label_call(string *src)
{
  if (!is_alpha(string_get_char(src, 0)))
  {
    return false;
  }
  for (int i = 1; i < src->length - 1; i++)
  {
    if (!is_alpha_num(string_get_char(src, 1)))
    {
      return false;
    }
  }
  return true;
}

bool lexer_is_register(string *src)
{
  char char_0 = string_get_char(src, 0);
  char char_1 = string_get_char(src, 1);
  char char_2 = string_get_char(src, 2);

  if (char_0 != 'r' && (src->length != 2 && src->length != 3))
  {
    return false;
  }
  if (src->length == 2)
  {
    return is_digit(char_1);
  }

  return is_digit(char_1) && is_digit(char_2);
}

bool lexer_is_instruction(string *src)
{
  for (int i = 0; i < sizeof(OPCODES) / sizeof(OPCODES[0]); i++)
  {
    if (string_char_equals(src, OPCODES[i]))
    {
      return true;
    }
  }
  return false;
}

bool lexer_is_hex_value(string *src)
{
  if (string_get_char(src, 0) != '0' || string_get_char(src, 1) != 'x')
  {
    return false;
  }

  for (int i = 2; i < src->length; i++)
  {
    if (!is_hex_digit(string_get_char(src, i)))
    {
      return false;
    }
  }
  return true;
}

bool lexer_is_dec_value(string *src)
{
  int i = 0;
  if (string_get_char(src, i) == '-')
  {
    i++;
  }
  for (i; i < src->length; i++)
  {
    if (!is_digit(string_get_char(src, i)))
    {
      return false;
    }
  }
  return true;
}

int lexer_get_register(string *src)
{

  return string_find_in_char_array(src, REGISTERS, 32);
}

int lexer_get_dec_value(string *src)
{
  return (int)strtol(src->data, NULL, 10);
}

int lexer_get_hex_value(string *src)
{
  return (int)strtol(src->data, NULL, 16);
}

int lexer_get_instruction(string *src)
{
  return string_find_in_char_array(src, OPCODES, 24);
}

int lexer_get_special_register(string *src)
{
  return string_find_in_char_array(src, SPECIAL_REGISTERS, 7);
}

token *lexer_get_token(string *src)
{
  token *token_obl = malloc(sizeof(token));

  if (lexer_is_instruction(src))
  {
    token_obl->type = INSTRUCTION;
    token_obl->value = lexer_get_instruction(src);
  }
  else if (lexer_is_register(src))
  {
    token_obl->type = REGISTER;
    token_obl->value = lexer_get_register(src);
  }

  else if (lexer_is_special_register(src))
  {
    token_obl->type = REGISTER;
    token_obl->value = lexer_get_special_register(src);
  }
  else if (lexer_is_dec_value(src))
  {
    token_obl->type = VALUE;
    token_obl->value = lexer_get_dec_value(src);
  }
  else if (lexer_is_hex_value(src))
  {
    token_obl->type = VALUE;
    token_obl->value = lexer_get_hex_value(src);
  }
  else if (lexer_is_label_def(src))
  {
    token_obl->type = LABEL_DEF;
    --src->length;
    token_obl->value = string_hash(src);
    ++src->length;
  }
  else if (lexer_is_label_call(src))
  {
    token_obl->type = LABEL_CALL;
    token_obl->value = string_hash(src);
  }
  else
  {
    // throw error
  }
  return token_obl;
}

ptr_array *lexer_tokenize(string *src)
{
  ptr_array *tokens = ptr_array_new();
  while (src->length > 0)
  {
    string *tok0 = lexer_get_next_token_string(src);
    token *tok = lexer_get_token(tok0);
    ptr_array_push(tokens, tok);
  }
  return tokens;
}

string *lexer_get_next_token_string(string *src)
{
  src = lexer_clear_whitespace(src);
  src = lexer_clear_comment(src);

  int i;
  for (i = 0; i < src->length; i++)
  {
    if (lexer_is_whitespace(string_get_char(src, i)))
    {
      break;
    }
  }
  string *string_token = string_new();

  string_token->data = src->data;
  string_token->length = i;

  string_shift_index(src, i);

  return string_token;
}

string *lexer_clear_whitespace(string *src)
{
  int i;
  for (i = 0; i < src->length; i++)
  {
    if (!lexer_is_whitespace(string_get_char(src, i)))
    {
      break;
    }
  }
  string_shift_index(src, i);
  return src;
}

string *lexer_clear_comment(string *src)
{
  if (src->length == 0)
  {
    return src;
  }
  if (string_get_char(src, 0) == SINGLE_LINE_COMMENT)
  {
    int newline_index = lexer_wait_for_next_char(src, '\n');
    string_shift_index(src, newline_index);
  }
  if (
      string_starts_with(src, &MULTI_LINE_COMMENT_OPEN, 0))
  {
    int close_index = lexer_wait_for_next_string(src, &MULTI_LINE_COMMENT_CLOSE);
    string_shift_index(src, close_index);
  }
  return src;
}

int lexer_wait_for_next_char(string *src, char c)
{
  int i;
  for (i = 0; i < src->length; i++)
  {
    if (string_get_char(src, i) == c)
    {
      return i;
    }
  }
  return -1;
}

int lexer_wait_for_next_string(string *src, string *key)
{
  int i;
  for (i = 0; i < src->length; i++)
  {
    if (string_starts_with(src, key, i))
    {
      return i + key->length;
    }
  }
  return -1;
}