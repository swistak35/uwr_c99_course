#include "wymierne.h"

// Zwraca wartość bezwzględną z liczby wymiernej
// Działa, ponieważ w naszej liczbie również bit znaku, to bit pierwszy
long long int abs(long long int x) {
    if (licznik(x) < 0)
        return -x;
    else
        return x;
}

// Iteracyjny algorytm euklidesa
long long int nwd(long long int x, long long int y) {
    long long int tmp;

    while (y != 0) {
        tmp = x % y;
        x = y;
        y = tmp;
    }

    return x;
}

// Korzystamy ze wzory, że NWW(a,b) = a * b / NWD(a,b)
long long int nww(long long int x, long long int y) {
    long long int dzielnik = nwd(x, y);
    return (x / dzielnik) * y;
}

// Przesuwamy pierwsza polowe bitow do prawej, lewa strona wypelnia sie zerami
liczba licznik(wymierna x) {
    return (x >> MOVE_BITS);
}

// Najpierw usuwamy licznik z liczby, przesuwajac mianownik o polowe w prawo,
// potem wracamy z powrotem na swoje miejsce, ale zamiast licznika mamy juz same zera
liczba mianownik(wymierna x) {
    return ((x << MOVE_BITS) >> MOVE_BITS);
}

// Utworzenie liczby wymiernej na podstawie licznika i mianownika
wymierna konwertuj(liczba licznikx, liczba mianownikx) {
    return ((licznikx << MOVE_BITS) + mianownikx);
}

// Wyswietlanie liczby wymiernej
void wypisz(wymierna x) {
    printf("%ld/%ld", licznik(x), mianownik(x));
}

// Wczytywanie liczby wymiernej
wymierna wczytaj() {
    liczba licznikx, mianownikx;

    do {
        scanf("%ld/%ld", &licznikx, &mianownikx);
        if (mianownikx == 0)
            printf("Mianownik nie może być zerem! Sprobuj jeszcze raz.\n");
    } while (mianownikx == 0);

    return konwertuj(licznikx, mianownikx);
}

// Suma dwoch ulamkow
wymierna suma(wymierna x, wymierna y) {
    // dlaczego w liczniku i mianowniku nie uzylem typu 'liczba'? Poniewaz przyda sie tutaj wiekszy zakres,
    //   bo jesli wspolny mianownik zajmuje 32 bity, to moze
    //   skroci sie z licznikiem i jednak zmiesci sie w tych 32 bitach

    // Mianownik wyliczamy z NWW
    long long int mianownikz = nww((long long int) mianownik(x), (long long int) mianownik(y));

    // Obliczamy licznik
    long long int licznikz = licznik(x) * (mianownikz / mianownik(x)) + licznik(y) * (mianownikz / mianownik(y));

    // Sprawdzamy czy abs(licznik) i mianownik maja wspolny dzielnik
    long long int wspolny_dzielnik = nwd((long long int) abs(licznikz), (long long int) mianownikz);

    // I skracamy - jesli liczby sa wzglednie pierwsze, to wspolny_dzielnik = 1
    mianownikz /= wspolny_dzielnik;
    licznikz /= wspolny_dzielnik;

    // Zwroc gotowy ulamek
    return konwertuj((long int) licznikz, (long int) mianownikz);
}

// Algorytm na roznice jest taki, że x - y = x + (-y)
wymierna roznica(wymierna x, wymierna y) {
    wymierna minus_y = konwertuj(-licznik(y), mianownik(y));
    return suma(x, minus_y);
}

//
wymierna iloczyn(wymierna x, wymierna y) {
    // Wymnazamy licznik i mianownik
    long long int mianownikz = (long long int)mianownik(x) * (long long int)mianownik(y);
    long long int licznikz = (long long int)licznik(x) * (long long int)licznik(y);

    // Obliczamy wspolny_dzielnik, moze cos skrocimy
    long long int wspolny_dzielnik = nwd((long long int) abs(licznikz), (long long int) mianownikz);

    // Skracamy
    mianownikz /= wspolny_dzielnik;
    licznikz /= wspolny_dzielnik;

    return konwertuj((long int) licznikz, (long int) mianownikz);
}

// W ilorazie korzystamy z tego, ze x/y = x * (1/y)
wymierna iloraz(wymierna x, wymierna y) {
    wymierna odwrotnosc_y;

    // Oczywiscie musimy pamietac, ze jesli ulamek jest ujemny, to minus ma byc w liczniku
    if (licznik(y) < 0) {
        odwrotnosc_y = konwertuj(-mianownik(y), -licznik(y));
    } else if (licznik(y) > 0) {
        odwrotnosc_y = konwertuj(mianownik(y), licznik(y));
    } else {
        // Nie mozemy dzielic przez zero
        printf("Nie mozna dzielic przez 0!\n");
        return 0;
    }
    return iloczyn(x, odwrotnosc_y);
}
