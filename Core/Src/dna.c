#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"

#define ARR_SIZE(arr) ((sizeof(arr)) / (sizeof(*arr)))

void dnaGame(void)
{
    // Seed the random number generator. Yes, in this form it is not
    // really random since it will give the same sequence for every run,
    // but it's good enough for this program.
    srand(1);

    char *ROWS[] =
    {
        "         ##", // Index 0 hans no %c
        "        #%c-%c#",
        "       #%c---%c#",
        "      #%c-----%c#",
        "     #%c------%c#",
        "    #%c------%c#",
        "    #%c-----%c#",
        "     #%c---%c#",
        "     #%c-%c#",
        "      ##", // Index 9 hans no %c
        "     #%c-%c#",
        "     #%c---%c#",
        "    #%c-----%c#",
        "    #%c------%c#",
        "     #%c------%c#",
        "      #%c-----%c#",
        "       #%c---%c#",
        "        #%c-%c#"
    };

    printf("DNA Animation, by Al Sweigart\n\r");
    printf("Press Ctrl-C to quit...\n\r");

    int rowIndex = 0;
    while (1)
    {
        rowIndex++;
        if(rowIndex == ARR_SIZE(ROWS))
        {
            rowIndex = 0;
        }

        if(rowIndex == 0 || rowIndex == 9)
        {
            printf("%s\n\r", ROWS[rowIndex]);
            continue;
        }

        // Select random nucleotide pairs, guanine-cytosine
        // and adenine-thymine.
        char leftNucleotide, rightNucleotide;
        switch (rand() % 4 + 1)
        {
        case 1:
            leftNucleotide = 'A';
            rightNucleotide = 'T';
            break;
        case 2:
            leftNucleotide = 'T';
            rightNucleotide = 'A';
            break;
        case 3:
            leftNucleotide = 'C';
            rightNucleotide = 'G';
            break;
        case 4:
            leftNucleotide = 'G';
            rightNucleotide = 'C';
            break;
        default:
            break;
        }

        char str[50];
        sprintf(str, "%s", ROWS[rowIndex]);
        sprintf(str, str, leftNucleotide, rightNucleotide);
        printf("%s\n\r", str);

        HAL_Delay(150);
    }
}