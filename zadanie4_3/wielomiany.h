#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "wymierne.h"

// Pierwsze 2001 pól jest do trzymania współczynników.
//  co prawda n <= 1000, ale możemy otrzymać też większy wielomian przy mnożeniu
//  np. x^1000 * x^1000 = x^2000
// Ostatnie pole wielomianu (x[2001]) przechowuje "n", czyli stopień wielomianu.
//   Uwaga! Stopień wielomianu interpretuję jak zwykłego inta, nie jak mój zdefiniowany typ liczby "wymierna".
# define STOPIEN 2001
// STOPIEN przechowuje nr indeksu, gdzie jest stopien wielomianu
typedef wymierna wielomian[STOPIEN+1];

int dodawanie(wielomian w1, wielomian w2, wielomian wout);
int odejmowanie(wielomian w1, wielomian w2, wielomian wout);
int mnozenie(wielomian w1, wielomian w2, wielomian wout);
int dzielenie(wielomian w1, wielomian w2, wielomian wout, wielomian wr);
wymierna obliczanie_wartosci(wielomian w, wymierna x);

void czyszczenie_zer(wielomian w);
void wyswietl_wielomian(wielomian w);
void wczytaj_wielomian(wielomian w);
