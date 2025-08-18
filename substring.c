#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char initial_string[] = "justregulartextjustfindinthistextjustworditsjustaword";
char initial_substring[] = "just";

bool compare(const char *haystack, int start, const char *needle, int m, int *comp)
{
    for (int i = 0; i < m; i++)
    {
        (*comp)++;
        if (haystack[start + i] != needle[i])
        {
            return false;
        }
    }
    return true;
}

int direct_search(char *string, char *substring)
{
    printf("\033[32m \033[21mDirect search:\033[0m\n");
    int string_len = strlen(string);
    int substring_len = strlen(substring);
    printf("\033[34mString text:\033[0m%s\n", string);
    printf("\033[34mSubstring text:\033[0m%s\n", substring);
    printf("\033[33mLen of string is\033[0m %d chars\n", string_len);
    printf("\033[33mLen of substring is\033[0m %d chars\n", substring_len);
    int direct_comp = 0;
    for (int i = 0; i <= string_len - substring_len; i++)
    {
        if (compare(string, i, substring, substring_len, &direct_comp))
        {
            printf("\033[36mFound substring at index\033[0m \033[1m%d\033[0m\n", i);
        }
    }
    printf("\033[35mTotal comparisons in Direct search: %d\033[0m\n", direct_comp);
    return -1;
}

int hash_string(const char *str, int start, int end, int q)
{
    int hash = 0;
    for (int i = start; i <= end; i++)
    {
        hash = (hash * 256 + (unsigned char)str[i]) % q;
    }
    return hash;
}

int RabinKarp(char *haystack, char *needle, int q)
{
    printf("\033[32m \033[21mRabinKarp search (q=%d):\033[0m\n", q);
    printf("\033[34mString text:\033[0m%s\n", haystack);
    printf("\033[34mSubstring text:\033[0m%s\n", needle);
    int m = strlen(needle);
    int n = strlen(haystack);
    int RabinKarp_comp = 0;
    int hash_needle = hash_string(needle, 0, m - 1, q);
    int hash_haystack = hash_string(haystack, 0, m - 1, q);
    for (int i = 0; i <= n - m; i++)
    {
        if (hash_haystack == hash_needle)
        {
            if (compare(haystack, i, needle, m, &RabinKarp_comp))
            {
                printf("\033[36mFound substring at index\033[0m \033[1m%d\033[0m\n", i);
            }
        }
        if (i < n - m)
        {
            hash_haystack = hash_string(haystack, i + 1, i + m, q);
        }
    }
    printf("\033[35mTotal comparisons in RabinKarp: %d\033[0m\n", RabinKarp_comp);
    return -1;
}

int main()
{
    int q[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    direct_search(initial_string, initial_substring);
    for (int i = 0; i < 10; i++)
    {
        RabinKarp(initial_string, initial_substring, q[i]);
    }
}
