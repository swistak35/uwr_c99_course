#include "sort_benchmark.h"

void generate_random_array(int tab[], int n) {
    for (int i=0; i<n; i++) {
        tab[i] = rand() % RANGE;
    }
}

int compare_int(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

bool sprawdz_wynik(int unsorted[], int sorted[], int n) {
    // Najpierw sprawdzamy czy wszystkie elementy z unsorted są w sorted.
    int * bsearch_pointer;
    for (int i=0;i<n;i++) {
        bsearch_pointer = (int*) bsearch(&unsorted[i], sorted, n, sizeof(int), compare_int);
        if (bsearch_pointer == NULL) {
            return false;
        }
    }

    // Sprawdz, czy są posortowane niemalejąco
    for (int i=1;i<n;i++) {
        if (sorted[i-1] > sorted[i]) {
            return false;
        }
    }

    return true;
}

void testuj_algorytm(int n, int length, struct result * result1, struct result * result2, void (*funkcja1)(void * base, size_t num, size_t size, int (*compare)(const void *, const void *)), void (*funkcja2)(void * base, size_t num, size_t size, int (*compare)(const void *, const void *))) {
    int sieve;
    sieve = time(NULL);
    srand(sieve);

    result1->min = 1000000;
    result1->max = 0;
    result1->average = 0;

    result2->min = 1000000;
    result2->max = 0;
    result2->average = 0;

    clock_t begin, end;
    float diff;

    int tab[length];

    for (int i=0;i<n;i++) {
        // Wygenerowanie tablicy i przekopiowanie jej do tab_sorted
        generate_random_array(tab, length);

        // Sortowanie przez funkcja1 i pomiary
        begin = clock();
        (*funkcja1)(tab, length, sizeof(int), compare_int);
        end = clock();

        diff = ((float) (end - begin)) / CLOCKS_PER_SEC;
        if (diff < result1->min)
            result1->min = diff;
        if (diff > result1->max)
            result1->max = diff;
        result1->average = (result1->average * i + diff) / (i+1);

        // Sortowanie przez funkcja2 i pomiary
        begin = clock();
        (*funkcja2)(tab, length, sizeof(int), compare_int);
        end = clock();

        diff = ((float) (end - begin)) / CLOCKS_PER_SEC;
        if (diff < result2->min)
            result2->min = diff;
        if (diff > result2->max)
            result2->max = diff;
        result2->average = (result2->average * i + diff) / (i+1);
    }
}
