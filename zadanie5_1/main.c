#include <stdio.h>
#include <stdbool.h>

// Napisać program, który dla zadanej jako parametr liczby naturalnej n wypisze
// w kolejnych wierszach wszystkie permutacje liczb 1,2,...,n. Użyć rekurencyjnej
// funkcji do generowania permutacji.

void permutuj(int n);
bool nastepna_permutacja(int tab[], int n);
void wypisz_tablice(int tab[], int n);

int main() {
  int n;
  scanf("%d", &n);
  permutuj(n);
  return 0;
}

void permutuj(int n) {
  int tab[n];
  for (int i=0;i<n;i++)
    tab[i] = i+1;

  do {
    wypisz_tablice(tab, n);
  } while (nastepna_permutacja(tab, n));
}

bool nastepna_permutacja(int tab[], int n) {
  if (n == 1)
    return false;

  // Przesuniecie permutacji o jeden w lewo
  int tmp = tab[0];
  for (int i=0;i<n-1;i++) {
    tab[i] = tab[i+1];
  }
  tab[n-1] = tmp;

  // Zwracanie wartosci
  if (tab[n-1] == n) {
    return nastepna_permutacja(tab, n-1);
  } else {
    return true;
  }
}

void wypisz_tablice(int tab[], int n) {
  for (int i=0;i<n;i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");
}
