#include <stdio.h>

// Napisać program, który zamienia w tekście ze standardowego wejścia polskie litery
// w standardzie ISO-8859-2 na WINDOWS-1250.
// Przetworzony tekst należy wypisać na standardowym wyjściu.

int main(void) {
  int znak;

  while ((znak=getchar()) != EOF) {
    if (znak == 161) znak = 165; // Ą
    else if (znak == 166) znak = 140; // Ś
    else if (znak == 172) znak = 143; // Ź
    else if (znak == 177) znak = 185; // ą
    else if (znak == 182) znak = 156; // ś
    else if (znak == 188) znak = 159; // ź
    putchar(znak);
  }
  return 0;
}
