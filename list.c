#include"data_structures.h"

struct list list_allocate(int type_size, int length) {
  int capacity = length * 2;
  struct array a = array_allocate(type_size, capacity);
  struct list l = {a, capacity, length, 0};
  return l;
}

struct list list_slice(struct list *l, int index_start, int index_end) {
  int length = index_end - index_start;
  int capacity = length * 2;
  struct array a = array_allocate(l->a.type_size, capacity);
  array_copy(&a, 0, list_at(l, index_start), list_at(l, index_end));
  struct list ls = {a, capacity, length, 0};
  return ls;
}

void list_reallocate(struct list *l, int length) {
  struct array a = array_allocate(l->a.type_size, length);
  array_copy(&a, 0, array_at(&(l->a), l->start), array_at(&(l->a), l->end));
  l->end = list_length(l);
  l->a = a;
  l->capacity = length;
  l->start = 0;
}

void list_deallocate(struct list *l) {
	array_deallocate(&(l->a));
}

void* list_at(struct list *l, int index) {
  if(index >= 0) {
    return array_at(&(l->a), l->start + index);
  }
  return array_at(&(l->a), l->end + index);
}

int list_length(struct list *l) {
  return l->end - l->start;
}

void list_append(struct list *l, struct list *source) {
  int length = list_length(l) + list_length(source);
  if( length > l->capacity)
    list_reallocate(l, length * 2);
  array_copy(&(l->a), l->end, array_at(&(source->a), source->start), array_at(&(source->a), source->end));
  l->end = l->start + length;
}

void list_push_back(struct list *l, void* element) {
  if(l->end == l->capacity)
     list_reallocate(l, list_length(l) * 2);
  for(int offset = 0; offset < l->a.type_size; offset++)
    *(((unsigned char*)array_at(&(l->a), l->end)) + offset) = *(((unsigned char*)element) + offset);
  l->end++;
}

void* list_pop_back(struct list *l, void* element) {
  for(int offset = 0; offset < l->a.type_size; offset++)
    *(((unsigned char*)element) + offset) = *(((unsigned char*)list_at(l, -1))  + offset);
   l->end--;
}

void* list_pop_front(struct list *l, void* element) {
  for(int offset = 0; offset < l->a.type_size; offset++)
    *(((unsigned char*)element) + offset) = *(((unsigned char*)list_at(l, 0)) + offset);
  l->start++;
}

int list_sort(struct list *l, int (*compare)(const void *, const void*)) {
	qsort(array_at(&(l->a), l->start), list_length(l), l->a.type_size, compare);
}




int cmpfunc (const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

/*
int main() {
  int element;

  struct list test0 = list_allocate(sizeof(int), 4);
  *((int*)list_at(&test0, -4)) = 1;
  *((int*)list_at(&test0, -3)) = 2;
  *((int*)list_at(&test0, -2)) = 4;
  *((int*)list_at(&test0, -1)) = 8;

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), test0.capacity, test0.start, test0.end);

  struct list test1 = list_slice(&test0, 0, 4);

  for(int i = 0; i < list_length(&test1); i++)
    printf("%d ", *((int*)list_at(&test1, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test1), test1.capacity, test1.start, test1.end);

  list_append(&test0, &test1);

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), test0.capacity, test0.start, test0.end);

  list_append(&test0, &test1);

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), test0.capacity, test0.start, test0.end);

  for(int i = 0; i < list_length(&test1); i++)
    printf("%d ", *((int*)list_at(&test1, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test1), test1.capacity, test1.start, test1.end);

  list_sort(&test0, cmpfunc);

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), test0.capacity, test0.start, test0.end);
}
*/
