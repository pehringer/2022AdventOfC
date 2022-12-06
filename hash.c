#include"data_structures.h"

//Code from: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash_djb2(unsigned char *string) {
	//Algorithm: hash(i - 1) * 33 ^ str[i]
	unsigned long hash = 5381;
	int character;
	while (character = *string++)
		hash = ((hash << 5) + hash) + character; //hash * 33 + c
	return hash;
}

//Code from: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash_sdbm(unsigned char *string) {
	//Algorithm: hash(i) = hash(i - 1) * 65599 + str[i]
	unsigned long hash = 0;
	int character;
	while (character = *string++)
		hash = character + (hash << 6) + (hash << 16) - hash;
        return hash;
}

