#include <stdio.h>
#include <stdbool.h>

// Napisać program, który na standardowym wyjściu wypisze dziesięć ostatnich wierszy
// z tekstu podanego na standardowym wejściu. Jeśli na wejściu tekst ma mniej
// niż 10 wierszy, to należy go skopiować w całości. Można założyć, że łączna
// długość 10 kolejnych wierszy w tekście nie przekracza stałej `MAX10` równej 10000.
// Jeśli tekst wejściowy nie spełnia tego założenia, to należy zasygnalizować błąd
// i przerwać przetwarzanie tekstu. Nie wolno ograniczać długości tekstu wyjściowego.

// Uwagi: W tablicy na wiersz rezerwowanych jest 10000 znaków, a czyta sie wiersze o maksymalnej
// długości 1024. Zmienna chars powinna być zmniejszana po przeczytaniu 11-tego i kolejnych
// wierszy - o długość wiersza, którego nie będzie się wypisywać.
// Bardzo nieefektywne kopiowanie całych wierszy - przecież można je zapisywać cyklicznie.

const int MAX10 = 10000;

int main() {
  char bufor[11][MAX10];
  int j,count=0;
  int chars=0;

  while (fgets(bufor[10],1024,stdin) != NULL) {
    if (count < 10) {
      count++;
    }

    // Zliczanie znaków
    j=0;
    while (bufor[10][j] != '\0') {
      chars++;
      j++;
    }

    // Nie wiem czy powinniśmy liczyć znaki nowego wiersza ('\n')
    // Ja ich nie liczę, dlatego wykonuję (chars--) po zliczaniu znaków z każdego wiersza.
    chars--;

    // Sprawdzanie, czy ilość znaków nie przekroczyła założeń zadania
    // Jeśli tak, to zakończenie działania programu
    if (chars > MAX10) {
      printf("Tekst wejsciowy jest zbyt dlugi (ilosc znakow przekracza stala MAX10).\n");
      return 1;
    }

    // Utrzymywanie bufora w takim stanie, żeby przetrzymywał tylko ostatnie 10 linijek
    for (int i=(10-count);i<10;i++) {
      j = 0;
      do {
        bufor[i][j] = bufor[i+1][j];
        j++;
      } while (bufor[i+1][j-1] != '\0');
    }
  }

  // Wyświetlenie ostatnich 10 linijek
  for (int i=(10-count);i<10;i++) {
    fputs(bufor[i], stdout);
  }

  return 0;
}
