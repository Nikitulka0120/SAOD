#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char initial_string[] = "it's just a regular text, it's just a word that needs to be found, isn't it simple? just try to find \"just\" in this regular text, just do it";
char initial_substring[] = "just";

bool compare(const char *haystack, int start, const char *needle, int m)
{
    for (int i = 0; i < m; i++)
    {
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

    for (int i = 0; i <= string_len - substring_len; i++)
    {
        int j;
        for (j = 0; j < substring_len; j++)
        {
            if (string[i + j] != substring[j])
            {
                break;
            }
        }
        if (j == substring_len)
        {
            printf("\033[36mFound substring at index\033[0m \033[1m%d\033[0m\n", i);
        }
    }
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
    printf("\033[32m \033[21mRabinKarp search:\033[0m\n");
    printf("\033[34mString text:\033[0m%s\n", haystack);
    printf("\033[34mSubstring text:\033[0m%s\n", needle);
    int m = strlen(needle);
    int n = strlen(haystack);
    int hash_needle = hash_string(needle, 0, m - 1, q);
    int hash_haystack = hash_string(haystack, 0, m - 1, q);
    for (int i = 0; i <= n - m; i++)
    {
        if (hash_haystack == hash_needle)
        {
            if (compare(haystack, i, needle, m))
            {
                printf("\033[36mFound substring at index\033[0m \033[1m%d\033[0m\n", i);
            }
        }
        if (i < n - m)
        {
            hash_haystack = hash_string(haystack, i + 1, i + m, q);
        }
    }
    return -1;
}

int main()
{  
    int q=7;
    direct_search(initial_string, initial_substring);
    RabinKarp(initial_string, initial_substring, q);
}