#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct array {
  unsigned char *start;
  unsigned char *end;
  int type_size;
};

struct array array_allocate(int type_size, int length);

void array_deallocate(struct array a);

void array_copy(struct array a, void *source_start, void *source_end);

void* array_at(struct array a, int index);

int array_length(struct array a);

#endif
