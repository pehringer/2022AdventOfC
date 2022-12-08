#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* ptr;

	ptr = fopen("day8input.txt", "r");
	if (NULL == ptr)
		printf("ERROR cannot open day8input.txt\n");

	//Load in height map from file.
	char height[10240];
	int rows = 0;
	int columns = 0;
	int index = 0;
	char ch;
	 while((ch = fgetc(ptr)) != EOF) {
		if(ch == '\n') {
			if(rows++ == 0)
				columns = index;
			continue;
		}
		height[index++] = ch - '0';
	}

	printf("ROWS: %d COLUMNS: %d\n", rows, columns);

	// Go through each tree.
	int best_score = 0;
	for(int tree_row = 0; tree_row < rows; tree_row++) {
		for(int tree_column = 0; tree_column < columns; tree_column++) {

			int current_height = height[(tree_row * columns) + tree_column];

			int top = 0;
        	        for(int row = tree_row-1; row > -1; row--) {
				top++;
				if(height[(row * columns) + tree_column] >= current_height)
					break;
			}

			int bottom = 0;
        	        for(int row = tree_row+1; row < rows; row++) {
				bottom++;
				if(height[(row * columns) + tree_column] >= current_height)
					break;
			}

			int right = 0;
        	        for(int column = tree_column-1; column > -1; column--) {
				right++;
				if(height[(tree_row * columns) + column] >= current_height)
					break;
			}

			int left = 0;
        	        for(int column = tree_column+1; column < columns; column++) {
				left++;
				if(height[(tree_row * columns) + column] >= current_height)
					break;
			}

			int current_score = top * bottom * right * left;
			if(current_score > best_score)
				best_score = current_score;
		}
	}

	printf("ANSWER: %d\n", best_score);

	return 0;
}
