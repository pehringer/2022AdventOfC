#include<stdlib.h>
#include<stdio.h>

int main()
{
    FILE* ptr;

    ptr = fopen("day3input.txt", "r");
    if (NULL == ptr)
        printf("ERROR cannot open day3input.txt\n");

    int priorities_sum = 0;
    int member = 0;
    char compartments[3][256];
    //Clear log for next group of elfs.
    for(int i = 0; i < 256; i++)
	compartments[0][i] = compartments[1][i] = compartments[2][i] = 0;

    while(1) {
	//All three elfs packs logged. Find item type carried by all three elfs.
	if(member == 3) {
		for(int i = 0; i < 256; i++) {
			if(compartments[0][i] && compartments[1][i] && compartments[2][i]) {
				if(i >= 'a')
					priorities_sum += i - 96; //1 or higher.
				else if(i >= 'A')
					priorities_sum += i - 38; //27 or higher.
			}
			//Clear log for next group of elfs.
			compartments[0][i] = compartments[1][i] = compartments[2][i] = 0;
		}
		member = 0; //Reset state for next group.
	}
	char ch = fgetc(ptr);
	//Done logging elfs pack items.
	if(ch == '\n') {
		member++;
		continue;
	}
	//End of file.
	if(ch == EOF)
		break;
	compartments[member][ch]++; //Log elfs pack item.
    }

    fclose(ptr);

    printf("priorities of common: %d\n", priorities_sum);

    return 0;
}
