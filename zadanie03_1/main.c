#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Napisać funkcję, która dla zadanej jako parametr liczby dodatniej n wyznaczy najbliższą,
// większą od niej liczbę pierwszą. Następnie napisać program, który wczytuje ze standardowego
// wejścia parę liczb n i k oraz - używając zdefiniowanej funkcji - wypisuje na standardowym
// wyjściu k kolejnych liczb pierwszych większych od n. Dla n użyć typu long long int,
// a dla k typu int. Zadbać o efektywność sprawdzania, czy liczba jest pierwsza.

int czy_pierwsza(long long int x);
long long int kolejna_pierwsza(long long int x);

long long int kolejna_pierwsza(long long int x) {
  if (x == 1) return 2;
  if (x == 2) return 3;

  while (true) {
    x++;
    if (czy_pierwsza(x) == 1) {
      return x;
    }
  }
}

int czy_pierwsza(long long int x) {
  // return 0 - nie jest liczba pierwsza
  // return 1 - jest liczba pierwsza
  long long int pierwiastek_x = sqrt(x);

  // 1 nie jest liczbą pierwszą
  if (x == 1) return 0;

  // 2 jest liczbą pierwszą
  if (x == 2) return 1;

  // żadna liczba parzysta > 2 nie jest liczbą pierwszą
  if (x % 2 == 0) return 0;


  for (int i=3;i<=pierwiastek_x;i+=2) {
    // jeśli liczba ma jakiś dzielnik, to nie jest pierwsza
    if (x % i == 0)
      return 0;
  }

  // jeśli żadna z liczb nie dzieliła x, to jest to liczba pierwsza
  return 1;
}

int main() {
  long long int n;
  int k;
  scanf("%lld", &n);
  scanf("%d", &k);

  for (int i=0;i<k;i++) {
    n = kolejna_pierwsza(n);
    printf("%lld\n", n);
  }

  return 0;
}
