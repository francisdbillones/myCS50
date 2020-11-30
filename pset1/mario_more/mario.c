#include <stdio.h>
#include <cs50.h>

void draw(int height, int h);

int main(void)
{
    int size; 
    do
    {
        size = get_int("How tall do you want your pyramid to be?:");
    }
    while (size < 1 || size > 8);
    
    draw(size,size);
}

void draw(int height, int h)
{
    if (h == 0)
    {
        return;
    }
    
    draw(height, h-1);

    for (int n = h; n < height; n++)
    {
        printf(" ");
    }
    for (int m = (height - h); m < height; m++)
    {
        printf("#");
    }
    
    printf("  ");

    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}