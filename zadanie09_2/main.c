#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

// Napisać program, który pozwala porównywać zawartość dwóch wybranych plików tekstowych.
// Nazwy plików powinny być parametrami wywołania programu. Wynikiem porównania powinno
// być "Pliki są identyczne", "Pliki różnią się tylko białymi znakami" lub "Pliki różnią się treścią".
// W tym ostatnim przypadku program powinien wypisać zawartość pierwszych różnych wierszy
// i podać ich numer (liczony od 1).

// Uwagi: Zwracanie nan("empty") jako wartości typu char może dać niespodziewany wynik (gcc
// generuje kod, który zwraca 0). Użycie list do sprawdzenia, czy dwa teksty różnią się tylko
// białymi znakami nie jest efektywne.

int main(int argc, char *argv[]) {
  FILE * file1;
  FILE * file2;

  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");

  if (file1 == NULL) {
    printf("Pierwszy plik nie istnieje!\n");
    exit(1);
  }

  if (file2 == NULL) {
    printf("Drugi plik nie istnieje!\n");
    exit(2);
  }

  struct element * queue1 = list_init();
  struct element * queue2 = list_init();
  char chr1, chr2;

  int line = 1;
  char line1[1024];
  char line2[1024];
  int diff_line;
  char diff_line1[1024];
  char diff_line2[1024];

  int status = 0;
  // status = 0; takie same
  // status = 1; roznica na bialych znakach
  // status = 2; roznica w tresci

  while (status < 2 && (!feof(file1) || !feof(file2))) {
    fgets(line1, 1024, file1);
    fgets(line2, 1024, file2);

    // Jesli sie roznia znaki, to zapiszmy ta linie.
    // Pozniej, jesli okaze sie, ze pliki sie roznia nie tylko bialymi znakami,
    //   to te linie bedziemy musieli wyswietlic.
    if (!feof(file1) && !feof(file2) && strcmp(line1,line2) != 0 && status == 0) {
      status = 1;
      diff_line = line;
      strcpy(diff_line1, line1);
      strcpy(diff_line2, line2);
    }

    if (!feof(file1)) {
      for (int i=0;i<strlen(line1);i++) {
        if (!isspace(line1[i])) {
          queue1 = list_push(queue1, line1[i]);
        }
      }
    }

    if (!feof(file2)) {
      for (int i=0;i<strlen(line2);i++) {
        if (!isspace(line2[i])) {
          queue2 = list_push(queue2, line2[i]);
        }
      }
    }

    while (!is_empty(queue1) && !is_empty(queue2)) {
      chr1 = list_shift(&queue1);
      chr2 = list_shift(&queue2);
//      printf("---Wyciagam %c i %c\n", chr1, chr2);
      if (chr1 != chr2) {
        status = 2;
      }
    }

    // Nie musimy zliczac znakow nowej linii z obu plikow.
    // W miejscu, w ktorym sie roznia, na pewno maja ta sama linie.
    // Gdyby mialy inna linie, to to wtedy tak naprawde nie bylaby pierwsza roznica.
    line++;
  }

  if (!is_empty(queue1) || !is_empty(queue2)) {
    status = 2;
  }

  if (status == 0) {
    printf("Pliki sa identyczne.\n");
  } else if (status == 1) {
    printf("Pliki roznia sie tylko bialymi znakami.\n");
  } else if (status == 2) {
    printf("Pliki roznia sie trescia w %d linii.\n", diff_line);
    printf("Plik1: %s", diff_line1);
    printf("Plik2: %s", diff_line2);
  }

  return 0;
}

