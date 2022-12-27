#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_str(const void* a, const void* b) { return strcmp((char*)a, (char*)b); }
static char** sorted_array;

int factorial(int n)
{
    int ret_n = 1;
    for (int i = 2; i <= n; i++)
    {
        ret_n *= i;
    }
    return ret_n;
}

// Shift right of all the elements in `s` from position `i` to `j-1`
// Replace the `i`-th element with the original `j`-th element (befor shifting)
int swap_and_shift(char** s, int i, int j, int n)
{
    if (strcmp(s[i], s[j]) == 0 || strcmp(s[j], s[j - 1]) == 0)
    {
        // This swap would lead to an earlier or the same state 
        return 0;
    }
    char* tmp = s[j];
    for (int p = j; p > i; p--)
    {
        s[p] = s[p - 1];
    }
    s[i] = tmp;
    return 1;
}

int swapper(char** s, int* swapper, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (swapper[i])
        {
            if (!swap_and_shift(s, i, i + swapper[i], n))
            {
                return 0;
            }
        }
    }
    return 1;
}

int next_permutation(int n, char** s)
{
    /**
     * Complete this method
     * Return 0 when there is no next permutation and 1 otherwise
     * Modify array s to its next permutation
     */
    static int permutation_count = 1;
    if (permutation_count > factorial(n))
    {
        return 0;
    }
    int* permutations = (int*)malloc(sizeof(int) * (n - 1));

    if (permutation_count == 1)
    {
        sorted_array = (char**)malloc(sizeof(char*) * n);
        memcpy(sorted_array, s, sizeof(char**) * n);
    }
    do
    {
        memcpy(s, sorted_array, sizeof(char**) * n);
        int reminder = permutation_count;
        int fact;
        for (int i = 1; i < n; i++)
        {
            fact = factorial(n - i);
            if (reminder >= fact)
            {
                permutations[i - 1] = reminder / fact;
                reminder %= fact;
            }
            else
            {
                permutations[i - 1] = 0;
            }
        }

        permutation_count++;
        if (permutation_count > factorial(n))
        {
            free(permutations);
            return 0;
        }
    } while (swapper(s, permutations, n) == 0);
    free(permutations);
    return 1;
}

int main()
{
    char** s;
    int n;
    scanf("%d", &n);
    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        scanf("%s", s[i]);
    }
    do
    {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));
    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);
    return 0;
}
