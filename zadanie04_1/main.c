#include <stdio.h>
#include "zbiory.h"

// Zbiór liczb całkowitych może być zapisany w tablicy o elementach typu int,
// gdzie elementy zbioru5 są posortowane rosnąco, a na początku tablicy zapisana
// jest liczba jego elementów. Zdefiniować za pomocą typedef nowy typ reprezentujący
// takie zbiory. Następnie zdefiniować dla tego typu operacje: sumy zbiorów, przekroju
// zbiorów, czyszczenia zbioru oraz dodawania do zbioru i usuwania ze zbioru pojedyńczego
// elementu. Zadbać o to, aby liczba operacji, którą wykonują te funkcje była proporcjonalna
// do wielkości tych zbiorów. Sformułować z nich moduł i stworzyć plik nagłówkowy.
// Następnie napisać drugi moduł zawierający program testujący poprawność zdefiniowanych funkcji.

void wyswietl_zbior(ZBIOR zbior) {
  for (int i=1;i<=zbior[0];i++)
    printf(" %d", zbior[i]);
}

int main() {
  ELEMENT e;
  int opcja;
  ZBIOR zbior1, zbior2, zbior3;
  printf("Zbiory podajemy w formacie n x1 x2 x3 ... xn\n");
  printf("gdzie n to liczba elementow, a x1, x2, ... xn to elementy zbioru.\n");

  printf("Podaj 1 zbior: ");
  scanf("%d", &zbior1[0]);
  for (int i=1;i<=zbior1[0];i++) {
    scanf("%d", &zbior1[i]);
  }

  printf("Podaj 2 zbior: ");
  scanf("%d", &zbior2[0]);
  for (int i=1;i<=zbior2[0];i++) {
    scanf("%d", &zbior2[i]);
  }

  printf("Podaj 3 zbior: ");
  scanf("%d", &zbior3[0]);
  for (int i=1;i<=zbior3[0];i++) {
    scanf("%d", &zbior3[i]);
  }

  printf("\n---------------------------------------\n");
  printf("0 -> Wyjście\n");
  printf("1 -> Suma zbiorow zbior1 i zbior2\n");
  printf("2 -> Przekroj zbiorow zbior1 i zbior2\n");
  printf("3 -> Czyszczenie zbioru zbior1\n");
  printf("4 -> Dodawanie elementu do zbioru zbior1\n");
  printf("5 -> Usuwanie elementu ze zbioru zbior1\n");
  do {
    printf("\nPodaj opcje: ");
    scanf("%d", &opcja);

    switch(opcja) {
      case 1:
        suma_zbiorow(zbior1, zbior2, zbior3);
        printf("Zbior3:");
        wyswietl_zbior(zbior3);
        break;
      case 2:
        przekroj_zbiorow(zbior1, zbior2, zbior3);
        printf("Zbior3:");
        wyswietl_zbior(zbior3);
        break;
      case 3:
        czyszczenie_zbioru(zbior1);
        printf("Zbior1:");
        wyswietl_zbior(zbior1);
        break;
      case 4:
        printf("Podaj element: ");
        scanf("%d", &e);
        dodaj_element(zbior1, e);
        printf("Zbior1:");
        wyswietl_zbior(zbior1);
        break;
      case 5:
        printf("Podaj element: ");
        scanf("%d", &e);
        usun_element(zbior1, e);
        printf("Zbior1:");
        wyswietl_zbior(zbior1);
        break;
      default:
        break;
    }
  } while (opcja != 0);
  return 0;
}
