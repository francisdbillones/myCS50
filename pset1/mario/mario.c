#include <stdio.h>
#include <cs50.h>

void draw(int height);

int main(void)
{
    int size; 
    do
    {
        size = get_int("How tall do you want your pyramid to be?:");
    }
    while (size < 1 || size > 8);
    
    draw(size);
}

void draw(int height)
{
    if (height == 0)
    {
        return;
    }

    draw(height-1);

    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");
}