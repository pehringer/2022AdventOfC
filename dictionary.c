#include"data_structures.h"

/*
struct dictionary dictionary_allocate(int type_size) {
  struct array arr = array_allocate((type_size + sizeof(key_value)), 1024);
  struct key_value empty = {"", -1, -1};
  for(int i = 0; i < array_length(&arr); i++)
    array_set(&arr, i, &empty);
  struct dictionary dic = {arr, -1};
  return dic;
}

void dictionary_reallocate(struct dictionary *dic);

void dictionary_deallocate(struct dictionary *dic);

void dictionary_keys(struct dictionary *dic, char keys[][64]) {
  int current_key = dic->head;
  int key_number = 0;

  while(current_key != -1) {
    char *key = array_at(&(dic->arr), current)
    for(int copy = 0; copy < 64; copy++)
      key[key_number][copy] = *(source++);
  }
}

void dictionary_at(struct dictionary *dic, char key[64]);

void dictionary_in(struct dictionary *dic, char key[64]);

void dictionary_get(struct dictionary *dic, char key[64], void *element);

void dictionary_set(struct dictionary *dic, char key[64], void *element);
*/
