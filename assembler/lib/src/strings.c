#include "../strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_find_in_char_array(string *src, char *arr[], int arr_length)
{
  for (int i = 0; i < arr_length; i++)
  {
    if (string_char_equals(src, arr[i]))
      return i;
  }
  return -1;
}

string *string_from_file(char *path)
{
  FILE *file = fopen(path, "r");
  if (file == NULL)
  {
    printf("Could not open file %s\n", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(length + 1);
  if (buffer == NULL)
  {
    printf("Could not allocate memory for file %s\n", path);
    fclose(file); // Don't forget to close the file before returning
    return NULL;
  }

  fread(buffer, 1, length, file);
  buffer[length] = '\0';

  fclose(file);

  string *result = string_new();
  if (result == NULL)
  {
    printf("Could not allocate memory for result structure\n");
    free(buffer); // Free the buffer if we can't allocate memory for the result
    return NULL;
  }

  result->data = buffer;
  result->length = length;
  return result;
}

char string_get_char(string *str, int index)
{
  if (index < 0 || index >= str->length)
    return '\0';
  return str->data[index];
}

bool string_equals(string *str1, string *str2)
{
  if (str1->length != str2->length)
    return false;

  for (int i = 0; i < str1->length; i++)
  {
    if (string_get_char(str1, i) != string_get_char(str2, i))
      return false;
  }

  return true;
}

unsigned int string_hash(string *str)
{
  unsigned int hash = 5381; // Initial value
  for (int i = 0; i < str->length; i++)
  {
    hash = ((hash << 5) + hash) + string_get_char(str, i); // hash * 33 + c
  }
  return hash;
}

bool string_is_digit(string *str)
{
  for (int i = 0; i < str->length; i++)
  {
    char c = string_get_char(str, i);
    if (c < '0' || c > '9')
      return false;
  }

  return true;
}

void print_string(string *str)
{
  print_string_offset(str, 0, str->length);
}

void print_string_offset(string *str, int offset, int length)
{
  printf("^");
  for (int i = 0; i < length; i++)
  {
    printf("%c", string_get_char(str, offset + i));
  }
  printf("^");

  printf("\n");
}

bool string_char_equals(string *str, char *c)
{
  size_t c_length = strlen(c);
  if (str->length != c_length)
  {
    return false;
  }
  for (size_t i = 0; i < c_length; i++)
  {
    if (string_get_char(str, i) != c[i])
    {
      return false;
    }
  }

  return true;
}

string *string_new()
{
  return malloc(sizeof(string));
}

void string_free(string *str)
{
  if (str->data)
  {
    free(str->data);
  }
  free(str);
}

bool string_starts_with(string *src, string *key, int offset)
{
  for (int i = 0; i < key->length; i++)
  {
    if (offset + i >= src->length || string_get_char(src, i + offset) != string_get_char(key, i))
    {
      return false;
    }
  }

  return true;
}

bool string_starts_with_char(string *src, char *key)
{
  for (int i = 0; key[i]; i++)
  {
    if (string_get_char(src, i) != string_get_char(key, i))
    {
      return false;
    }
  }
  return true;
}

void string_load_char_ptr(string *dest, char *src)
{
  dest->length = strlen(src);
  dest->data = src;
}

void string_shift_index(string *str, int index)
{
  str->data = &str->data[index];
  str->length -= index;
}