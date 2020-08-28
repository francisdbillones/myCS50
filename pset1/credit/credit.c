#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //gets card number from user
    long card;

    do
    {
        card = get_long("Enter your card number:");
    }
    while (card < 0); //checks if card number is positive

    //gets exact length of card
    int digits = 0;
    for (long cardD = card; cardD > 0; cardD /= 10)
    {
        digits++;
    }

    //checks if card digits match any digit standard
    if (digits != 13 && digits != 15 && digits != 16)
    {
        printf("INVALID\n");
        return false;
    }

    //checksum algorithm
    long cardC = card;
    int checksum1 = 0;
    int checksum2 = 0;
    int digitsum = 0;
    if (digits == 13 || digits == 15 || digits == 16)
    {
        while (cardC > 0)
        {
            checksum2 = checksum2 + (cardC % 10);
            cardC /= 10;
            if (((cardC % 10) * 2) > 9)
            {
                digitsum = ((cardC % 10) * 2);
                checksum1 += ((digitsum / 10) + (digitsum % 10));
            }
            else
            {
                checksum1 = checksum1 + ((cardC % 10) * 2);
            }
            cardC /= 10;
        }
        int totalChecksum = checksum1 + checksum2;
        
        //checking validity of checksum
        if ((totalChecksum % 10) == 0)
        {
            if (digits == 16)
            {
                if ((card / 100000000000000) == 51 || (card / 100000000000000) == 52 || (card / 100000000000000)== 53 || (card / 100000000000000) == 54 || (card / 100000000000000) == 55)
                {
                    printf("MASTERCARD\n");
                }
                else if ((card / 1000000000000000) == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (digits == 15)
            {
                if ((card / 1000000000000) == 34 || (card / 10000000000000) == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                if ((card / 1000000000000) == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}








