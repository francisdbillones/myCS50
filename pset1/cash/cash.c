#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //values
    float change_float = get_float("How much change do you want?: $");
    int change_int = round(change_float * 100);
    int quarters = 0;
    int dimes = 0; 
    int nickels = 0; 
    int pennies = 0;
    printf("%i\n", change_int);
    
    
    //algorithm
    while ((change_int - 25) >= 0)
    {
        change_int -= 25;
        quarters += 1;
    }
    
    while ((change_int - 10) >= 0)
    {
        change_int -= 10;
        dimes += 1;
    }
    
    while ((change_int - 5) >= 0)
    {
        change_int -= 5;
        nickels += 1;
    }
    
    while ((change_int - 1) >= 0)
    {
        change_int -= 1;
        pennies += 1;
    }

    printf("Your change is %i quarters, %i dimes, %i nickels, and %i pennies\n", quarters, dimes, nickels, pennies);
}