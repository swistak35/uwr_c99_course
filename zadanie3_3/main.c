#include <stdio.h>

// Wielomian jednej zmiennej o współczynnikach rzeczywistych może być reprezentowany
// poprzez stopień i tablicę współczynników typu double. Napisać program,
// który zawiera funkcje dodawania, odejmowania i mnożenia wielomianów, dzielenia wielomianów
// przez jednomian oraz funkcję main, która wykonuje zadane operacje na podanych wielomianach.
// Przydatne będą też funkcje czytania i wypisania wielomianu. Każdy wiersz danych standardowego
// wejścia zawiera znak operacji ('+', '-', '*', '/'), a następnie oddzielone spacjami dwa
// wielomiany - argumenty operacji (w przypadku dzielenia drugim argumentem jest jednomian).
// Wielomian zadany jest jako ciąg liczb n, a_0, a_1, ..., a_n, gdzie 0 <= n <= 1000 oraz
// a_n != 0, jeśli n > 0. Jednomian a*x^n jest podany jako dwie liczby: n i a. Wynikowe wielomiany
// powinny być wypisane w takiej samej postaci w oddzielnych wierszach; dla dzielenia reszta nie jest
// wypisywana. Liczby należy wypisywać z dwiema cyframi po przecinku.


int dodawanie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]);
int odejmowanie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]);
int mnozenie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]);
int dzielenie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]);
void czyszczenie_zer(int *n, double w[]);
void wyswietl_wielomian(int n, double w[]);
void wczytaj_wielomian(int n, double w[]);
void wczytaj_jednomian(int n, double w[]);

int main() {
  int n_w1, n_w2, n_out, znak, wynik;
  double w1[2001];
  double w2[2001];
  double out[2001];

	while ((znak = getchar()) != EOF) {
    if (znak != '+' && znak != '-' && znak != '*' && znak != '/')
      continue;

    // Wczytywanie 1 wielomianu
    scanf("%d", &n_w1);
    wczytaj_wielomian(n_w1, w1);

    // Wczytywanie 2 wielomianu lub jednomianu
    scanf("%d", &n_w2);
    if (znak == '/') {
      wczytaj_jednomian(n_w2, w2);
    } else {
      wczytaj_wielomian(n_w2, w2);
    }

    // Wykonanie odpowiedniej operacji
    switch (znak) {
      case '+':
        wynik = dodawanie(n_w1, w1, n_w2, w2, &n_out, out);
        break;
      case '-':
        wynik = odejmowanie(n_w1, w1, n_w2, w2, &n_out, out);
        break;
      case '*':
        wynik = mnozenie(n_w1, w1, n_w2, w2, &n_out, out);
        break;
      case '/':
        wynik = dzielenie(n_w1, w1, n_w2, w2, &n_out, out);
        break;
    }

    // Jesli operacja zakonczyla sie powodzeniem
    if (wynik == 0) {
      czyszczenie_zer(&n_out, out);
      wyswietl_wielomian(n_out, out);
    }
    // W przeciwnym wypadku petla zostanie uruchomiona jeszcze raz.
    // Byłoby w tym miejscu 'else continue', gdyby nie to, że to i tak jest
    //   koniec pętli
	}
	return 0;
}

// Wczytywanie wspolczynnikow wielomianu
void wczytaj_wielomian(int n, double w[]) {
  for (int i=0;i<=n;i++)
    scanf("%lf", &w[i]);
}

// Wczytywanie wspolczynnika jednomianu
void wczytaj_jednomian(int n, double w[]) {
  scanf("%lf", &w[0]);
}

// Wyswietlanie stopnia i wspolczynnikow wielomianu
void wyswietl_wielomian(int n, double w[]) {
  printf("%d", n);
  for (int i=0;i<=n;i++)
    printf(" %.2f", w[i]);
  printf("\n");
}

// Operacja dodawania. Stopniem wynikowego wielomianu bedzie wiekszy ze stopni
//   wejsciowych. Potem iterujemy po wszystkich potegach i sumujemy wspolczynniki.
int dodawanie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]) {
  if (nw1 > nw2)
    *nwout = nw1;
  else
    *nwout = nw2;

  for (int i=0;i<=*nwout;i++) {
    wout[i] = 0;
    if (nw1 >= i)
      wout[i] += w1[i];
    if (nw2 >= i)
      wout[i] += w2[i];
  }
  return 0;
}

// Tutaj rowniez stopniem wielomianu jest wiekszy z wejsciowych. Oczywiscie moze
//   sie zdarzyc, ze najwyzsza potega wielomianu sie zredukuje - za czyszczenie
//   niepotrzebnych zer z lewej strony wielomianu odpowiada funkcja czyszczenie_zer
//   wywoływana w main().
int odejmowanie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]) {
  if (nw1 > nw2)
    *nwout = nw1;
  else
    *nwout = nw2;

  for (int i=0;i<=*nwout;i++) {
    wout[i] = 0;
    if (nw1 >= i)
      wout[i] += w1[i];
    if (nw2 >= i)
      wout[i] -= w2[i];
  }
  return 0;
}

// Mnozenie wielomianów na zasadzie "kazdy z kazdym" i dodanie wartosci w odpowiednie
//   miejsce w tablicy (poczatkowo wypełniona zerami). Stopien wielomianu to suma
//   stopni wielomianow wejsciowych.
int mnozenie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]) {
  int potega;
  double wspolczynnik;
  *nwout = nw1 + nw2;

  for (int i=0;i<=*nwout;i++)
    wout[i] = 0;

  for (int i=0;i<=nw1;i++) {
    for (int j=0;j<=nw2;j++) {
      wspolczynnik = w1[i] * w2[j];
      potega = i + j;
      wout[potega] += wspolczynnik;
    }
  }
  return 0;
}

// Funkcja dzielenia zwraca 1 (czyli blad), gdy wielomian jest zerowy.
// Stopien wielomianu to roznica stopni wielomianow wejsciowych.
// Operacja dzielenia to podzielenie kazdego elementu wielomianu 1 przez jedyny
//   element wielomianu 2.
int dzielenie(int nw1, double w1[], int nw2, double w2[], int *nwout, double wout[]) {
  if (w2[0] == 0) {
    printf("Nie można dzielić przez wielomian zerowy!\n");
    return 1;
  } else if (nw2 > nw1) {
    *nwout = 0;
    wout[0] = 0;
  } else {
    *nwout = nw1 - nw2;

    for (int i=0;i<=*nwout;i++)
      wout[i] = 0;

    for (int i=nw1;i>=nw2;i--)
      wout[i-nw2] = w1[i] / w2[0];
  }
  return 0;
}

// Ta funkcja usuwa zera wiodace w wielomianie, tzn. konwertuje np.
// (0*x^4 + 0*x^3 + 2*x^2 + 5) do postaci (2*x^2 + 5)
void czyszczenie_zer(int *n, double w[]) {
  for (int i=*n;i>0;i--) {
    if (w[i] != 0)
      break;
    *n -= 1;
  }
}
