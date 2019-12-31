#include <string.h>
#include <cs50.h>
#include <stdio.h>

#define HASHTABLE_SIZE 65536;

int hash_it(char* needs_hashing);

int main(void)
{
    char* word = "cat";
    hash_it(word);
}

int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    int n = hash % HASHTABLE_SIZE;
    printf("%i", n);
    
    return 0;
}