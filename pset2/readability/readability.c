#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int wordCount = 0;
    int letterCount = 0;
    int sentenceCount = 0;
    string userIn = get_string("Text: ");
    int len = strlen(userIn);

    for (int i = 0; i < len; i++)
    {
        if (userIn[i] == " ")
        {
            wordCount++;
        }
        else if (userIn[i] == "!" || userIn[i] == "?" || userIn[i] == ".")
        {
            sentenceCount++;
        }
        else
        {
            letterCount++;
        }

    }

    float letterAvg = ((float)letterCount / (float)wordCount) * 100;
    float sentenceAvg = ((float)sentenceCount / (float)wordCount) * 100;

    int grade = round(0.0588 * letterAvg - 0.296 * sentenceAvg - 15.8);

    if (grade <= 1)
    {
        printf("Before Grade 1");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+");
    }

    else
    {
        printf("Grade %i", grade);
    }
}
