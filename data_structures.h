#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include<stdlib.h>
#include<stdio.h>

/*
################################################################
Array structs and functions below.
################################################################
*/

// Used to hold state of array. Property manipulated with any functions that
// begin with "array_".
struct array {
  unsigned char *end;
  unsigned char *start;
  int type_size;
};

// Constructor, returns array of given length with element of the given
// type_size.
// Example:
//	array_allocate(sizeof(int), 4)
//	array_allocate(sizeof(double), 42)
struct array array_allocate(int type_size, int length);

// Deconstructor, releases any system resources used by given array.
void array_deallocate(struct array *arr);

// Copies data from given source_start upto (but not including) given
// source_end over to given array starting at given index.
// Example:
//	arr = array_allocate(sizeof(int), 4)
//	data = [2, 6, 4, 9, 8, 5]
//	array_copy(&arr, 1, &data[2], &data[4]) ---> arr = [#, 4, 9, #]
//	array_copy(&arr, 0, &data[3], &data[6]) ---> arr = [9, 8, 5, #]
//	array_copy(&arr, 0, &data[0], &data[6]) ---> arr = [2, 6, 4, 9]
void array_copy(struct array *arr, int start_index, void *src_start, void *src_end);

// Return pointer to given arrays element at given index. Given index
// is in units of the given arrays type.
// Example:
//	arr = array_allocate(sizeof(int), 4)
//	*((int*) array_at(&arr, 2)) = 4 ---> arr = [#, #, 4, #]
//	*((int*) array_at(&arr, 0)) = 9 ---> arr = [9, #, 4, #]
void* array_at(struct array *arr, int index);

// Copies element at given index in given array into given element.
// Example:
//	arr = array_allocate(sizeof(int), 4)
//	e = 4
//	array_set(&arr, 2, &e) ---> arr = [#, #, 2, #]
//	e = 0
//	array_set(&arr, 3, &e) ---> arr = [#, #, 2, 0]
//      array_get(&arr, 2, &e) ---> e = 2
void array_get(struct array *arr, int index, void *element);

// Copies given element into element at given index in given array.
// Example:
//	arr = array_allocate(sizeof(int), 4)
//	e = 4
//	array_set(&arr, 2, &e) ---> lis = [#, #, 2, #]
//	e = 0
//	array_set(&arr, 3, &e) ---> lis = [#, #, 2, 0]
//      array_get(&arr, 2, &e) ---> e = 2
void array_set(struct array *arr, int index, void *element);

// Returns length of given array in units of the given arrays type.
// Example:
//	arr = array_allocate(sizeof(int), 4)
//	arr_length(&arr) ---> 4
int array_length(struct array *arr);

/*
################################################################
List structs and functions below.
################################################################
*/

// Used to hold state of list. Property manipulated with any function that
// begins with "list_".
struct list {
  struct array arr;
  int end;
  int start;
};

// Constructor, returns list of given length with element of the given
// type_size.
// Example:
//	list_allocate(sizeof(int), 4)
//	list_allocate(sizeof(double), 42)
struct list list_allocate(int type_size, int length);


// Constructor, returns list with elements copied from given lists elements
// from given index_start upto (but not including) given index_end. given
// index are in units of the given lists type.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1, &e))
//	e = 4
//	list_set(&lis, 2, &e))
//	e = 9
//	list_set(&lis, 3, &e))
//	s0 = list_slice(&lis, 0, 2) ---> s0 = [2, 6]
//      s1 = list_slice(&lis, 1, 3) ---> s1 = [6, 4]
//      s2 = list_slice(&lis, 1, 4) ---> s2 = [6, 4, 9]
//	s3 = list_slice(&lis, 0, 4) ---> s3 = [2, 6, 4, 9]
struct list list_slice(struct list *lst, int index_start, int index_end);

// Resizes given list to given capacity. Given lists length will be adjusted
// Accordingly. This function is mainly used by other functions.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1, &e))
//	e = 4
//	list_set(&lis, 2, &e))
//	e = 9
//	list_set(&lis, 3, &e))
//	list_reallocate(&lis, 8) ---> lis = [2, 6, 4, 9] 0, 0, 0, 0]
//	list_length(&lis)           ---> 4
//	list_reallocate(&lis, 6) ---> lis = [2, 6, 4, 9] 0, 0]
//	list_length(&lis)           ---> 4
//	list_reallocate(&lis, 4) ---> lis = [2, 6, 4, 9]]
//	list_length(&lis)           ---> 4
//	list_reallocate(&lis, 2) ---> lis = [2, 6]]
//	list_length(&lis)           ---> 2
void list_reallocate(struct list *lst, int capacity);

