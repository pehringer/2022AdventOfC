#include<stdlib.h>
#include<stdio.h>

int main()
{
	FILE* ptr;

	ptr = fopen("day6input.txt", "r");
	if (NULL == ptr)
		printf("ERROR cannot open day5input.txt\n");

	char data[14];
	for(int d = 1; d < 14; d++)
		data[d] = fgetc(ptr);
	int position = 13;
	char ch;
	while((ch = fgetc(ptr)) != EOF) {
		//shift values.
		for(int d = 0; d < 13; d++)
                	data[d] = data[d+1];
		data[13] = ch;
		position++;

		for(int d = 0; d < 14; d++)
			for(int d1 = d + 1; d1 < 14; d1++)
				if(data[d] == data[d1])
					goto skip;
		break;
		skip:;
	}

	fclose(ptr);

	printf("ANSWER: %d\n", position);

	return 0;
}
