#include "../arrays.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize a new void pointer array
ptr_array *ptr_array_new()
{
  ptr_array *array = (ptr_array *)malloc(sizeof(ptr_array));
  if (array == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for the array.\n");
    exit(1);
  }

  array->data = (void **)malloc(sizeof(void *) * INITIAL_CAPACITY);
  if (array->data == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for the data array.\n");
    exit(1);
  }

  array->size = 0;
  array->capacity = INITIAL_CAPACITY;

  return array;
}

void ptr_array_push(ptr_array *array, void *element)
{
  if (array->size >= array->capacity)
  {
    // Automatically resize the array
    array->capacity *= 2;
    void **newData = (void **)realloc(array->data, sizeof(void *) * array->capacity);
    if (newData == NULL)
    {
      fprintf(stderr, "Failed to reallocate memory for the data array.\n");
      exit(1);
    }
    array->data = newData;
  }

  array->data[array->size++] = element;
}

void *ptr_array_pop(ptr_array *array)
{
  if (array->size <= 0)
  {
    fprintf(stderr, "Array is empty. Cannot pop elements.\n");
    return NULL;
  }

  void *poppedElement = array->data[--array->size];

  // Shrink the array if its size is much smaller than its capacity
  if (array->size < array->capacity / 4)
  {
    array->capacity /= 2;
    void **newData = (void **)realloc(array->data, sizeof(void *) * array->capacity);
    if (newData == NULL)
    {
      fprintf(stderr, "Failed to reallocate memory for the data array.\n");
      exit(1);
    }
    array->data = newData;
  }

  return poppedElement;
}

// Set an element at a specific index in the array
void ptr_array_set(ptr_array *array, int index, void *element)
{
  if (index < 0 || index >= array->size)
  {
    fprintf(stderr, "Index out of bounds.\n");
    return;
  }

  array->data[index] = element;
}

// Set an element at a specific index in the array
void *ptr_array_get(ptr_array *array, int index)
{
  if (index < 0 || index >= array->size)
  {
    fprintf(stderr, "Index out of bounds.\n");
    return NULL;
  }
  return array->data[index];
}

// Free the memory used by the array
void ptr_array_free(ptr_array *array)
{
  free(array->data);
  free(array);
}
