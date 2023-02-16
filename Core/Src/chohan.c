// Cho-Han, by Al Sweigart
// The traditional Japanese dice game of even-odd.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *JAPANESE_NUMBERS[] = {"ICHI", "NI", "SAN", "SHI", "GO", "ROKU"};
enum BOOL { FALSE, TRUE };

char welcomePromprt[] = "In this traditional Japanese dice \
game, two dice are rolled in a bamboo cup by the dealer sitting \
on the floor. The player must guess if the deice total to an \
even (cho) or odd (han) number.";

char * ch_input(char *prompt)
{
    int MAX_INPUT_LENGTH = 500;
    char *buf = malloc(MAX_INPUT_LENGTH * sizeof(char));

    printf("%s", prompt);
    if (fgets(buf, MAX_INPUT_LENGTH, stdin) != NULL)
        return buf;
    else
        return NULL;
}

// return string uppercase
char* upper(char *s)
{
    char *stmp = s;

    int strlen = 0;
    while (*stmp++ != 0)
        strlen++;

    // +1 for terminating null character
    char *t = malloc((strlen + 1) * sizeof(char));
    
    for(; *s != 0; s++, t++)
    {
        // if lowercase than make it uppercase
        if (*s >= 'a' && *s <= 'z')
            *t = *s - 32;
        else // just copy
            *t = *s;
    }

    *t = '\0';
    t -= strlen; // return starting address
    return t;
}

int toDecimal(char *s, long *n)
{
    char *end;
    long temp = strtol(s, &end, 10);

    /* strtol returns a pointer to the end of the numeric portion of the string 
    so if this end pointer still refers to the start of the original string that
    means there was an error and nothing is converted. */
    if(end == s) return 1;
    
    *n = temp;
    return 0;
}

void chohanGame(void)
{
    srand(1);
    printf("%s\n\r", welcomePromprt);

    long purse = 5000;
    long pot = 0;
    while (1)
    {
        printf("You have, %ld mon. How much do you bet? (or QUIT)\n\r", purse);
        while (1)
        {
            char *input = ch_input("> ");
            char *INPUT = upper(input);
            if (!strcmp(INPUT, "QUIT\n"))
            {
                printf("Thanks for playing!\n\r");
                exit(EXIT_SUCCESS);
            }

            if (toDecimal(INPUT, &pot))
            {
                printf("Please enter a number!\n\r");
                free(input);
                continue;
            }

            if  (pot < 0)
            {
                printf("Negative bet is not allowed!\n\r");
                free(input);
                continue;
            }

            if(pot > purse)
            {
                printf("You don't have enough to make that bet.\n\r");
            }
            else
            {
                free(input);
                break; // Exit loop once valid loop is placed.
            }
        }
        
        // Roll the dice
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;

        printf("The dealer swirls the cup and you hear the rattle of dice.\n\r");
        printf("The dealer slams the cup on the floor, still covering the\n\r");
        printf("dice and ask for your bet.\n\n\r");
        printf("    CHO (even) or HAN (odd)?\n\r");

        // Let the player bet cho or han:
        char bet[5];
        while(1)
        {
            char *input = ch_input("> ");
            char *INPUT = upper(input);
            strcpy(bet, INPUT);
            if ((!strcmp(bet, "CHO\n")) || (!strcmp(bet, "HAN\n")))
                break;
            else
                printf("Please enter either 'CHO' or 'HAN'.\n\r");
        }

        // Reveal the dice results:
        printf("The dealer lifts the cup to reveal:\n\r");
        printf("%s - %s\n", JAPANESE_NUMBERS[dice1 - 1], JAPANESE_NUMBERS[dice2 - 1]);
        printf("%d - %d\n", dice1, dice2);

        // Determine if the player won:
        int rollIsEven = (dice1 + dice2) % 2 == 0;

        char correctBet[5];
        if (rollIsEven)
            strcpy(correctBet, "CHO\n");
        else
            strcpy(correctBet, "HAN\n");

        int playerWon = !strcmp(bet, correctBet) ? TRUE : FALSE;

        if (playerWon)
        {
            printf("You won! You take, %ld, mon.\n\r", pot);
            purse = purse + pot; // Add the pot from player's purse.
            printf("The house collects a %ld mon fee.\n\r", pot / 10);
            purse = purse - (pot / 10); // The house fee is 10%
        }
        else
        {
            purse = purse - pot; // Substract the pot from player's purse.
            printf("You lost!\n\r");
        }

        // Check if the player has run out of money:
        if (purse == 0)
        {
            printf("You have run out of money!\n\r");
            printf("Thanks for playing!");
            exit(EXIT_SUCCESS);
        }
    }
}