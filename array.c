#include"data_structures.h"

struct array array_allocate(int type_size, int length) {
  length = length * type_size;
  unsigned char *start = malloc(length);
  struct array a = {start + length, start, type_size};
  return a;
}

void array_deallocate(struct array *a) {
  free(a->start);
}

void array_copy(struct array *a, int start_index, void *source_start, void *source_end) {
  unsigned char *source = source_start;
  unsigned char *destination = (unsigned char*) a->start + (start_index * a->type_size);
  while(destination < a->end && source < (unsigned char*) source_end)
    *(destination++) = *(source++);
}

void* array_at(struct array *a, int index) {
  return a->start + (index * a->type_size);
}

int array_length(struct array *a) {
  return (a->end - a->start) / a->type_size;
}
