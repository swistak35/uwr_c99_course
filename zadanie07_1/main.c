#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "list.h"

// Zdefiniować moduł służący do obsługi cyklicznych list jednostronnych zawierających wartości
// typu double. Moduł powinien udostępniać następujące operacje: (1) utwórz i zwróć wskaźnik
// na listę pustą, (2) dodaj wartość na początek wskazanej listy, (3) dodaj wartość na koniec
// wskazanej listy, (4) usuń i zwróć wartość z początku listy, (5) podaj wartość z początku listy,
// (6) sprawdź czy lista jest pusta, (7) połącz dwie wskazane listy, (8) skopiuj wskazaną listę,
// (9) podaj długość wskazanej listy oraz (10) wstaw wartość na właściwe miejsce w uporządkowanej
// liście wartości. Pamięć dla elementów listy powinna być przydzielana i zwalniana dynamicznie za
// pomocą standardowych procedur malloc i free z biblioteki stdlib. Lista reprezentowana jest przez
// wskaźnik na jej ostatni element (dla listy pustej ten wskaźnik ma wartość NULL).

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

int main() {
  struct element * moja_lista;
  struct element * moja_lista2;
  struct element * moja_lista3;
  moja_lista = list_init();

  moja_lista = list_unshift(moja_lista, 3.0);
  wyswietl_liste(moja_lista);

  moja_lista = list_unshift(moja_lista, 1.0);
  wyswietl_liste(moja_lista);

  moja_lista = list_push(moja_lista, 7.0);
  wyswietl_liste(moja_lista);

  printf("Wyswietlam element %lf\n", list_fetch_first(moja_lista));
  wyswietl_liste(moja_lista);

  printf("Usuwam element %lf\n", list_shift(moja_lista));
  wyswietl_liste(moja_lista);

  moja_lista2 = list_copy(moja_lista);
  wyswietl_liste(moja_lista2);

  moja_lista3 = list_join(moja_lista, moja_lista2);
  wyswietl_liste(moja_lista3);
  printf("Liczba elementow w moja_lista3: %d\n", list_count(moja_lista3));

  moja_lista = list_push(moja_lista, 9.0);
  moja_lista = list_push(moja_lista, 13.0);
  moja_lista = list_push(moja_lista, 19.0);
  moja_lista = list_push(moja_lista, 22.0);
  wyswietl_liste(moja_lista);

  list_add_in_order(moja_lista, 1.0);
  wyswietl_liste(moja_lista);

  return 0;
}
