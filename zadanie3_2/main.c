#include <stdio.h>

// Napisać program, który sprawdza, czy w tekście zadanym na standardowym wejściu poprawnie
// zostały rozstawione nawiasy '(', ')', '[' i ']'. Na wyjściu należy wypisać
// pozycje (numery wierszy i kolumn liczonych od 1) niesparowanych nawiasów. Użyć funkcji
// rekurencyjnej do szukania pasującego nawiasu zamykającego.

int sprawdzanie_znaku(int znak);
int szukaj_nawiasu(char poszukiwany);

// Zmienne globalne
int wiersz, kolumna;

int main() {
  wiersz = 1;
  kolumna = 0;
  int znak;

  while ((znak = getchar()) != EOF) {
    kolumna++;
    if (sprawdzanie_znaku(znak) == 1) break;
  }
  return 0;
}

int sprawdzanie_znaku(int znak) {
  // jesli zwraca 1 - przerwij petle, bo dostales EOF z zagniezdzonej funkcji rekurencyjnej
  // jesli jest to jedna z opcji szukaj_nawiasu, to zwroc to co ona zwroci - jesli ona zwrocila 1, znaczy, ze dostala EOF
  // w pozostalych przypadkach zwroc 0

  if (znak == '\n') {
    wiersz++;
    kolumna = 0;
  } else if (znak == '(') {
    return szukaj_nawiasu(')');
  } else if (znak == '[') {
    return szukaj_nawiasu(']');
  } else if (znak == ')') {
    printf("\nNadmiarowy nawias ')'.");
  } else if (znak == ']') {
    printf("\nNadmiarowy nawias ']'.");
  }
  return 0;
}

int szukaj_nawiasu(char poszukiwany) {
  // funkcja szukania nawiasu. jesli znajdzie, to zwraca 0, czyli wszystko ok.
  // jesli nie znajdzie, wyswietla komunikat i zwraca 1 - zeby wyjsc z nadrzednych petli, bo juz tutaj dostalismy EOF

  int znak;
  int pochodzenie_kolumna = kolumna;
  int pochodzenie_wiersz = wiersz;

  while ((znak = getchar()) != EOF) {
    kolumna++;

    if (znak == poszukiwany) return 0;
    if (sprawdzanie_znaku(znak) == 1) break;
  }

  printf("\nBrak nawiasu zamykajacego '%c' dla nawiasu w wierszu %d i kolumnie %d.", poszukiwany, pochodzenie_wiersz, pochodzenie_kolumna);
  return 1;
}
