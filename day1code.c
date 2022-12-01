#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* ptr;
    char ch;
    int length = 0;

    ptr = fopen("day1input.txt", "r");
    if (NULL == ptr)
        printf("ERROR cannot open day1input.txt\n");

    int currentCount = 0;
    int maxCount1 = 0;
    int maxCount2 = 0;
    int maxCount3 = 0;
    char digits[8];
    int currentDigit = 0;
    int lastNewLine = 0;

    do {
	ch = fgetc(ptr);
        //Empty line, counted all numbers for elf.
        //Compare elf count to top three elf counts
        if(ch == '\n' && lastNewLine) {
              if(currentCount >= maxCount1) {
                  maxCount3 = maxCount2;
                  maxCount2 = maxCount1;
                  maxCount1 = currentCount;
              }
	      else if(currentCount >= maxCount2) {
                  maxCount3 = maxCount2;
                  maxCount2 = currentCount;
              }
              else if(currentCount >= maxCount3) {
                  maxCount3 = currentCount;
              }
	      //Reset for next elf.
              currentCount = 0;
        }
	//End of line. Parse out number stored in
	//digits and add it to the elfs count.
        if(ch == '\n') {
	    lastNewLine = 1;
            digits[currentDigit] = '\0';
            currentCount += atoi(digits);
            currentDigit = 0;
        }
	//Read in digit for lines number, store in digits.
        if(ch != '\n') {
             lastNewLine = 0;
             digits[currentDigit++] = ch;
        }
    } while (ch != EOF);

    fclose(ptr);

    printf("Elf with 1st most: %d\n", maxCount1);
    printf("Elf with 2nd most: %d\n", maxCount2);
    printf("Elf with 3rd most: %d\n", maxCount3);
    printf("Total of top Elfs: %d\n", maxCount1 + maxCount2 + maxCount3);

    return 0;
}
