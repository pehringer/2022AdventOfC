#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

//Array
struct array {
  unsigned char *end;
  unsigned char *start;
  int type_size;
};
struct array array_allocate(int type_size, int length);
void array_deallocate(struct array *a);
void array_copy(struct array *a, void *source_start, void *source_end);
void* array_at(struct array *a, int index);
int array_length(struct array *a);

//List, Note supports negative indexes.
struct list {
  struct array a;
  int end;
  int start;
};
struct list list_allocate(int type_size, int length);
struct list list_slice(struct list *l, int index_start, int index_end);
void list_reallocate(struct list *l, int length);
void list_deallocate(struct list *l);
void* list_at(struct list *l, int index);
int list_length(struct list *l);
void list_append(struct list *l, struct list source);
void list_push(struct list *l, void* element);
void* list_pop(struct list *l);
void list_enqueue(struct list *l, void* element);
void* list_dequeue(struct list *l);
int list_sort(struct list *l, int (*compare)(const void *, const void*));

#endif