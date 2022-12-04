#include"data_structures.h"

struct list list_allocate(int type_size, int length) {
  struct array a = array_allocate(type_size, length * 2);
  struct list l = {a, length, 0};
  return l;
}

struct list list_slice(struct list *l, int index_start, int index_end) {
  int length = index_end - index_start;
  struct array a = array_allocate(l->a.type_size, length * 2);
  array_copy(&a, 0, list_at(l, index_start), list_at(l, index_end));
  struct list s = {a, length, 0};
  return s;
}

void list_reallocate(struct list *l, int capacity) {
  int length = list_length(l);
  int end = length < capacity ? length : capacity;
  struct array a = array_allocate(l->a.type_size, capacity);
  array_copy(&a, 0, array_at(&(l->a), l->start), array_at(&(l->a), l->end));
  struct list r = {a, end, 0};
  *l = r;
}

void list_deallocate(struct list *l) {
	array_deallocate(&(l->a));
}

void* list_at(struct list *l, int index) {
  return array_at(&(l->a), l->start + index);
}

int list_length(struct list *l) {
  return l->end - l->start;
}

void list_append(struct list *l, struct list *r) {
  int length = list_length(l) + list_length(r);
  int end = l->start + length;
  if(end >= array_length(&(l->a)))
    list_reallocate(l, length * 2);
  array_copy(&(l->a), l->end, array_at(&(r->a), r->start), array_at(&(r->a), r->end));
  l->end = end;
}

void list_push_back(struct list *l, void* element) {
  if(l->end == array_length(&(l->a)))
    list_reallocate(l, (list_length(l) + 1) * 2);
  unsigned char *source = element;
  unsigned char *destination = array_at(&(l->a), (l->end)++);
  for(int copied = 0; copied < l->a.type_size; copied++)
    *(destination++) = *(source++);
}

void* list_pop_back(struct list *l, void* element) {
  unsigned char *source = array_at(&(l->a), --(l->end));
  unsigned char *destination =  element;
  for(int copied = 0; copied < l->a.type_size; copied++)
    *(destination++) = *(source++);
}

void* list_pop_front(struct list *l, void* element) {
  unsigned char *source = array_at(&(l->a), (l->start)++);
  unsigned char *destination =  element;
  for(int copied = 0; copied < l->a.type_size; copied++)
    *(destination++) = *(source++);
}

int list_sort(struct list *l, int (*compare)(const void *, const void*)) {
	qsort(array_at(&(l->a), l->start), list_length(l), l->a.type_size, compare);
}



/*
int cmpfunc (const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main() {
  int element;

  struct list test0 = list_allocate(sizeof(int), 4);
  *((int*)list_at(&test0, 0)) = 1;
  *((int*)list_at(&test0, 1)) = 2;
  *((int*)list_at(&test0, 2)) = 4;
  *((int*)list_at(&test0, 3)) = 8;

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), array_length(&test0.a), test0.start, test0.end);

  struct list test1 = list_slice(&test0, 0, 4);

  for(int i = 0; i < list_length(&test1); i++)
    printf("%d ", *((int*)list_at(&test1, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test1), array_length(&test0.a), test1.start, test1.end);

  list_append(&test0, &test1);
  list_append(&test0, &test1);
  list_sort(&test0, cmpfunc);

  for(int i = 0; i < list_length(&test0); i++)
    printf("%d ", *((int*)list_at(&test0, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), array_length(&test0.a), test0.start, test0.end);

  struct list test2 = list_slice(&test0, 0, list_length(&test0));

  for(int i = 0; i < list_length(&test2); i++)
    printf("%d ", *((int*)list_at(&test2, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.a), test2.start, test2.end);

  list_reallocate(&test2, 12);

  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);
  list_pop_front(&test2, &element);
  printf("%d\n", element);

  for(int i = 0; i < list_length(&test2); i++)
    printf("%d ", *((int*)list_at(&test2, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.a), test2.start, test2.end);

  element = 42;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++)
    printf("%d ", *((int*)list_at(&test2, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.a), test2.start, test2.end);

  element = 84;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++)
    printf("%d ", *((int*)list_at(&test2, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.a), test2.start, test2.end);

  element = 168;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++)
    printf("%d ", *((int*)list_at(&test2, i)));
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.a), test2.start, test2.end);

}
*/
