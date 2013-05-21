#include "wielomiany.h"

// Ta funkcja usuwa zera wiodace w wielomianie, tzn. konwertuje np.
// (0*x^4 + 0*x^3 + 2*x^2 + 5) do postaci (2*x^2 + 5)
void czyszczenie_zer(wielomian w) {
  while (true) {
    if (czy_zero(w[w[STOPIEN]]))
      w[STOPIEN]--;
    else
      break;
  }
}

// Wczytywanie wspolczynnikow wielomianu
void wczytaj_wielomian(wielomian w) {
  scanf("%lld", &w[STOPIEN]);
  for (int i=0;i<=w[STOPIEN];i++)
    w[i] = wczytaj();
}

// Wyswietlanie stopnia i wspolczynnikow wielomianu
void wyswietl_wielomian(wielomian w) {
  printf("%lld", w[STOPIEN]);
  for (int i=0;i<=w[STOPIEN];i++) {
    printf(" ");
    wypisz(w[i]);
  }
  printf("\n");
}

// Operacja dodawania. Stopniem wynikowego wielomianu bedzie wiekszy ze stopni
//   wejsciowych. Potem iterujemy po wszystkich potegach i sumujemy wspolczynniki.
int dodawanie(wielomian w1, wielomian w2, wielomian wout) {
  if (w1[STOPIEN] > w2[STOPIEN])
    wout[STOPIEN] = w1[STOPIEN];
  else
    wout[STOPIEN] = w2[STOPIEN];

  for (int i=0;i<=wout[STOPIEN];i++) {
    wout[i] = wymierna_zero();
    if (w1[STOPIEN] >= i)
      wout[i] = suma(wout[i], w1[i]);
    if (w2[STOPIEN] >= i)
      wout[i] = suma(wout[i], w2[i]);
  }
  return 0;
}


// Tutaj rowniez stopniem wielomianu jest wiekszy z wejsciowych. Oczywiscie moze
//   sie zdarzyc, ze najwyzsza potega wielomianu sie zredukuje - za czyszczenie
//   niepotrzebnych zer z lewej strony wielomianu odpowiada funkcja czyszczenie_zer
//   wywoływana w main().
int odejmowanie(wielomian w1, wielomian w2, wielomian wout) {
  if (w1[STOPIEN] > w2[STOPIEN])
    wout[STOPIEN] = w1[STOPIEN];
  else
    wout[STOPIEN] = w2[STOPIEN];

  for (int i=0;i<=wout[STOPIEN];i++) {
    if (w1[STOPIEN] >= i && w2[STOPIEN] >= i)
      wout[i] = roznica(w1[i], w2[i]);
    else if (w1[STOPIEN] >= i)
      wout[i] = w1[i];
    else
      wout[i] = roznica(wymierna_zero(), w2[i]);
  }
  return 0;
}

// Mnozenie wielomianów na zasadzie "kazdy z kazdym" i dodanie wartosci w odpowiednie
//   miejsce w tablicy (poczatkowo wypełniona zerami). Stopien wielomianu to suma
//   stopni wielomianow wejsciowych.
int mnozenie(wielomian w1, wielomian w2, wielomian wout) {
  int potega;
  wymierna wspolczynnik;
  wout[STOPIEN] = w1[STOPIEN] + w2[STOPIEN];

  for (int i=0;i<=wout[STOPIEN];i++)
    wout[i] = wymierna_zero();

  for (int i=0;i<=w1[STOPIEN];i++) {
    for (int j=0;j<=w2[STOPIEN];j++) {
      wspolczynnik = iloczyn(w1[i], w2[j]);
      potega = i + j;
      wout[potega] = suma(wout[potega], wspolczynnik);
    }
  }
  return 0;
}

// Dzielenie wielomianów wg schematu dzielenia pisemnego
// Da się nietrudno przerobić na formę rekurencyjną, jednak zrezygnowałem z tego
// ze względów wydajnościowych - za każdym razem trzeba by tworzyć nowy wielomian
// pomocniczy.
int dzielenie(wielomian w1, wielomian w2, wielomian wout, wielomian wr) {
  // Sprawdzamy czy nie dzielimy przez wielomian zerowy, jesli tak to blad
  if (w2[STOPIEN] == 0 && w2[0] == 0)
    return 1;

  // Obliczamy jaki bedzie stopien wynikowego wielomianu
  wout[STOPIEN] = w1[STOPIEN] - w2[STOPIEN];
  wr[STOPIEN] = w1[STOPIEN];

  // Kopiowanie w1 do wr. Konieczne, żeby nie zniszczyć w1.
  for (int i=0;i<=w1[STOPIEN];i++)
    wr[i] = w1[i];

  // Dzielenie wykonujemy dopoki nie zostanie nam reszta o stopniu mniejszym niz dzielnik
  while (w2[STOPIEN] <= wr[STOPIEN]) {
    dzielenie_w_petli(wr, w2, wout);
    czyszczenie_zer(wr);
  }
  return 0;
}

int dzielenie_w_petli(wielomian wr, wielomian w2, wielomian wout) {
  int potega = wr[STOPIEN] - w2[STOPIEN];
  wymierna wspolczynnik = iloraz(wr[wr[STOPIEN]], w2[w2[STOPIEN]]);

  // Przypisanie wyliczonej wartosci do wyjsciowego wielomianu
  wout[potega] = wspolczynnik;

  // Definicja wielomianu pomocniczego:
  //   Jest to iloczyn wielomianu 2 (dzielnika) i elementu, który ostatnio
  //   wymnożyliśmy i wstawiliśmy do wielomianu wynikowego.
  wielomian pomocniczy;
  pomocniczy[STOPIEN] = wr[STOPIEN];

  for (int i=0;i<=pomocniczy[STOPIEN];i++)
    pomocniczy[i] = wymierna_zero();

  for (int i=w2[STOPIEN];i>=0;i--)
    pomocniczy[(i+potega)] = iloczyn(wspolczynnik, w2[i]);

  // Odejmujemy od wielomianu głównego wielomian pomocniczy - da nam to nowy wielomian główny.
  odejmowanie(wr, pomocniczy, wr);
  return 0;
}

wymierna obliczanie_wartosci(wielomian w, wymierna x) {
    wymierna wynik = w[0];
    wymierna podstawa = x;
    for (int i=1;i<=w[STOPIEN];i++) {
        wynik = suma(wynik, iloczyn(x, w[i]));
        x = iloczyn(x,podstawa); // potegujemy
    }
    return wynik;
}
