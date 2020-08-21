#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int count, string key[])
{
    //count filter
    if (count != 1)
    {
        if (count == 0)
        {
            printf("Please input a key.\n");
        }
        if (count > 1)
        {
            printf("You have entered %i arguments. Please input only one.\n", count);
        }
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    //length filter
    if (strlen(key[0]) != 26)
    {
        printf("Your key has %zu characters. Only keys with 26 characters are accepted.\n", strlen(key[0]));
        return 1;
    }
    //alphabetical filter
    for (int i = 0; i < strlen(key[0]); i++)
    {
        if (isalpha(key[0][i]) == 0)
        {
            printf("Your key includes a non-alphabetical character. Please try again.\n");
            return 1;
        }
        if 
    }
}