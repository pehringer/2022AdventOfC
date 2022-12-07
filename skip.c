#include"data_structures.h"

struct skip skip_allocate(int type_size, int levels, int (*compare)(const void *, const void*)) {
	struct array arr = array_allocate((sizeof(int) * levels) + type_size, 32);
	for(int l = 0; l < levels; l++ )
		*(((int*) array_at(&arr, i)) + l) = 0;
	for(int i = 1; i < array_length(&arr) - 1; i++)
		*((int*) array_at(&arr, i)) = i + 1;
	*((int*) array_at(&arr, array_length(&arr) - 1)) = 0;
	struct skip skp = {arr, compare, 1, 0, 0, levels};
	return skp;
}

void skip_reallocate(struct skip *skp, int capacity);

void skip_deallocate(struct skip *skp) {
	array_deallocate(&(skp->array));
}

void skip_insert(struct skip *skp, void *element) {
	if(!(skp->free))
		skip_reallocate(skp, skp->length * 2));
	int insert_index = skp->free;
	int insert_levels = array_at(&(skp->arr), skp->free);
	skp->free = *((int*) array_at(&(skp->arr), skp->free));
	int current_index = 0;
	int current_level = 0;
	do {
		int next_index = ((int*) array_at(&(skp->arr), current_index))[current_level];
		if(next_index == 0) {
			insert_levels[current_level] = current_index;
			current_level++;
		}
		int result = skp->compare(current + skp->levels, element);
		if(0 < result) // Keep traversing level.
			;
		else if(0 == result) // Found existing element replace element.
			;
		else if(0 > result) // 
			;
	} while(1)
}

void skip_remove(struct skip *skp, void *element);

void skip_search(struct skip *skp, char *element);

void skip_length(struct skip *skp);

struct list skip_elements(struct skip * skp);
