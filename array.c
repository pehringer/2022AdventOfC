#include "data_structures.h"
#include "stdio.h"
/*
struct vector construct(int elementSize, int numberOf) {
  struct vector v = {numberOf * 2 * elementSize, 0,
                     elementSize, numberOf * elementSize};
  v.data = malloc(v.capacity * v.elementSize);
}

void append(struct vector v, void *elements, int numberOf) {
  int newSize = v.size + (numberOf * v.elementSize);
  if(newSize > v.capacity) {
     v.capacity = newSize*2;
     void *newData = malloc(v.capacity);
     for(int i = 0; i < v.size; i++)
	*((unsigned char*) newData + i) = *((unsigned char*) v.data + i);
     v.data = newData;
     free(v.data);
  }
  for(int i = 0; i < numberOf; i++, v.size++)
     *(((unsigned char*) v.data) + v.size) = *(((unsigned char*) elements) + i);
}

int get_size(struct vector v) {
    return v.size / v.elementSize;
}
*/

struct array array_allocate(int type_size, int length) {
  length = length * type_size;
  unsigned char *start = malloc(length);
  struct array a = {start, start + length, type_size};
  return a;
}

void array_deallocate(struct array a) {
  free(a.start);
}

void array_copy(struct array a, void *source_start, void *source_end) {
  unsigned char *source = source_start;
  unsigned char *destination = (unsigned char*) a.start;
  while(destination < a.end && source < (unsigned char*) source_end)
    *(destination++) = *(source++);
}

void* array_at(struct array a, int index) {
  return a.start + (index * a.type_size);
}

int array_length(struct array a) {
  return (a.end - a.start) / a.type_size;
}

void main() {
  int in[] = {0, 1, 2, 3, 4, 5};
  struct array arr = array_allocate(sizeof(int), 8);
  array_copy(arr, in, in + 6);

  for(int i = 0; i < array_length(arr); i++)
    printf("%d, ", *((int*)array_at(arr, i)));
  printf("\n");

  struct array new_arr = array_allocate(sizeof(int), 4);
  array_copy(new_arr, array_at(arr, 0), array_at(arr, 4));
  for(int i = 0; i < array_length(new_arr); i++)
    printf("%d, ", *((int*)array_at(new_arr, i)));
  printf("\n");
}
