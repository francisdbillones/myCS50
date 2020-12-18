#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define success 0
#define error 1

bool isMastercard(int first_two_digits, int digit_count);
bool isVisa(int first_two_digits, int digit_count);
bool isAmex(int first_two_digits, int digit_count);
int getDigitCount(long n);
bool validChecksum(long card);

int main(void)
{
    //gets card number from user
    //long card;

    long card;

    do{
        printf("Enter your card number: ");
        scanf("%ld", &card);
    }
    while (card < 0);

    //gets exact length of card
    int digit_count = getDigitCount(card);

    //checks if card digits match any digit standard
    if (digit_count != 13 && digit_count != 15 && digit_count != 16){
        printf("INVALID\n");
        return 0;
    }

    //checksum algorithm
    long cardC = card;
    int checksum1 = 0;
    int checksum2 = 0;
    int digitsum = 0;

    //checking validity of checksum
    if (validChecksum(card)){
        int first_two_digits = card / (pow(10, (digit_count-2)));

        if (isMastercard(first_two_digits, digit_count)){
            printf("MASTERCARD\n");
        }

        else if (isVisa(first_two_digits, digit_count)){
            printf("VISA\n");
        }

        else if (isAmex(first_two_digits, digit_count)){
            printf("AMEX\n");
        }

        else{
            printf("INVALID\n");
        }
    }
     
    else{
        printf("INVALID\n");
    }

    return 0;
}

bool validChecksum(long card){
    int checksum1 = 0;
    int checksum2 = 0;
    int digitsum = 0;

    while (card > 0){
        checksum2 += (card % 10);
        card /= 10;
        if (((card % 10) * 2) > 9){
            digitsum = ((card % 10) * 2);
            checksum1 += ((digitsum / 10) + (digitsum % 10));
        }
        else{
            checksum1 = checksum1 + ((card % 10) * 2);
        }
        card /= 10;
    }
    return ((checksum1 + checksum2) %10 == 0);
}

bool isMastercard(first_two_digits, digit_count){
    bool correctDigits = (first_two_digits-51 >= 0 && first_two_digits-51 <= 4);
    bool correctDigitCount = (digit_count == 16);
    
    if (correctDigitCount && correctDigits){
        return true;
    }
    return false;
}

bool isVisa(first_two_digits, digit_count){
    bool correctDigits = (first_two_digits / 10 == 4);
    bool correctDigitCount = (digit_count == 16 || digit_count == 13);

    if (correctDigitCount && correctDigits){
        return true;
    }
    return false;
}

bool isAmex(first_two_digits, digit_count){
    bool correctDigits = (first_two_digits == 34 || first_two_digits == 37);
    bool correctDigitCount = (digit_count == 15);

    if (correctDigitCount && correctDigits){
        return true;
    }
    return false;
}

int getDigitCount(long n){
    int digits = 0;

    while (n > 0){
        n/=10;
        digits++;
    }

    return digits;
}








