#include<stdlib.h>
#include<stdio.h>

int main()
{
	FILE* ptr;

	ptr = fopen("day6input.txt", "r");
	if (NULL == ptr)
		printf("ERROR cannot open day5input.txt\n");

	char d0;
	char d1 = fgetc(ptr);
	char d2 = fgetc(ptr);
	char d3 = fgetc(ptr);
	int position = 3;
	char ch;
	while((ch = fgetc(ptr)) != EOF) {
		//shift values.
		d0 = d1;
		d1 = d2;
		d2 = d3;
		d3 = ch;
		position++;
		if(d0 == d1 || d0 == d2 || d0 == d3 ||
		   d1 == d2 || d1 == d3 ||
		   d2 == d3)
			continue;
		break;
	}

	fclose(ptr);

	printf("ANSWER: %d\n", position);

	return 0;
}
