#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size; 
    do
    {
        size = get_int("How tall do you want your pyramid to be?:\n");
    }
    while (size < 1 || size > 8);
    
    //master loop for rows
    for (int height = 0; height < size; height++)
    {
        //loop for spaces
        for (int blank = (size - height) - 1; blank > 0; blank--)
        {
            printf(" ");
        }
        //loop for left hashes
        for (int hashesL = (height + 1); hashesL > 0; hashesL--)
        {
            printf("#");
        }
        
        printf("  ");
        
        //loop for right hashes
        for (int spacesR = (height + 1); spacesR > 0; spacesR--)
        {
            printf("#");
        }
        
        printf("\n");
    }
}