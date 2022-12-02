#include "vector.h"

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


void main() {
}
