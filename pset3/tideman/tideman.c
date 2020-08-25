#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name)==0)
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count-1; i++)
    {

        for (int j = i+1 ; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]+=1;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0 ; j < candidate_count; j++)
        {
            if(i!=j)
            {
                if(preferences[i][j]>preferences[j][i])
                {
                    pairs[pair_count].winner=i;
                    pairs[pair_count].loser=j;
                    pair_count+=1;
                }
            }
        }

    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int temp1;
    int temp2;
    for (int i = 0; i < pair_count-1; i++)
    {
        for (int j = 1 ; j < pair_count; j++)
        {
            if(preferences[pairs[j].winner][pairs[j].loser]>preferences[pairs[j-1].winner][pairs[j-1].loser])
            {
                temp1=pairs[j].winner;
                temp2=pairs[j].loser;
                pairs[j].winner=pairs[j-1].winner;
                pairs[j].loser=pairs[j-1].loser;
                pairs[j-1].winner=temp1;
                pairs[j-1].loser=temp2;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int rec;
    int count_cycle;
    int temp1,temp2;
    int check[MAX]={0};
    int isvalid[MAX]={0};
    int j=pair_count-1;
    while (true)
    {
        if (j<0)
        {
            break;
        }
        if (check[j]!=1)
        {
            count_cycle=0;
            rec=j-1;
            temp2=pairs[j].winner;
            temp1=pairs[j].loser;
            while (true)
            {
                if (rec<0)
                {
                    break;
                }
                if (temp2==pairs[rec].loser)
                {
                    temp2=pairs[rec].winner;
                    count_cycle+=1;
                    isvalid[count_cycle]=pairs[rec].winner;
                }
                if (count_cycle>=2 && temp1==pairs[rec].winner && isvalid[count_cycle-1]==pairs[rec].loser)
                {
                    check[j]=1;
                    j=pair_count;
                    break;
                }
                rec-=1;
            }
        }
        j-=1;
    }
    for (int i = 0 ; i < pair_count; i++)
    {
        if (check[i]!=1)
        {
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
    }
}
// Print the winner of the election
void print_winner(void)
{
    bool flag=false;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i])
            {
                flag=true;
                break;
            }
        }
        if (!flag)
        {
            printf("%s\n", candidates[i]);
        }
        flag=false;
    }
    return;
}

