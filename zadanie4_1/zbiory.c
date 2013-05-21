#include "zbiory.h"

// Suma zbiorow, dzialanie podobne do merge sort
void suma_zbiorow(const ZBIOR zbior1, const ZBIOR zbior2, ZBIOR wynik) {
  int i1, i2, iw;
  i1 = i2 = iw = 1;
  wynik[0] = 0;

  while (i1 <= zbior1[0] || i2 <= zbior2[0]) {
    // Jesli jeszcze nie przejrzelismy zadnego zbioru
    if (i1 <= zbior1[0] && i2 <= zbior2[0]) {
      // Jesli element ze zbioru 1 jest mniejszy lub elementy sa rowne, to go dodajemy
      if (zbior1[i1] <= zbior2[i2]) {
        // ale tylko wtedy, jesli go jeszcze nie ma
        if (iw <= 1 || zbior1[i1] != wynik[iw-1]) {
          wynik[iw] = zbior1[i1];
          iw++;
          wynik[0]++;
        }
        i1++;
      // Analogiczna sytuacja, ale jesli element 2 jest mniejszy
      } else {
        if (iw <= 1 || zbior2[i2] != wynik[iw-1]) {
          wynik[iw] = zbior2[i2];
          iw++;
          wynik[0]++;
        }
        i2++;
      }
    // Dodawanie reszty elementow ze zbior1
    } else if (i1 <= zbior1[0]) {
      if (iw <= 1 || zbior1[i1] != wynik[iw-1]) {
        wynik[iw] = zbior1[i1];
        iw++;
        wynik[0]++;
      }
      i1++;
    // Dodawanie reszty elementow ze zbior2
    } else if (i2 <= zbior2[0]) {
      if (iw <= 1 || zbior2[i2] != wynik[iw-1]) {
        wynik[iw] = zbior2[i2];
        iw++;
        wynik[0]++;
      }
      i2++;
    }
  }
}

void czyszczenie_zbioru(ZBIOR wynik) {
  wynik[0] = 0;
}

void dodaj_element(ZBIOR wynik, ELEMENT e) {
  int i = 1;
  while (i <= wynik[0]) {
    if (e <= wynik[i])
      break;
    i++;
  }

  // jeśli ten element jest już w zbiorze, to nie trzeba go dodawać
  // jesli zbior jest pusty, to tez dodajemy
  //      (bez tego wystepowal blad, jesli poprzednio na 1 pozycji byla jakas liczba,
  //      np. 3, i teraz tez probujemy dodac 3, to wtedy e == wynik[1])
  if (e != wynik[i] || i > wynik[0]) {
    wynik[0]++;
    for (int k=wynik[0];k>i;k--) {
      wynik[k] = wynik[k-1];
    }

    wynik[i] = e;
  }
}

void usun_element(ZBIOR wynik, ELEMENT e) {
  int i = 1;
  while (i <= wynik[0]) {
    if (e == wynik[i])
      break;
    i++;
  }

  // jesli znaleziono
  if (i <= wynik[0]) {
    wynik[0]--;
    for (;i<=wynik[0];i++)
      wynik[i] = wynik[i+1];
  }
}

void przekroj_zbiorow(const ZBIOR zbior1, const ZBIOR zbior2, ZBIOR wynik) {
  int i1, i2;
  i1 = i2 = 1;
  wynik[0] = 0;

  while (i1 <= zbior1[0] && i2 <= zbior2[0]) {
    if (zbior1[i1] == zbior2[i2]) {
      wynik[0]++;
      wynik[wynik[0]] = zbior1[i1];
      i1++;
      i2++;
    } else if (zbior1[i1] < zbior2[i2]) {
      i1++;
    } else {
      i2++;
    }
  }
}
