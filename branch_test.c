#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <x86intrin.h>

#define LOOP_INTERVAL (50000000UL)

volatile int test = 0;

void pattern_always(int *arr, size_t len);
void pattern_alternate(int *arr, size_t len);
void pattern_random(int *arr, size_t len);

int main(int argc, char **argv)
{
    size_t len = LOOP_INTERVAL;
    int *arr = malloc(sizeof(int) * len);
    if (NULL == arr) return 1;
    
    for (size_t i = 0; i < len; i++) arr[i] = 1;

    if (argc < 2) 
    {
        printf("Usage: %s always|alt|rand\n", argv[0]);
        return 1;
    }

    if (strncmp(argv[1], "always", 7) == 0) 
        pattern_always(arr, len);
    if (strncmp(argv[1], "alt", 4) == 0)
        pattern_alternate(arr, len);
    if (strncmp(argv[1], "rand", 5) == 0)
        pattern_alternate(arr, len);

    printf("Done, test = %d\n", test);
    return 0;
}

void pattern_always(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) 
    {
        if (arr[i]) ++test;
        else --test;
    }
}

void pattern_alternate(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) 
    {
        if (i&1) ++test;
        else --test;
    }
}

void pattern_random(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) 
    {
        if (rand() & 1) ++test;
        else --test;
    }
}
