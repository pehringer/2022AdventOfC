#include"data_structures.h"

int main()
{
	FILE* ptr;

	ptr = fopen("day4input.txt", "r");
	if (NULL == ptr)
		printf("ERROR cannot open day3input.txt\n");

	int redo_pairs = 0;
	int pairs[4];
	int number = 0;
	char digits[8];
	char place = 0;

	while(1) {
		char ch = fgetc(ptr);
		//End of numbers digits. Convert digits to number.
		if(ch == '-' || ch == ',' || ch == '\n') {
			digits[place] = '\0';
			pairs[number++] = atoi(digits);
			place = 0;
			//End of line, use pair numbers to find complete overlap.
			if(number == 4) {
				if(pairs[0] <= pairs[2] && pairs[1] >= pairs[3])
					redo_pairs++;
				else if(pairs[2] <= pairs[0] && pairs[3] >= pairs[1])
					redo_pairs++;
				number = 0;
			}
			continue;
		}
		//End of file.
		if(ch == EOF)
			break;
		digits[place++] = ch;
	}

	fclose(ptr);

	printf("Answer: %d\n", redo_pairs);

	return 0;
}
