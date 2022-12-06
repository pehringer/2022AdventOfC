#include"data_structures.h"

struct list list_allocate(int type_size, int length) {
  struct array arr = array_allocate(type_size, length * 2);
  struct list lst = {arr, length, 0};
  return lst;
}

struct list list_slice(struct list *lst, int index_start, int index_end) {
  int length = index_end - index_start;
  struct array arr = array_allocate(lst->arr.type_size, length * 2);
  array_copy(&arr, 0, list_at(lst, index_start), list_at(lst, index_end));
  struct list slice = {arr, length, 0};
  return slice;
}

void list_reallocate(struct list *lst, int capacity) {
  int length = list_length(lst);
  int end = length < capacity ? length : capacity;
  struct array arr = array_allocate(lst->arr.type_size, capacity);
  array_copy(&arr, 0, array_at(&(lst->arr), lst->start), array_at(&(lst->arr), lst->end));
  struct list new_lst = {arr, end, 0};
  *lst = new_lst;
}

void list_deallocate(struct list *lst) {
	array_deallocate(&(lst->arr));
}

void* list_at(struct list *lst, int index) {
  return array_at(&(lst->arr), lst->start + index);
}

void list_get(struct list *lst, int index, void *element) {
  array_get(&(lst->arr), lst->start + index, element);
}


void list_set(struct list *lst, int index, void *element) {
  array_set((&lst->arr), lst->start + index, element);
}


int list_length(struct list *lst) {
  return lst->end - lst->start;
}

void list_append(struct list *lst, struct list *source) {
  int length = list_length(lst) + list_length(source);
  int end = lst->start + length;
  if(end >= array_length(&(lst->arr)))
    list_reallocate(lst, length * 2);
  array_copy(&(lst->arr), lst->end, array_at(&(source->arr), source->start), array_at(&(source->arr), source->end));
  lst->end = end;
}

void list_push_back(struct list *lst, void* element) {
  if(lst->end == array_length(&(lst->arr)))
    list_reallocate(lst, (list_length(lst) + 1) * 2);
  array_set(&(lst->arr), (lst->end)++, element);
}

void* list_pop_back(struct list *lst, void* element) {
  array_get(&(lst->arr), --(lst->end), element);
}

void* list_pop_front(struct list *lst, void* element) {
  array_get(&(lst->arr), (lst->start)++, element);
}

int list_sort(struct list *lst, int (*compare)(const void*, const void*)) {
	qsort(array_at(&(lst->arr), lst->start), list_length(lst), lst->arr.type_size, compare);
}







/*
int cmpfunc (const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main() {
  int element;

  struct list test0 = list_allocate(sizeof(int), 4);
  element = 1;
  list_set(&test0, 0, &element);
  element = 2;
  list_set(&test0, 1, &element);
  element = 4;
  list_set(&test0, 2, &element);
  element = 8;
  list_set(&test0, 3, &element);

  for(int i = 0; i < list_length(&test0); i++) {
    list_get(&test0, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), array_length(&test0.arr), test0.start, test0.end);

  struct list test1 = list_slice(&test0, 0, 4);

  for(int i = 0; i < list_length(&test1); i++) {
    list_get(&test1, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test1), array_length(&test1.arr), test1.start, test1.end);

  list_append(&test0, &test1);
  list_append(&test0, &test1);
  list_sort(&test0, cmpfunc);

  for(int i = 0; i < list_length(&test0); i++) {
    list_get(&test0, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test0), array_length(&test0.arr), test0.start, test0.end);

  struct list test2 = list_slice(&test0, 0, list_length(&test0));

  for(int i = 0; i < list_length(&test2); i++) {
    list_get(&test2, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.arr), test2.start, test2.end);

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

  for(int i = 0; i < list_length(&test2); i++) {
    list_get(&test2, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.arr), test2.start, test2.end);

  element = 42;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++) {
    list_get(&test2, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.arr), test2.start, test2.end);

  element = 84;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++) {
    list_get(&test2, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.arr), test2.start, test2.end);

  element = 168;
  list_push_back(&test2, &element);

  for(int i = 0; i < list_length(&test2); i++) {
    list_get(&test2, i, &element);
    printf("%d ", element);
  }
  printf("len: %d cap: %d start: %d end: %d\n", list_length(&test2), array_length(&test2.arr), test2.start, test2.end);

}
*/
