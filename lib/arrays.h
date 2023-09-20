#include "types.h"
#ifndef PTR_ARRAY_H
#define PTR_ARRAY_H

#define INITIAL_CAPACITY 40

ptr_array *ptr_array_new();
void ptr_array_free(ptr_array *array);

void *ptr_array_pop(ptr_array *array);
void *ptr_array_get(ptr_array *array, int index);

void ptr_array_push(ptr_array *array, void *element);
void ptr_array_set(ptr_array *array, int index, void *element);

#endif /* PTR_ARRAY_H */
