#include<stdlib.h>
#include<stdio.h>

int main()
{
	FILE* ptr;

	ptr = fopen("day5input.txt", "r");
	if (NULL == ptr)
		printf("ERROR cannot open day5input.txt\n");

	//Parse out starting stack state.
	int parsing_rows = 1;
	int rows = 0;
	int parsing_columns = 0;
	int columns = 0;
	char starting_state[1024];
	int current = 0;
	while(1) {
		fgetc(ptr);
		char data = fgetc(ptr);
		fgetc(ptr);
		char dlim = fgetc(ptr);
		if(parsing_rows && (data == ' ' || (data >= 'A' && data <= 'Z'))) {
			starting_state[current++] = data;
			if(dlim == '\n')
				rows++;
			continue;
		}
		if(parsing_rows && (data >= '0' && data <= '9')) {
			parsing_rows = 0;
			parsing_columns = 1;
                        columns++;
			continue;
                }
		if(parsing_columns) {
			columns++;
			if(dlim == '\n')
				break;
		}
	}
	/*
	//Print out starting stack state.
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < columns; c++)
			printf("%c ", starting_state[(r * columns) + c]);
		printf("\n");
	}
	printf("ROWS: %d COLUMNS: %d\n", rows, columns);
	*/
	//Allocate working state.
	char *working_state = malloc(sizeof(char) * ((rows * columns) * columns));
	for(int i = 0; i < (rows * columns) * columns; i++)
		working_state[i] = ' ';
	int *top = malloc(sizeof(int) * columns);
        for(int i = 0; i < columns; i++)
                top[i] = 0;

	//Copy over starting state to working state. Get starting heights.
	for(int sr = 0, wr = rows - 1; sr < rows; sr++, wr--) {
		for(int c = 0; c < columns; c++) {
			if(starting_state[(sr * columns) + c] != ' ' && !top[c])
				top[c] = wr;
			working_state[(wr * columns) + c] = starting_state[(sr * columns) + c];
		}
	}
	/*
	//Print out working stack state.
	for(int i = 0; i < columns; i++)
		printf("%d ", top[i]);
	printf("\n");
        for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++)
                        printf("%c ", working_state[(r * columns) + c]);
                printf("\n");
        }
	*/
	//Skip newline dlim.
	fgetc(ptr);
	//Parse moves.
	int numbers = 0;
	int number[3];
	char string[32];
	int length = 0;
	while(1) {
		char ch = fgetc(ptr);
		if((ch == '\n' && numbers == 0) || ch == EOF)
			break;
		if(ch == ' ' || ch == '\n') {
			string[length] = '\0';
			length = 0;
			int value = atoi(string);
			//Number parsed.
			if(value > 0)
				number[numbers++] = value;
			//Process move.
			if(numbers == 3) {
				numbers = 0;
				/*
				printf("MOVE: %d %d %d\n", number[0], number[1], number[2]);
				*/
				for(int n = 0; n < number[0]; n++) { //working_state[(wr * columns) + c]
					top[number[2]-1]++;
					working_state[(top[number[2]-1] * columns) + (number[2]-1)] = working_state[(top[number[1]-1] * columns) + (number[1]-1)];
					top[number[1]-1]--;
				}
			}
			continue;
		}
		string[length++] = ch;
	}

	//Get top crates.
	char *top_crates = malloc(sizeof(char) *columns);
	length = 0;
	for(int i = 0; i < columns; i++)
		if(working_state[(top[i] * columns) + i] > -1)
			top_crates[length++] = working_state[(top[i] * columns) + i];
	top_crates[length] = '\0';

	printf("ANSWER: %s\n", top_crates);

	fclose(ptr);

	return 0;
}
