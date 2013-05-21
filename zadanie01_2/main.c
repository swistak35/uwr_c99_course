#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// Napisz program, który wczytuje dwie liczby całkowite N i M,
// a następnie oblicza i drukuje wartość ilorazu N/M w postaci okresowego
// rozwinięcia dziesiętnego, np. `4/3` należy wydrukować jako `1,(3)`,
// a `2/7` jako `0,(285714)`. Ułamki, które mają skończone rozwinięcie dziesiętne
// należy wydrukować dokładnie (bez nawiasów zawierających 0),
// np. `3/8` należy wypisać jako `0,375`.

// Funkcja pomocnicza zwracająca wartość bezwzględną
int abs(int x) {
  if (x >= 0) {
    return x;
  } else {
    return -x;
  }
}

int main() {
  int x, y, c, cyfra;
  int okres = -1;
  int tab[10];
  
  for (int i=0;i<10;i++)
    tab[i] = 0;
  
  printf("Podaj 1 liczbe: ");
  scanf("%d", &x);

  printf("Podaj 2 liczbe: ");
  scanf("%d", &y);

  // Wyswietlenie bledu, gdy y == 0
  if (y == 0) {
    printf("Druga liczba musi być różna od zera.");
    return 0;
  }

  // Drukowanie znaku
  if (x*y < 0)
    printf("-");

  // Skoro mamy już znak, zajmujemy się tylko liczbami
  x = abs(x);
  y = abs(y);
  
  // Drukowanie części całkowitej i kropki
  printf("%d.", (x/y));
  
  // Część całkowita wydrukowana, więc zajmujemy się teraz częścią dziesiętną
  x = x % y;
  
  // Jeśli liczba jest całkowita, to drukujemy 0,
  // a jeśli nie, to szukamy rozwinięcia dziesiętnego
  if (x == 0) {
    printf("0");
  } else {
    c = 0;
    
    do {
      // Oblicz kolejną cyfrę rozwinięcia dziesiętnego
      x *= 10;
      cyfra = x / y;
      
      for (int i=0;i<c;i++) {
        // Ustaw pozycję, na której zaczyna się okres, jeśli znaleziono powtarzającą się cyfrę
        if (tab[i] == cyfra) {
          okres = i;
          break;
        }
      }
      
      // Jeśli cyfra jest zerem lub znaleziono okres, zakończ pętlę,
      // a jeśli nie, dodaj cyfrę do tablicy rozwinięcia dziesiętnego
      if (cyfra == 0 || okres >= 0) {
        break;
      } else {
        tab[c] = cyfra;
        x = x % y;
      }
      c++;
    } while (cyfra != 0 && okres == -1);
    // Powtarzaj, dopóki ostatnia cyfra rozwinięcia nie jest zerem i nie znaleziono powtarzającej się cyfry w rozwinięciu
    
    // Drukowanie rozwinięcia dziesiętnego
    for(int i=0;i<c;i++) {
      // Drukowanie nawiasu w odpowiednim miejscu
      if (i == okres)
        printf("(");
        
      printf("%d", tab[i]);
    }
    
    // Nawias zamykający, jeśli jest okres
    if (okres >= 0)
      printf(")");
  }
  
  printf("\n");
  return 0;
}
