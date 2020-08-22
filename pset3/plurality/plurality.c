#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

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

    for (int n = 0; n < voterCount; n++)
    {
        string name = get_string("Voter %i's vote: ", n + 1);
        
        //checks for invalid usage
        if (!vote(name, candidateCount))
        {
            printf("Invalid vote.\n");
        }
    }

    printWinner(candidateCount);
    for (int a = 0; a < candidateCount; a++)
    {
        printf("%s\n", candidates[a].name);
    }
    
}

bool vote(string name, int candidateCount)
{
    for (int m = 0; m < candidateCount; m++)
    {
        if (strcmp(makeLower(candidates[m].name), makeLower(name)) == 0)
        {
            candidates[m].votes += 1;
            return true;
        }
    }
    return false;
}

void printWinner(int candidateCount)
{
    int biggest = 0;
    for (int k = 0; k < candidateCount; k++)
    {
        if (candidates[k].votes > biggest)
        {
            biggest = candidates[k].votes;
        }
    }

    printf("Winner(s):\n");

    for (int e = 0; e < candidateCount; e++)
    {
        if (candidates[e].votes == biggest)
        {
            printf("Candidate %s\n", candidates[e].name);
        }
    }
}

string makeLower(string inWord)
{
    string word = inWord;
    for (int i = 0; i < strlen(word); i++)
    {
        if (islower(word[i]) == 0)
        {
            word[i] = tolower(word[i]);
        }
    }
    return word;
}