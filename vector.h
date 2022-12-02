#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct vector {
  int capacity;
  void *data;
  int elementSize;
  int size;
};

struct vector construct(int elementSize, int numberOf);

int get_append_element(void *elements, int numberOf);

int get_size(struct vector v);

#endif
