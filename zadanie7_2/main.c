#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "list.h"

// Używając modułu z pierwszego zadania zaprogramować wersje algorytmów quicksort i sortowania
// przez wstawianie na listach zawierających wartości typu double. Parametrem obu procedur będzie
// tylko lista. W algorytmie quicksort jako element dzielący należy wziąć pierwszy element
// listy i rozdzielić dalszą część tej listy na dwie części: jedną zawierającą elementy <=,
// a drugą zawierającą elementy >. Te części należy posortować rekurencyjnie.

void status(struct element * list);
struct element * quick_sort(struct element ** list_ptr);
struct element * insertion_sort(struct element ** list_ptr);
void wyswietl_liste(struct element * list);

int main() {
  struct element * moja_lista;
  struct element * moja_lista2;

  moja_lista = list_init();

  moja_lista = list_push(moja_lista, 3.0);
  moja_lista = list_push(moja_lista, 1.0);
  moja_lista = list_push(moja_lista, 5.0);
  moja_lista = list_push(moja_lista, 3.0);
  moja_lista = list_push(moja_lista, 7.0);
  moja_lista = list_push(moja_lista, 2.0);
  moja_lista = list_push(moja_lista, 9.0);
  moja_lista = list_push(moja_lista, 6.0);

  moja_lista2 = list_copy(moja_lista);

  // Zamiast "wyświetl listę" można użyć "status" - jest to funkcja, która wyświetla listę
  //   w sposób bardziej przystępny do debugowania programu (lub do sprawdzania jak działa)
  printf("DANIE NIEPOSORTOWANE:\n");
  wyswietl_liste(moja_lista);

  printf("SORTOWANIE QUICK_SORT:\n");
  quick_sort(&moja_lista);
  wyswietl_liste(moja_lista);

  printf("SORTOWANIE INSERTION_SORT:\n");
  insertion_sort(&moja_lista);
  wyswietl_liste(moja_lista);

  return 0;
}

void wyswietl_liste(struct element * list) {
  struct element * next_element;

  printf("Lista: ");
  next_element = list;
  do {
    next_element = next_element->pointer;
    printf(" %lf", next_element->value);
  } while (next_element != list);
  printf("\n");
}

void status(struct element * list) {
  printf("------------\n");
  printf("Lista: %p\n");

  struct element * next_element;
  if (is_empty(list)) {
    printf("Lista pusta\n");
  } else {
    next_element = list;
    do {
      next_element = next_element->pointer;
      printf("   * [value: %lf] [next: %p] [addr: %p]\n", next_element->value, next_element->pointer, next_element);
    } while (next_element != list);
    printf("\n");
  }
}

struct element * insertion_sort(struct element ** list_ptr) {
    struct element * list = *list_ptr;
    struct element * new_list;

    new_list = list_init();
    double temp_value;

    while (!is_empty(list)) {
      temp_value = list_shift(&list);
      new_list = list_add_in_order(new_list, temp_value);
    }
    *list_ptr = new_list;
    return new_list;
}

struct element * quick_sort(struct element ** list_ptr) {
  struct element * list = *list_ptr;

  if (!is_empty(list) && list->pointer != list) {
    struct element * list_low = list_init();
    struct element * list_high = list_init();

    double pivot = list_shift(&list);
    double temp;

    while (!is_empty(list)) {
      temp = list_shift(&list);
      if (temp > pivot)
        list_high = list_push(list_high, temp);
      else
        list_low = list_push(list_low, temp);
    }

    quick_sort(&list_low);
    quick_sort(&list_high);

    list_low = list_push(list_low, pivot);
    list = list_join(list_low, list_high);
  }

  *list_ptr = list;

  return list;
}
