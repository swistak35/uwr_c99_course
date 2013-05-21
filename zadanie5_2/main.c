#include <stdio.h>
#include <stdbool.h>

// Kwadratem magicznym rozmiaru N nazywamy tablicę kwadratową rozmiaru N x N,
// w której pola wpisane zostały liczby od 1 do N² w taki sposób, że każda z nich
// występuje dokładnie jeden raz oraz sumy wierszy, sumy kolumn oraz sumy głównych
// przekątnych są takie same. Napisać program, który dla zadanego N wypisuje na
// standardowym wyjściu kolejne, różne kwadraty magiczne rozmiaru N i pyta, czy
// kontynuować wypisywanie. Rozmiar powinien być zadawany jako parametr wywołania programu.

void nastepna_permutacja(int tab[], int k);
void wypisz_kwadrat(int tab[]);
bool kwadrat_magiczny(int tab[]);
void zamien(int tab[], int a, int b);

// Dlaczego użyłem zmiennych globalnych?
// Ponieważ używa ich się wszędzie, a praktycznie nigdzie nie modyfikuje (tylko j, który robi jako licznik)
//   więc trochę nie ma sensu za każdym razem przekazywać te dane do funkcji i tracić niepotrzebnie zasoby.
int n, nkw, suma, j;

int main(int argc, char** argv) {
    // n to bok kwadratu, nkw to "pole" kwadratu,
    //   czyli liczba pol w tablicy
    // Program jest tak złożony, że nie przeszkadza założenie, że n to liczba jednocyfrowa
    n = argv[1][0] - '0';
    printf("Liczba N: %d\n\n", n);

    nkw = n*n;

    // Licznik zliczajacy kwadraty
    j = 1;

    // Obliczanie sumy, jaka musi być w kazdym rzedzie
    suma = 0;
    for (int i=1;i<=nkw;i++)
        suma += i;
    suma /= n;

    // Inicjalizacja pol liczbami 1, 2, 3, ..., n^2
    int tab[nkw];
    for (int i=0;i<nkw;i++)
        tab[i] = i+1;

    // Wywolanie wlasciwej funkcji
    nastepna_permutacja(tab, nkw);
    return 0;
}

bool kwadrat_magiczny(int tab[]) {
    int tmpsuma;

    // Pierwsza przekatna
    tmpsuma = 0;
    for (int i=0;i<n;i++)
        tmpsuma += tab[i*n+i];
    if (tmpsuma != suma)
        return false;

    // Druga przekatna
    tmpsuma = 0;
    for (int i=1;i<=n;i++)
        tmpsuma += tab[i*(n-1)];
    if (tmpsuma != suma)
        return false;

    // Kolumny
    for (int i=0;i<n;i++) {
        tmpsuma = 0;
        for (int j=0;j<n;j++)
            tmpsuma += tab[i+j*n];
        if (tmpsuma != suma)
            return false;
    }

    // Rzedow nie sprawdzamy, bo niewlasciwe na biezaco odcinamy
    return true;
}

void wypisz_kwadrat(int tab[]) {
    printf("-------------------------\n");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            printf("%d ", tab[i*n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void zamien(int tab[], int a, int b) {
    int tmp;
    tmp = tab[a];
    tab[a] = tab[b];
    tab[b] = tmp;
}

void nastepna_permutacja(int tab[], int k) {
    int tmpsuma, indeks;
    int roznica = nkw - k;

    if (roznica % n == 0) {
        for (int i=0;i<(roznica/n);i++) {
            tmpsuma = 0;
            for (int j=0;j<n;j++) {
                // Trochę dziwny wzór, ale chodzi tylko o zsumowanie ostatnich kawałków
                //   i jeśli są różne od sumy, której potrzebujemy, to odcinamy
                indeks = nkw - i*n - j - 1;
                tmpsuma += tab[indeks];
            }
            if (tmpsuma != suma)
                return;
        }
    }

    // Algorytm permutacji przez selekcję
    if (k == 1) {
        if (kwadrat_magiczny(tab)) {
            printf("   Kwadrat nr %d\n", j++);
            wypisz_kwadrat(tab);
            getchar();
        }
    } else {
        nastepna_permutacja(tab, k-1);
        for (int i=0;i<k-1;i++) {
            zamien(tab, i, k-1);
            nastepna_permutacja(tab, k-1);
            zamien(tab, i, k-1);
        }
    }
}
