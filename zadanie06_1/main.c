#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "queue.h"

// Kolejka to struktura, w której nowe elementy dopisywane są na końcu,
// a pobierane z niej elementy pochodzą z początku kolejki (podobnie jak w kolejce sklepowej).
// Do implementacji kolejki w tablicy potrzebne są dwa indeksy (lub wskaźniki) - jeden wskazujący
// początek kolejki, a drugi - jej koniec. Tablica powinna być wykorzystywana cyklicznie,
// jeśli na jej początku zwolni się miejsce. Zdefiniować strukturę reprezentującą kolejkę liczb typu
// double i funkcje: (1) opróżniania kolejki, (2) dopisywania liczby do kolejki, (3) pobierania
// liczby z kolejki, (4) sprawdzania, czy kolejka jest pusta. Utworzyć z nich moduł z odpowiednim
// plikiem nagłówkowym. Program główny powinien umożliwić testowanie operacji na kolejce.

int main() {
  struct Queue kolejka;
  queue_flush(&kolejka);
  double element = 3.0;
  int znak = 2;
  int stan;

  printf("-----------------------------------\n");
  printf("1. Oproznij kolejke (wyczysc)\n");
  printf("2. Dodaj element do kolejki\n");
  printf("3. Pobierz element z kolejki\n");
  printf("4. Pobierz i usun element z kolejki\n");
  printf("5. Sprawdz czy pusta\n");
  printf("6. Sprawdz czy pelna\n");
  printf("7. Wyswietl kolejke\n");
  printf("0. Wyjscie\n");
  printf("-----------------------------------\n\n");

  do {
    printf("Podaj opcje: ");
    stan = scanf("%d", &znak);

    if (znak == 1) {
      queue_flush(&kolejka);
    }

    if (znak == 2) {
      printf("Podaj element: ");
      stan = scanf("%lf", &element);
      if (queue_push(&kolejka, element) == false)
        printf("Kolejka pelna, nie udalo sie dodac elementu.\n");
    }

    if (znak == 3) {
      element = queue_fetch(&kolejka);
      if (isnan(element)) {
        printf("Brak elementow w kolejce.\n");
      } else {
        printf("Element pierwszy w kolejce: %lf\n", element);
      }
    }

    if (znak == 4) {
      element = queue_pop(&kolejka);
      if (isnan(element)) {
        printf("Brak elementow w kolejce.\n");
      } else {
        printf("Element pierwszy z kolejki: %lf zostal usuniety\n", element);
      }
    }

    if (znak == 5) {
      if (queue_if_empty(&kolejka)) {
        printf("Kolejka jest pusta.\n");
      } else {
        printf("Kolejka nie jest pusta.\n");
      }
    }

    if (znak == 6) {
      if (queue_if_full(&kolejka)) {
        printf("Kolejka jest pełna.\n");
      } else {
        printf("Kolejka nie jest pełna.\n");
      }
    }

    if (znak == 7) {
      printf("Kolejka: ");
      queue_display(&kolejka);
      printf("\n");
    }
  } while (znak != 0);
  return 0;
}
