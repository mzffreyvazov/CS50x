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
pair sorted_pair[MAX * (MAX - 1) / 2];

int candidate_count;
int pair_count;


// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
// Merge sorting algorithm
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


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
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;

            }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // Update the preferences array using ranks array
    for (int a = 0; a < candidate_count; a++) {
        for (int b = a + 1; b < candidate_count; b++) {
            preferences[ranks[a]][ranks[b]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] != preferences[j][i]) {
                if (preferences[i][j] > preferences[j][i]) {
                    pairs[i+(j-1)].winner = i;
                    pairs[i+(j-1)].loser = j;
                    pair_count++;

                } else {
                    pairs[i+(j-1)].winner = j;
                    pairs[i+(j-1)].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // pair sorted_pairs[pair_count];
    int strengths[pair_count];
    for (int i = 0; i < pair_count; i++) {
        strengths[i] = preferences[pairs[i].winner][pairs[i].loser];
    }
    // Sort the strenghts array using merge sort
    int sizeof_strengths = sizeof(strengths) / sizeof(strengths[0]);
    mergeSort(strengths, 0, sizeof_strengths - 1);
    // Reverse the strength array
    int start = 0;
    int end = sizeof_strengths - 1;
    while (start < end) {
        int temp = strengths[start];
        strengths[start] = strengths[end];
        strengths[end] = temp;
        start++;
        end--;
    }
    // Create a sorted version of pairs array
    int upvar = 0;
    for (int j = 0; j < 5; j++) {
        for (int c = 0; c < 5; c++) {
            if (strengths[j] == preferences[pairs[c].winner][pairs[c].loser] && c != upvar) {
                sorted_pair[j].winner = pairs[c].winner;
                sorted_pair[j].loser = pairs[c].loser;
                upvar = c;
                break;
            }
        }

    }
    // Replace the elements of sorted_pair array with the original pairs array
    // (technically we don't need to do this but the program wants the actual pairs array to be sorted)
    for (int i = 0; i < sizeof_strengths; i++) {
        pairs[i].winner = sorted_pair[i].winner;
        pairs[i].loser = sorted_pair[i].loser;
    }

    return;
}

bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && has_cycle(winner,i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Set all the elements of lock_pairs array to false

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            locked[i][j] = false;
        }
    }
    // Create locked graph
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if(!has_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
for (int col = 0; col < candidate_count; col++)
    {
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == true)
            {
                break;
            }
            else if (row == candidate_count - 1)
            {
                printf("%s\n", candidates[col]);
            }
        }
    }

    return;
}