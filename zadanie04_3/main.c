#include <stdio.h>
#include "wymierne.h"
#include "wielomiany.h"

// Zdefiniować za pomocą typedef nowy typ reprezentujący w tablicy wielomian jednej zmiennej
// o współczynnikach wymiernych. Użyć reprezentacji liczb wymiernych z poprzedniego zadania.
// Dla takich wielomianów zdefiniować funkcje wykonujące ich dodawanie, odejmowanie, mnożenie
// i dzielenie oraz operacje czytania, pisania i wyliczania wartości wielomianu w punkcie
// wymiernym. Sformułować z nich moduł i stworzyć plik nagłówkowy. Następnie napisać program
// testujący poprawność zdefiniowanych funkcji.

// Uwagi: Ostrzeżenia przy kompilacji:
// wymierne.c:44:5: warning: left shift count >= width of type [enabled by default]
// main.c:11:5: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘wymierna’ [-Wformat]
// ale po ich usunieciu działa poprawnie.

int main() {
    wielomian w1, w2, wout, wr;
    wymierna wynik, x;
    x = konwertuj(-3, 1);
    printf("Czy zero: %d\n", konwertuj(0, 1));
    printf("Wielomiany podajemy w formacie:\n");
    printf("n a0 a1 a2 a3 a4 ... an gdzie n to stopień wielomianu,\na a1...an to jego wspolczynniki w formacie licznik/mianownik.\n");

    printf("Podaj pierwszy wielomian: ");
    wczytaj_wielomian(w1);

    printf("Podaj drugi wielomian: ");
    wczytaj_wielomian(w2);

    dodawanie(w1, w2, wout);
    printf("\nSuma: ");
    wyswietl_wielomian(wout);

    odejmowanie(w1, w2, wout);
    printf("\nRoznica: ");
    wyswietl_wielomian(wout);

    mnozenie(w1, w2, wout);
    printf("\nIloczyn: ");
    wyswietl_wielomian(wout);

    dzielenie(w1, w2, wout, wr);
    printf("\nIloraz: ");
    wyswietl_wielomian(wout);
    printf("\nReszta: ");
    wyswietl_wielomian(wr);


    wynik = obliczanie_wartosci(w1, x);
    printf("Wartość wielomianu 1 dla x = -3: ");
    wypisz(wynik);


    return 0;
}
