#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int start, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // for loop to check if name is in candiates array and update ranks array if this is the case
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {

            ranks[rank] = i;
            // printf("Rank[%i] - %i\n", rank, i);
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //printf("pref[%i][%i] - %i\n",ranks[i] ,ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                // printf ("pair: %i - %i\n", i, j);
            }
        }


        // printf ("pair[%i]: %i - %i\n", i,  pairs[i].winner, pairs[i].loser);
    }
    // printf ("pairs = %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //printf ("Pre Sort:\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf ("Pair %i: %i(%i) - %i(%i)\n", i, pairs[i].winner, preferences[pairs[i].winner][pairs[i].loser], pairs[i].loser, preferences[pairs[i].loser][pairs[i].winner]);
    // }
    // printf("\n");
    // printf ("Post Sort:\n");
    for (int i = 0; i < pair_count; i++)
    {
        int temp = i;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                temp = j;
            }
        }

        int temp_win;
        int temp_lose;

        temp_win = pairs[i].winner;
        temp_lose = pairs[i].loser;

        pairs[i].winner = pairs[temp].winner;
        pairs[temp].winner = temp_win;

        pairs[i].loser = pairs[temp].loser;
        pairs[temp].loser = temp_lose;

        // printf ("Pair %i: %i(%i) - %i(%i)\n", i, pairs[i].winner, preferences[pairs[i].winner][pairs[i].loser], pairs[i].loser, preferences[pairs[i].loser][pairs[i].winner]);
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //lock highest pair
    //check if cycle to highest
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf ("Pair %i: %i - %i Locked: %i\n", i, pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser]);
    // }

    return;

}

bool cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO


    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                false_count++;

                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }

            }

        }

    }

    return;
}

