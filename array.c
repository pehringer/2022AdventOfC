#include"data_structures.h"

struct array array_allocate(int type_size, int length) {
  length = length * type_size;
  unsigned char *start = malloc(length);
  struct array arr = {start + length, start, type_size};
  return arr;
}

void array_deallocate(struct array *arr) {
  free(arr->start);
}

void array_copy(struct array *arr, int start_index, void *source_start, void *source_end) {
  unsigned char *source = source_start;
  unsigned char *destination = arr->start + (start_index * arr->type_size);
  while(destination < arr->end && source < (unsigned char*) source_end)
    *(destination++) = *(source++);
}

void* array_at(struct array *arr, int index) {
  return arr->start + (index * arr->type_size);
}

void array_get(struct array *arr, int index, void *element) {
  unsigned char *source = array_at(arr, index);
  unsigned char *destination = element;
  for(int copy = 0; copy < arr->type_size; copy++)
    *(destination++) = *(source++);
}

void array_set(struct array *arr, int index, void *element) {
  unsigned char *source = element;
  unsigned char *destination = array_at(arr, index);
  for(int copy = 0; copy < arr->type_size; copy++)
    *(destination++) = *(source++);
}

int array_length(struct array *arr) {
  return (arr->end - arr->start) / arr->type_size;
}
