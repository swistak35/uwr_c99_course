#include <stdio.h>
#include <math.h>

// Napisać program, który korzystając z rozwinięcia liczby pi w szereg
// wyznaczy i wydrukuje jej wartość z dokładnością do maksymalnej
// liczby miejsc po przecinku, którą można uzyskać dla typów double
// i long double. Definicje takich szeregów oraz początkowe cyfry rozwinięcia
// liczby pi można znaleźć np. w Wikipedii. Spośród wielu możliwych szeregów
// należy wybrać taki, który jest szybko zbieżny.

int main() {
  double pi_d, arg_d0, arg_d1, arg_d2, arg_d3, arg_d4;
  long double pi_ld, arg_ld0, arg_ld1, arg_ld2, arg_ld3, arg_ld4;

  // Zerowanie zmiennych
  pi_d = 0;
  pi_ld = 0;

  for (int k=0;k<14;k++) {
    // Czesc liczaca double PI
    arg_d0 = (1.0/pow(16,k));
    arg_d1 = (4.0/(8.0*k + 1.0));
    arg_d2 = (2.0/(8.0*k + 4.0));
    arg_d3 = (1.0/(8.0*k + 5.0));
    arg_d4 = (1.0/(8.0*k + 6.0));
    pi_d += arg_d0*(arg_d1 - arg_d2 - arg_d3 - arg_d4);

    // Czesc liczaca long double PI
    arg_ld0 = (1.0/pow(16,k));
    arg_ld1 = (4.0/(8.0*k + 1.0));
    arg_ld2 = (2.0/(8.0*k + 4.0));
    arg_ld3 = (1.0/(8.0*k + 5.0));
    arg_ld4 = (1.0/(8.0*k + 6.0));
    pi_ld += arg_ld0*(arg_ld1 - arg_ld2 - arg_ld3 - arg_ld4);
  }

  printf("Double PI: %17.15f\n", pi_d);
  printf("Long double PI: %20.18Lf\n", pi_ld);
  return 0;
}
