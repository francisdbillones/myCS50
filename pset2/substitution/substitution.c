#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scanArray(string text, char element, int length);

int main(int count, string key[])
{
    //count filter
    if (count != 2)
    {
        if (count == 1)
        {
            printf("Please input a key.\n");
        }
        else if (count > 2)
        {
            printf("You have entered %i arguments. Please input only one.\n", count);
        }

        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    //length filter
    int length = strlen(key[1]);
    if (length != 26)
    {
        printf("Your key has %i characters. Only keys with 26 characters are accepted.\n", length);
        return 1;
    }
    
    //alphabetical filter
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for (int i = 0; i < length; i++)
    {
        if (isalpha(key[0][i]) == 0)
        {
            printf("Your key includes a non-alphabetical character.\n");
            return 1;
            break;
        }
    }
    //completeness filter
    for (int y = 0; y < 26; y++)
    {
        if (scanArray(key[1], alphabet[y], length) == 0)
        {
            printf("Your key does not include all letters of the alphabet.\n");
            printf("Missing: the letter %c\n", alphabet[y]);
            return 1;
            break;
        }
        else if (scanArray(key[1], alphabet[y], length) > 1)
        {
            printf("Your key has duplicate letters.\n");
            return 1;
            break;
        }
    }
}

int scanArray(string text, char element, int length)
{
    int elemCount = 0;
    for (int x = 0; x < length; x++)
    {
        if (tolower(text[x]) == tolower(element))
        {
            elemCount++;
        }
    }
    return elemCount;
}