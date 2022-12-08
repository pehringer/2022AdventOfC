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

	//Init visible map.
	char visible[10240];
	for(int row = 0; row < rows; row++) {
		for(int column = 0; column < columns; column++) {
			visible[(row * columns) + column] = 0;
			if(row == 0 || row == rows - 1)
				visible[(row * columns) + column] = 1;
			if(column == 0 || column == columns - 1)
				visible[(row * columns) + column] = 1;
		}
	}

	//Mark visible from top to bottom.
	for(int column = 0; column < columns; column++) {
		char current_height = height[column];
		for(int row = 0; row < rows; row++) {
			if(current_height == 9)
				break;
			if(height[(row * columns) + column] > current_height) {
				current_height = height[(row * columns) + column];
				visible[(row * columns) + column] = 1;
			}
		}
	}

	//Mark visible from right to left.
	for(int row = 0; row < rows; row++) {
		char current_height = height[((row + 1) * columns) - 1];
		for(int column = columns - 1; column > -1; column--) {
			if(current_height == 9)
				break;
			if(height[(row * columns) + column] > current_height) {
				current_height = height[(row * columns) + column];
				visible[(row * columns) + column] = 1;
			}
		}
	}

	//Mark visible from bottom to top.
	for(int column = 0; column < columns; column++) {
		char current_height = height[((rows - 1) * columns) + column];
		for(int row = rows - 1; row > -1; row--) {
			if(current_height == 9)
				break;
			if(height[(row * columns) + column] > current_height) {
				current_height = height[(row * columns) + column];
				visible[(row * columns) + column] = 1;
			}
		}
	}

	//Mark visible from left to right.
	for(int row = 0; row < rows; row++) {
		char current_height = height[row * columns];
		for(int column = 0; column < columns; column++) {
			if(current_height == 9)
				break;
			if(height[(row * columns) + column] > current_height) {
				current_height = height[(row * columns) + column];
				visible[(row * columns) + column] = 1;
			}
		}
	}

	//Sum up visible trees.
	int num_visible = 0;
	for(int row = 0; row < rows; row++)
		for(int column = 0; column < columns; column++)
			num_visible += visible[(row * columns) + column];

	printf("ANSWER: %d\n", num_visible);

	return 0;
}
