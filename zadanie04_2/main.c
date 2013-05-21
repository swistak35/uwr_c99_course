#include <stdio.h>
#include <limits.h>
#include "wymierne.h"

// Zdefiniować za pomocą typedef nowy typ reprezentujący liczbę wymierną jako long long int,
// w której licznik i mianownik są zapisane na odpowiednich połowach ciągu bitów. Licznik
// i mianownik zapisywane w tym typie nie powinny mieć nietrywialnego wspólnego dzielnika,
// a mianownik powinien być nieujemny. Dla nowego typu zdefiniować funkcje wykonujące cztery
// podstawowe działania oraz operacje czytania i wypisywania liczby wymmiernej. Wprowadzone
// i drukowane liczby wymierne powinny mieć postać n/m. Sformować z nich moduł i stworzyć plik
// nagłówkowy. Następnie napisać drugi moduł zawierający program testujący poprawność
// zdefiniowanych funkcji.

// Uwagi: Ładnie, alew funkcji konwertuj brakowało rzutowania licznika na long long int,
// tzn:return (((wymierna)licznikx

int main() {
    wymierna x,y,z;

    printf("Podaj pierwszą liczbę wymierną w formacie licznik/mianownik: ");
    x = wczytaj();

    printf("Podaj drugą liczbę wymierną w formacie licznik/mianownik: ");
    y = wczytaj();

    z = suma(x,y);
    printf("\nSuma: ");
    wypisz(z);

    z = roznica(x, y);
    printf("\nRoznica: ");
    wypisz(z);

    z = iloczyn(x,y);
    printf("\nIloczyn: ");
    wypisz(z);

    z = iloraz(x, y);
    printf("\nIloraz: ");
    wypisz(z);

    return 0;
}
