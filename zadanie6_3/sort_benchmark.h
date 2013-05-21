#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RANGE 10000

struct result {
    float min;
    float max;
    float average;
};

void generate_random_array(int tab[], int n);
int compare_int(const void * a, const void * b);
void testuj_algorytm(int n, int length, struct result * result1, struct result * result2, void (*funkcja1)(void * base, size_t num, size_t size, int (*compare)(const void *, const void *)), void (*funkcja2)(void * base, size_t num, size_t size, int (*compare)(const void *, const void *)));
bool sprawdz_wynik(int unsorted[], int sorted[], int n);
