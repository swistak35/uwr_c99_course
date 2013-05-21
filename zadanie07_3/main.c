#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "kolejka.h"

// Kolejka dwustronna to struktura, w której elementy mogą być dopisywane i pobierane z obu stron.
// Do implementacji takiej kolejki jako struktury łączonej na stercie potrzebne są w każdym
// elemencie dwa wskaźniki - jeden na element poprzedni, a drugi na element następny. Głowa kolejki
// powinna zawierać dwa wskaźniki: na pierwszy i na ostatni element kolejki. Zdefiniować strukturę
// reprezentującą kolejkę liczb typu double i funkcje: (1) opróżniania kolejki, (2) dopisywania
// liczby do kolejki z przodu, (3) dopisywanie liczby do kolejki z tyłu, (4) pobierania liczby
// z kolejki z przodu, (5) pobierania liczby z kolejki z tyłu oraz (6) sprawdzania, czy kolejka
// jest pusta. Wskaźnik na strukturę reprezentującą kolejkę (głowę kolejki) powinien być pierwszym
// parametrem wszystkich tych operacji. Utworzyć z nich moduł z odpowiednim plikiem nagłówkowym.
// Program główny powinien umożliwić testowanie operacji na kolejce.

// Funkcja malloc nie zeruje zwracanej pamięci, a Pana kod zakłada, że po przydzieleniu pamięci
// wskaźniki są automatycznie ustawiane na NULL (poza tym standard C nie określa wartości NULL jako zera).

void wyswietl_kolejke(Queue * my_queue);
void status(Queue * my_queue);

int main() {
  int wybor;
  double element;
  Queue * kolejka;

  if (!queue_init(&kolejka)) {
    printf("Nie udało się utworzyć kolejki.\n");
    exit(1);
  }

  printf("---------------\n");
  printf("0. Wyjście\n");
  printf("1. Wyświetl kolejkę\n");
  printf("2. Dodaj element na początek\n");
  printf("3. Dodaj element na koniec\n");
  printf("4. Wyświetl pierwszy element\n");
  printf("5. Wyświetl ostatni element\n");
  printf("6. Wyświetl i usuń pierwszy element\n");
  printf("7. Wyświetl i usuń ostatni element\n");
  printf("8. Opróżnij kolejkę\n");
  printf("9. Sprawdź czy kolejka jest pusta\n");
  printf("10. Wyświetl info do debugowania\n");

  do {
    printf("Wybor: ");
    scanf("%d", &wybor);

    switch (wybor) {
      case 0:
        break;
      case 1:
        wyswietl_kolejke(kolejka);
        break;
      case 2:
        printf("Podaj element: ");
        scanf("%lf", &element);
        if (!queue_unshift(kolejka, element))
          printf("Nie udało się dodać elementu do kolejki.\n");
        break;
      case 3:
        printf("Podaj element: ");
        scanf("%lf", &element);
        if (!queue_push(kolejka, element))
          printf("Nie udało się dodać elementu do kolejki.\n");
        break;
      case 4:
        element = queue_fetch_first(kolejka);
        if (!isnan(element))
          printf("Pierwszy element: %lf\n", element);
        else
          printf("Nie udało się pobrać elementu, ponieważ kolejka jest pusta\n");
        break;
      case 5:
        element = queue_fetch_last(kolejka);
        if (!isnan(element))
          printf("Ostatni element: %lf\n", element);
        else
          printf("Nie udało się pobrać elementu, ponieważ kolejka jest pusta\n");
        break;
      case 6:
        element = queue_shift(kolejka);
        if (!isnan(element))
          printf("Pierwszy element: %lf\n", element);
        else
          printf("Nie udało się pobrać elementu, ponieważ kolejka jest pusta\n");
        break;
      case 7:
        element = queue_pop(kolejka);
        if (!isnan(element))
          printf("Ostatni element: %lf\n", element);
        else
          printf("Nie udało się pobrać elementu, ponieważ kolejka jest pusta\n");
        break;
      case 8:
        queue_purge(kolejka);
        printf("Kolejka wyczyszczona\n");
        break;
      case 9:
        if (queue_isempty(kolejka))
          printf("Kolejka jest pusta\n");
        else
          printf("Kolejka nie jest pusta\n");
        break;
      case 10:
        status(kolejka);
        break;
      default:
        printf("Nieprawidłowa opcja!\n");
    }
  } while (wybor != 0);

  return 0;
}

void wyswietl_kolejke(Queue * my_queue) {
  QElement * element;

  if (queue_isempty(my_queue)) {
    printf("Kolejka: jest pusta!\n");
  } else {
    printf("Kolejka:");

    element = my_queue->begin;
    do {
      printf("  %lf", element->value);
      if (element == my_queue->end) break;
      element = element->next;
    } while (true);

    printf("\n");
  }
}


void status(Queue * my_queue) {
  QElement * element;

  printf("------------------\n");
  printf("Wskaźnik kolejki: %p\n", my_queue);
  printf("Kolejka->begin: %p\n", my_queue->begin);
  printf("Kolejka->end: %p\n", my_queue->end);

  if (!queue_isempty(my_queue)) {
    printf("Kolejka: \n");

    element = my_queue->begin;
    do {
      printf("  * [prev: %p] [valu: %lf] [next: %p] [addr: %p]\n", element->previous, element->value, element->next, element);
      if (element == my_queue->end) break;
      element = element->next;
    } while (true);

    printf("\n");
  }
}
