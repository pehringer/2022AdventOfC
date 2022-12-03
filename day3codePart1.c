#include"data_structures.h"

int main()
{
    FILE* ptr;
    char ch;
    int length = 0;

    ptr = fopen("day3input.txt", "r");
    if (NULL == ptr)
        printf("ERROR cannot open day3input.txt\n");


    int priorities_sum = 0;
    char line[1024];
    int line_length = 0;
    char first_compartment[256];

    while(1) {
	char ch = fgetc(ptr);
	if(ch == '\n') {
		//Clear out log.
		int i = 0;
		while(i < 256)
			first_compartment[i++] = 0;
		i = 0;
		//log what is in the first compartment.
		while(i < line_length / 2)
                        first_compartment[line[i++]]++;
		//Look for matches in second compartment with log.
		while(i < line_length) {
			if(first_compartment[line[i]])
				break;
			i++;
		}
		//Match found add points.
		if(i != 256) {
			if(line[i] >= 'a')
				priorities_sum += line[i] - 96; //1 or higher.
			else if(line[i] >= 'A')
				priorities_sum += line[i] - 38; //27 or higher.
		}
		line_length = 0;
		continue;
	}
	if(ch == EOF)
		break;
        line[line_length++] = ch;
    }

    fclose(ptr);

    printf("priorities_sum: %d\n", priorities_sum);

    return 0;
}
