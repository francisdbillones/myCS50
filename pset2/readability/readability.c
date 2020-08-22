#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //values
    int wordCount = 1;
    int letterCount = 0;
    int sentenceCount = 0;
    string userIn = get_string("Text: ");
    int len = strlen(userIn);

    //analyze the text
    for (int i = 0; i < len; i++)
    {
        if (userIn[i] == ' ')
        {
            wordCount++;
        }
        else if (userIn[i] == '!' || userIn[i] == '?' || userIn[i] == '.')
        {
            sentenceCount++;
        }
        else if (isalpha(userIn[i]) != 0)
        {
            letterCount++;
        }


    }

    float letterAvg = ((float)letterCount / (float)wordCount) * 100;
    float sentenceAvg = ((float)sentenceCount / (float)wordCount) * 100;

    int grade = round(0.0588 * letterAvg - 0.296 * sentenceAvg - 15.8);

    //special formatting
    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", grade);
    }
}
