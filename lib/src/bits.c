#include "../bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()

word pushWord(word in_word, word to_push, int offset)
{
  return in_word << offset | to_push;
}

word popWord(word in_word, int offset)
{
  return in_word >> offset;
}

#define MAX_RETRIES 5
#define RETRY_DELAY 1 // in seconds

void *malloc_with_retry(size_t size)
{
  void *ptr = NULL;
  int retries = 0;

  while (!ptr && retries < MAX_RETRIES)
  {
    ptr = malloc(size);
    if (!ptr)
    {
      retries++;
      printf("Memory allocation of size %zu failed. Attempt %d of %d.\n", size, retries, MAX_RETRIES);
      sleep(RETRY_DELAY);
    }
  }

  if (!ptr)
  {
    perror("Failed to allocate memory after multiple attempts");
    exit(EXIT_FAILURE);
  }

  return ptr;
}
