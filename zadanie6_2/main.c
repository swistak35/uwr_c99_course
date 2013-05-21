#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Numer rachunku bankowego w standardzie IBAN (ang. International Bank Account Number)
// składa się z dwuliterowego kodu kraju (dla Polski - PL), po którym następują dwie cyfry
// sprawdzające (suma kontrolna), i do trzydziestu znaków alfanumerycznych określających numer
// rachunku, określanych jako BBAN (Basic Bank Account Number). Decyzja o długości tego bloku
// należy do poszczególnych krajów z tym, że dany kraj musi posiadać jedną, określoną
// długość (w Polsce wynosi ona 24). W BBAN musi się zawierać unikatowy kod identyfikujący bank,
// o określonej długości i określonym miejscu, w którym się on rozpoczyna. Jego pozycja
// i długość również zależy od danego kraju (w Polsce 8 pierwszych znaków BBAN-u). Napisać program,
// który wczytuje ze standardowego wejścia pewną liczbę numerów kont bankowych w standardzie
// IBAN (nie więcej niż MAX=10000, każdy w oddzielnym wierszu), sortuje je leksykograficznie
// z pominięciem cyfr kontrolnych wybranym przez siebie algorytmem i wypisuje w kolejności nierosnącej
// na standardowym wyjściu. Aby przyspieszyć sortowanie przestawiać należy wskaźniki na
// numery bankowe, a nie same numery.

int compare(char * tab1, char * tab2) {
    // Najpierw sprawdzamy pierwszy znak (kod kraju)
    if (tab1[0] != tab2[0])
        return (tab1[0] - tab2[0]);

    // Potem drugi znak z kodu kraju
    if (tab1[1] != tab2[1])
        return (tab1[1] - tab2[1]);

    int i = 4; // Pomijamy 2 cyfry kontrolne
    while (tab1[i] == tab2[i] && tab1[i] != 0 && tab2[i] != 0 && i < 40)
        i++;

    if (tab1[i] == 0 && tab2[i] != 0) {
        return -1;
    } else if (tab2[i] == 0 && tab1[i] != 0) {
        return 1;
    } else {
        return tab1[i] - tab2[i];
    }
    return 0;
}

// Quicksort
void sort(char **array, int begin, int end) {
   char * temp;
   if (end > begin) {
      char * pivot = array[begin];
      int l = begin + 1;
      int r = end;
      while(l < r) {
         if (compare(array[l],pivot) <= 0) {
            l += 1;
         } else {
            r -= 1;
            temp = array[l];
            array[l] = array[r];
            array[r] = temp;
         }
      }
      // Zamiana pivot z odpowiednim elementem
      l -= 1;
      temp = array[begin];
      array[begin] = array[l];
      array[l] = temp;

      sort(array, begin, l);
      sort(array, l+1, end);
   }
}

void my_qsort(char **array, int n) {
   sort(array, 0, n);
}


int main() {
    char * tab[10000];

    char string[40];
    int n = 0;
    while(gets(string) != NULL) {
        tab[n] = (char*) malloc (40);
        strcpy(tab[n], string);
        n++;
    }

    my_qsort(tab, n);

    for(int i=n-1;i>=0;i--) {
        printf("%s\n", tab[i]);
    }

    return 0;
}

