#include <stdio.h>
#include <stdlib.h>
#include "wllc.h"

// Wielopoziomową listę liczb całkowitych (w skrócie WLLC) definiujemy jako
// skończony (w tym także pusty) ciąg, którego elementami są liczby całkowite lub WLLC.
// Jeśli lista zawiera tylko liczby to nazywamy ją jednopoziomową. Przykłady: L1 = [3,1,5];
// L2 = [2,[4,7],[]] oraz L3 = [[[3],[5,8],2],[1,5]]. Lista L1 jest jednopoziomowa.
// Zdefiniować moduł WLLC, w którym:
//   a) Za pomocą typedef zdefiniowany jest typ reprezentujący WLLC.
//   b) Zdefiniowana jest funkcja WLLC merge(WLLC l1, WLLC l2),
//       która zwraca listę powstałą z dołączenia listy l2 na końcu listy l1.
//   c) Zdefiniowana jest funkcja WLLC flat(WLLC li), która tworzy nową listę
//       jednopoziomową zawierającą wszystkie liczby z listy li z zachowaniem ich kolejności.

int main() {
  LElement * list1;
  LElement * list2;
  LElement * list3;
  LElement * list4;

  // Lista 1
  list1 = list_init();
  list1 = list_push_value(list1, 3);
  list1 = list_push_value(list1, 1);
  list1 = list_push_value(list1, 5);

  // Lista 2
  list2 = list_init();
  list2 = list_push_value(list2, 2);
  list2 = list_push_list(list2);
  list2->sublist = list_push_value(list2->sublist, 4);
  list2->sublist = list_push_value(list2->sublist, 7);
  list2 = list_push_list(list2);

  // Lista 3
  list3 = list_init();
  list3 = list_push_list(list3);
  list3->sublist = list_push_list(list3->sublist);
  list3->sublist->sublist = list_push_value(list3->sublist->sublist, 3);
  list3->sublist = list_push_list(list3->sublist);
  list3->sublist->sublist = list_push_value(list3->sublist->sublist, 5);
  list3->sublist->sublist = list_push_value(list3->sublist->sublist, 8);
  list3->sublist = list_push_value(list3->sublist, 2);
  list3 = list_push_list(list3);
  list3->sublist = list_push_value(list3->sublist, 1);
  list3->sublist = list_push_value(list3->sublist, 5);

  list1 = list_merge(list2, list1);
  list4 = list_flat(list3);

  printf("PO POLACZENIU:\n");
  status(list1);

  printf("LISTA 4 - JEDNOPOZIOMOWA:\n");
  status(list4);

  printf("LISTA 3 - WIELOPOZIOMOWA, ZRODLO LISTA 4, NIEZMIENIONE:\n");
  status(list3);

  return 0;
}
