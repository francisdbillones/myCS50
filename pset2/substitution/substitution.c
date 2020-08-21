#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scanText(string text, char element, int length);
int searchArray(string array, char element, int length);

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
        if (isalpha(key[1][i]) == 0)
        {
            printf("Your key includes a non-alphabetical character = %c.\n",  key[0][i]);
            return 1;
            break;
        }
    }
    //completeness and duplicate filter
    for (int y = 0; y < 26; y++)
    {
        if (scanText(key[1], alphabet[y], length) == 0)
        {
            printf("Your key does not include all letters of the alphabet.\n");
            printf("Missing: the letter %c\n", alphabet[y]);
            return 1;
            break;
        }
        if (scanText(key[1], alphabet[y], length) > 1)
        {
            printf("Your key has duplicate letters.\n");
            return 1;
            break;
        }
    }

    //substitution algorithm
    string plaintext = get_string("Plaintext: ");
    for (int z = 0; z < strlen(plaintext); z++)
    {
        if (isalpha(plaintext[z]) != 0)
        {
            if (isupper(plaintext[z]) != 0)
            {
                plaintext[z] = toupper(key[1][searchArray(alphabet, tolower(plaintext[z]), 26 )]);
            }
            else
            {
                plaintext[z] = tolower(key[1][searchArray(alphabet, tolower(plaintext[z]), 26 )]);
            }
        }
    }
    printf("Ciphertext = %s\n", plaintext);
}

int scanText(string text, char element, int length)
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

int searchArray(string array, char element, int length)
{
    int elemIndex = 0;
    for (int q = 0; q < length; q++)
    {
        if (tolower(array[q]) == tolower(element))
        {
            elemIndex = q;
            return elemIndex;
            break;
        }
    }
    return elemIndex;
}