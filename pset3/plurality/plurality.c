#include <string.h>
#include <stdio.h>
#include <cs50.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

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

    int voterCount = get_int("Number of voters:");

    for (int n = 0; n < voterCount; n++)
    {
        string name = get_string("Voter %i's vote:", n + 1);
        
        //checks for invalid usage
        if (!vote(string))
        {
            printf("Invalid vote.\n");
        }
    }
}