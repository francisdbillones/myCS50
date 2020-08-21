#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(string key)
{
    //length filter
    if (strlen(key) != 26)
    {
        if (strlen(key) > 26)
        {
            printf("Your key has more than 26 characters. Please try again.")
            return 1
        }
        else
        {
            printf("Your key has less than 26 characters. Please try again.");
            return 1
        }
    }
    //alphabetical filter
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Your key includes a non-alphabetical character. Please try again.");
            return 1;
        }
        
    }
}