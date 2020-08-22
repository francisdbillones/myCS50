#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <strings.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

//function prototypes
bool vote(string name, int candidateCount);
void printWinner(int candidateCount);
string makeLower(string inWord);

int main(int argc, string argv[])
{
    //checks for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }
    else if (argc > MAX + 1)
    {
        printf("Maximum number of candidates is %i.\n", MAX);
        return 2;
    }

    int candidateCount = argc - 1;

    for (int i = 0; i < candidateCount; i++)
    {
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
    }

    int voterCount = get_int("Number of voters: ");

    for (int i = 0; i < voterCount; i++)
    {
        string name = get_string("Voter %i's vote: ", i + 1);

        //checks for invalid usage
        if (!vote(name, candidateCount))
        {
            printf("Invalid vote.\n");
        }
        
    }

    printWinner(candidateCount);
    
}

bool vote(string name, int candidateCount)
{
    for (int i = 0; i < candidateCount; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

void printWinner(int candidateCount)
{
    int biggest = 0;
    for (int i = 0; i < candidateCount; i++)
    {
        if (candidates[i].votes > biggest)
        {
            biggest = candidates[i].votes;
        }
    }

    printf("Winner(s):\n");

    for (int i = 0; i < candidateCount; i++)
    {
        if (candidates[i].votes == biggest)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}