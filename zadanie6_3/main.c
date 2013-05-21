#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "sort_benchmark.h"

// Zdefiniować moduł służący do testowania sprawności różnych algorytmów sortowania liczb całkowitych.
// Moduł powinien mieć generator pseudolosowych ciągów o zadanej w parametrze długości (użyć funkcji
// rand z biblioteki stdlib do otrzymywania pseudolosowej wartości całkowitej), funkcję sprawdzającą,
// czy wynik sortowania jest poprawny (tzn. czy wynik jest permutacją ciągu wejściowego i czy jest
// uporządkowany niemalejąco) oraz funkcję obliczającą minimalny, średni oraz maksymalny czas
// wykonania zadanego algorytmu dla podanej liczby zestawów danych zadanej długości (użyć funkcji clock
// z time.h). Następnie, używając zdefiniowanego modułu, porównać sprawności wybranego,
// zaprogramowanego algorytmu sortowania oraz standardowej procedury qsort z biblioteki stdlib dla
// 100 zestawów wygenerowanych danych o rozmiarach 5000, 10000 i 50000. Wyznaczyć należy minimalny,
// średni i maksymalny czas działania każdego z algorytmów dla podanych rozmiarów danych.
// W pomiarach nie należy sprawdzać poprawności wyników.

// Uwagi: Algorytm sprawdzania posortowania jest poprawny tylko wtedy, gdy tablica nie zawiera powtórzeń.

// Do wyboru bubble sort i insertion sort, w programie głównym użyłem insertion sort,
//   bo działa szybciej i ładniej wygląda porównanie wyników

void swap(void *a, void *b, size_t size);
void bubble_sort(void * base, size_t num, size_t size, int (*compare)(const void *, const void *));
void insertion_sort(void * base, size_t num, size_t size, int (*compare)(const void *, const void *));

int main() {
    struct result result_insertion;
    struct result result_qsort;

    testuj_algorytm(100, 5000, &result_insertion, &result_qsort, insertion_sort, qsort);
    printf("100 zestawów po 5000 znaków:\n");
    printf("\tinsertion_sort:\n");
    printf("\t\tmin: %f\n", result_insertion.min);
    printf("\t\tmax: %f\n", result_insertion.max);
    printf("\t\taverage: %f\n", result_insertion.average);
    printf("\tqsort:\n");
    printf("\t\tmin: %f\n", result_qsort.min);
    printf("\t\tmax: %f\n", result_qsort.max);
    printf("\t\taverage: %f\n", result_qsort.average);

    testuj_algorytm(100, 10000, &result_insertion, &result_qsort, insertion_sort, qsort);
    printf("100 zestawów po 10000 znaków:\n");
    printf("\tinsertion_sort:\n");
    printf("\t\tmin: %f\n", result_insertion.min);
    printf("\t\tmax: %f\n", result_insertion.max);
    printf("\t\taverage: %f\n", result_insertion.average);
    printf("\tqsort:\n");
    printf("\t\tmin: %f\n", result_qsort.min);
    printf("\t\tmax: %f\n", result_qsort.max);
    printf("\t\taverage: %f\n", result_qsort.average);

    testuj_algorytm(100, 50000, &result_insertion, &result_qsort, insertion_sort, qsort);
    printf("100 zestawów po 50000 znaków:\n");
    printf("\tinsertion_sort:\n");
    printf("\t\tmin: %f\n", result_insertion.min);
    printf("\t\tmax: %f\n", result_insertion.max);
    printf("\t\taverage: %f\n", result_insertion.average);
    printf("\tqsort:\n");
    printf("\t\tmin: %f\n", result_qsort.min);
    printf("\t\tmax: %f\n", result_qsort.max);
    printf("\t\taverage: %f\n", result_qsort.average);

    return 0;
}

void swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, b, size);
    memcpy(b, a, size);
    memcpy(a, tmp, size);
}

void bubble_sort(void * base, size_t num, size_t size, int (*compare)(const void *, const void *)) {
    void * i;
    void * j;
    void * end;
    end = base + num * size;

    for(i = base; i < end; i += size) {
		for(j = base; j < (end-size); j += size) {
            if ((*compare)(j, j+size) > 0) {
				swap(j, j+size, size);
			}
		}
	}
}

void insertion_sort(void * base, size_t num, size_t size, int (*compare)(const void *, const void *)) {
    void * i;
    void * j;
    void * value = (void*) malloc(size);
    void * end = base + num * size;

    for(i = (base+size); i < end; i += size) {
        memcpy(value, i, size);

        for (j = (i - size); (j >= base) && (compare(j, value) > 0); j -= size) {
            memcpy(j+size, j, size);
        }
        memcpy(j+size, value, size);
    }
}
