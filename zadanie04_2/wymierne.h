#include <math.h>
#include <stdio.h>

#define MOVE_BITS 32

typedef long long int wymierna;
typedef long int liczba;
// definiuje liczbe, poniewaz czesto bede uzywal jako long int licznika lub mianownika
// nazwa niefortunna, ale nie moglem wymyslec nic lepszego, co by laczylo licznik i mianownik

// Matematyczne funkcje pomocnicze
long long int abs(long long int x);
long long int nwd(long long int x, long long int y);
long long int nww(long long int x, long long int y);

// Inne funkcje pomocnicze
liczba licznik(wymierna x);
liczba mianownik(wymierna x);
wymierna konwertuj(liczba licznikx, liczba mianownikx);

// Wlasciwe funkcje w zadaniu
void wypisz(wymierna x);
wymierna wczytaj();
wymierna suma(wymierna x, wymierna y);
wymierna roznica(wymierna x, wymierna y);
wymierna iloczyn(wymierna x, wymierna y);
wymierna iloraz(wymierna x, wymierna y);
