#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* ptr;
    char ch;
    int length = 0;

    ptr = fopen("day2input.txt", "r");
    if (NULL == ptr)
        printf("ERROR cannot open day2input.txt\n");


    int score = 0;
    while(1) {
	//Handle end of file.
	char first = fgetc(ptr);
	if(first == '\n')
		continue;
	if(first == EOF)
		break;

	//Convert plays to shape points.
	int op_play = first - '@';
	printf("op_play: %d ", op_play);
	fgetc(ptr);
        int yo_play = fgetc(ptr) - 'W';
	printf("yo_play: %d \n", yo_play);
	fgetc(ptr);

	//Add to shape and round to score.
	score += yo_play;
	if((yo_play == 1 && op_play == 3) ||
	   (yo_play == 2 && op_play == 1) ||
	   (yo_play == 3 && op_play == 2))
		score += 6;
	if(yo_play == op_play)
		score += 3;
    }

    fclose(ptr);

    printf("Your score: %d\n", score);
    return 0;
}
