#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Napisać program, który przepisze tekst ze standardowego wejścia na standardowe wyjście
// umieszczając na wyjściu słowa rozdzielone pojedyńczą spacją w zadanym przedziale kolumn m...n,
// gdzie m < n < 200. Oznacza to, że każdy wiersz powinien się zaczynać m-1 znakami spacji,
// po których występuje ciąg kolejnych słów (co najmniej jedno) oddzielonych pojedyńczą spacją,
// a ostatni znak ostatniego słowa w wierszy znajduje się na pozycji <= n,
// gdzie pozycje (kolumny) w wierszu numerujemy od 1. Wartości m i n powinny być argumentami
// wywołania programu. Jeśli w tekście wejściowym pojawi się słowo dłuższe niż n-m+1 to można
// przerwać działanie programu z czytelnym komunikatem. Słowem nazywamy tu niepusty ciąg znaków
// nie zawierający tzw. białych znaków, czyli spacji, tabulacji czy znaku nowej linii.

// Uwagi: Program nie korzysta z argumentów wywołania programu - nie można go wywołać jako
// program filtrujący. Na wyjsciu wyrazy nie zawsze są oddzielone pojedynczą spacją.

// Wyświetla x spacji, i zwraca x (czyli ilość spacji, jaką funkcja wyświetliła)
int wyswietl_spacje(int x) {
  for (int i=0;i<x;i++) {
    putchar(' ');
  }
  return x;
}

// Sprawdza czy znak jest biały (spacja, koniec linii, tabulator) lub jest końcem ciągu (znak 0)
bool czy_bialy(char x) {
  if (x == ' ' || x == 0 || x == '\n' || x == '\t') {
    return true;
  } else {
    return false;
  }
}

int main(void) {
  char line[1024];
  int n, m, i, line_length, dlugosc_wyrazu, poz_line, pozycja;
  
  do {
    printf("Podaj m: ");
    scanf("%d", &m);
  } while(m <= 0 || m >= 200);

  do {
    printf("Podaj n: ");
    scanf("%d", &n);
  } while(n <= m || n >= 200);
  
  const int szerokosc = n - m + 1;
  
  printf("Wprowadzaj tekst:\n");
  //getchar();
  
  pozycja = 1 + wyswietl_spacje(m-1);
  
  while (fgets(line, 1024, stdin) != NULL) {
    // Odjąć znak \n na końcu, jest nam niepotrzebny
    line_length = strlen(line) - 1;
    
    // poz_line reprezentuje gdzie jesteśmy w aktualnie wczytanej przez nas linijce
    poz_line = 0;
    while (poz_line < line_length) {
      // sprawdzamy długość najbliższego wyrazu
      dlugosc_wyrazu = 0;
      while (czy_bialy(line[poz_line+dlugosc_wyrazu]) == false) {
        dlugosc_wyrazu++;
      }
      
      if (dlugosc_wyrazu > szerokosc) {
        printf("\nJeden z wyrazów jest za długi. Koniec programu.\n");
        return 1;
      } else if (dlugosc_wyrazu > 0) {
        
        // Jeśli na ten wyraz nie ma już miejsca w tej linii, to zaczynamy nową
        if ((n-pozycja+1) < dlugosc_wyrazu) {
          putchar('\n');
          pozycja = 1 + wyswietl_spacje(m-1);
        }
        
        // Wyświetlanie wyrazu
        for (i=poz_line;i<(poz_line+dlugosc_wyrazu);i++) {
          putchar(line[i]);
        }
        
        // Aktualizacja pozycji i pozycji przetwarzanej linii
        pozycja += dlugosc_wyrazu;
        poz_line += dlugosc_wyrazu;
      }

      // Jeśli jeszcze nie kończymy linii, to wydrukujmy spację,
      // która oddzieli aktualny wyraz od nastęnego
      if (pozycja <= n) {
        putchar(' ');
        pozycja++;
      }
      poz_line++;
    }
  }
  return 0;
}
