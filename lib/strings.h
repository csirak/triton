#include "types.h"

#ifndef STRINGS_H
#define STRINGS_H

string *string_new();
void string_free(string *str);

string *string_from_file(char *path);
void string_load_char_ptr(string *dest, char *src);

bool string_equals(string *str1, string *str2);
bool string_char_equals(string *str, char *c);
bool string_is_digit(string *str);
bool string_is_char(string *str);

char string_get_char(string *str, int index);

bool string_starts_with(string *src, string *key, int offset);
bool string_starts_with_char(string *src, char *key);

void print_string(string *str);
void print_string_offset(string *str, int offset, int length);

unsigned int string_hash(string *str);

int string_find_in_char_array(string *src, char *arr[], int arr_length);
void string_shift_index(string *str, int index);
void string_push_char(string *s, char c);
#endif // STRINGS_H