// Deconstructor, releases any system resources used by given list.
void list_deallocate(struct list *lst);

// Return pointer to given list element at given index. Given index
// is in units of the given lists type.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	*((int*) list_at(&lis, 2)) = 4 ---> arr = [#, #, 4, #]
//	*((int*) list_at(&lis, 0)) = 9 ---> arr = [9, #, 4, #]
void* list_at(struct list *lst, int index);

// Copies element at given index in given list into given element.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 4
//	list_set(&lis, 2, &e) ---> lis = [#, #, 2, #]
//	e = 0
//	list_set(&lis, 3, &e) ---> lis = [#, #, 2, 0]
//      list_get(&lis, 2, &e) ---> e = 2
void list_get(struct list *lst, int index, void *element);

// Copies given element into element at given index in given list.
// Example:
//	arr = list_allocate(sizeof(int), 4)
//	e = 4
//	list_set(&arr, 2, &e) ---> lis = [#, #, 2, #]
//	e = 0
//	list_set(&arr, 3, &e) ---> lis = [#, #, 2, 0]
//      list_get(&arr, 2, &e) ---> e = 2
void list_set(struct list *lst, int index, void *element);

// Returns length of given list in units of the given lists type.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	lst_length(&lis) ---> 4
int list_length(struct list *lst);

// Appends copies of elements from given list onto the back of given
// list.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1, &e))
//	e = 4
//	list_set(&lis, 2, &e))
//	e = 9
//	list_set(&lis, 3, &e))
//	s = list_slice(&lis, 0, 2) ---> s = [2, 6]
//      list_append(&lis, &s)      ---> lis = [2, 6, 4, 9, 2, 6]
void list_append(struct list *lst, struct list *src);

// Appends copy of given element from given list onto the back of given
// list.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//      e = 2
//      list_push_back(&lis, &e) ---> lis = [2]
//      e = 6
//      list_push_back(&lis, &e) ---> lis = [2, 6]
void list_push_back(struct list *lst, void* element);

// Copies element at the end of the given list to the given element. Then
// removes the element at the end of the list.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1)) = 6
//      e = 0
//      list_pop_back(&lis, &e) ---> lis = [2]
//      e                       ---> 6
//      list_pop_back(&lis, &e) ---> lis = []
//      e                       ---> 2
void* list_pop_back(struct list *lst, void* element);

// Copies element at the front of the given list to the given element. Then
// removes the element at the front of the list.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1)) = 6
//      e = 0
//      list_pop_back(&lis, &e) ---> lis = [2]
//      e                       ---> 6
//      list_pop_back(&lis, &e) ---> lis = []
//      e                       ---> 2
void* lst_pop_front(struct list *lst, void* element);

// Sorts elements int the given list with given comapare function.
// Example:
//	lis = list_allocate(sizeof(int), 4)
//	e = 2
//	list_set(&lis, 0, &e))
//	e = 6
//	list_set(&lis, 1, &e))
//	e = 4
//	list_set(&lis, 2, &e))
//	e = 9
//	list_set(&lis, 3, &e))
//	list_sort(&lis) ---> lis = [2, 4, 6, 9]
int list_sort(struct list *lst, int (*compare)(const void *, const void*));

/*
################################################################
Hash structs and functions below.
################################################################
*/

unsigned long hash_djb2(unsigned char *string);

unsigned long hash_sdbm(unsigned char *string);

/*
################################################################
Dictionary structs and functions below.
################################################################
*/

/*
// Used to hold state of dictionary. Property manipulated with any functions
// that begin with "dictionary_".
struct dictionary {
  struct array arr;
  int head;
};

// Used to hold state of dictionary key value pair. Used internally by
// functions that begin with "dictionary_".
struct key_value {
  char key[64];
  int next;
  int previous;
};

struct dictionary dictionary_allocate(int type_size);

void dictionary_reallocate(struct dictionary *dic);

void dictionary_deallocate(struct dictionary *dic);

void dictionary_keys(struct dictionary *dic, char keys[][64]);

void dictionary_at(struct dictionary *dic, char key[64]);

void dictionary_in(struct dictionary *dic, char key[64]);

void dictionary_get(struct dictionary *dic, char key[64], void *element);

void dictionary_set(struct dictionary *dic, char key[64], void *element);
*/

#endif
