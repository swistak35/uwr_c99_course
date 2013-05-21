#include <stdio.h>
#include <stdbool.h>

#define ZERO '0'

// Napisać program policz, który dla zadanego na wejściu wyrażenia zbudowanego
// z liczb całkowitych ze znakiem oraz operatorów +, -, * i / (bez nawiasów)
// obliczy wartość tego wyrażenia z uwzględnieniem priorytetów i łączności tych
// operatorów (takich jak w języku C). Użyć oddzielnej funkcji do obliczenia
// wartości podwyrażenia, w którym występują tylko operatory mnożenia i dzielenia.

bool czy_cyfra(int znak);
int cyfra(int znak);
int oblicz(int operacja, int liczba1, int liczba2);
void wyswietl_blad(int typ);
void ustaw_jako_przeciwna(int *liczba, bool *ujemna);
int wczytuj_mnozenie_dzielenie(int *znak, int liczba1);

int main() {
    printf("-------------------------\n");
    printf("Sposób działania programu\n");
    printf("Wpisz wyrażenie i zatwierdź ENTERem\n");
    printf("Minus stojacy przed liczba oznacza liczbe ujemna\n");
    printf("Przykladowe wyrażenia:\n");
    printf("2*3 + 4*5    (zwraca 26)\n");
    printf("-10 - -3     (zwraca -7)\n");
    printf("-2/5 * 100   (zwraca 0, bo dzielenie jest calkowite, wiec -2/5 = 0)\n");
    printf("-------------------------\n\n");

    int znak, liczba1, liczba2, operacja;
    bool poprzednio_cyfra, ujemna;

    poprzednio_cyfra = false;
    operacja = '+';
    liczba1 = 0;
    liczba2 = 0;
    ujemna = false;

    znak = getchar();
    do {
        // Dlaczego to jest rozdzielne od pozostalych przypadkow?
        //   Poniewaz po wykonaniu tego bloku, po wykonaniu dzielenia i mnozenia
        //   mamy w znak jakas operacje - dodawania lub odejmowania i chcemy ja jeszcze zaladowac.
        if (poprzednio_cyfra && (znak == '*' || znak == '/')) {
            liczba2 = wczytuj_mnozenie_dzielenie(&znak, liczba2);
            poprzednio_cyfra = true;
        }

        // Jesli wczesniej byla cyfra, a teraz jest + lub - to wykonaj poprzednia operacje
        //   i zdefiniuj nowa jako nastepna
        if (poprzednio_cyfra && (znak == '+' || znak == '-')) {
            ustaw_jako_przeciwna(&liczba2, &ujemna);
            liczba1 = oblicz(operacja, liczba1, liczba2);
            poprzednio_cyfra = false;
            operacja = znak;
        // Jesli cyfra, to wczytuj liczbe
        } else if (czy_cyfra(znak)) {
            // Jesli poprzednio byl znak, to rozpocznij wczytywanie nowej liczby
            if (!poprzednio_cyfra) {
                poprzednio_cyfra = true;
                liczba2 = 0;
            // Jesli nie, to kontunuuj wczytywanie
            } else {
                liczba2 *= 10;
            }
            liczba2 += cyfra(znak);
        // Jesli wczesniej byl znak, a teraz jest -, to zdefiniuj nastepna liczbe jako ujemna
        } else if (!poprzednio_cyfra && znak == '-') {
            ujemna = true;
        // Jesli bedzie spacja zignoruj
        // Jesli jest jeden ze znakow z rozdzielnych przypadkow, rowniez nie reaguj
        // Jesli jednak jakis inny znak, to wyrzuc blad
        } else if (znak != ' ' && znak != '\n' && !(poprzednio_cyfra && (znak == '*' || znak == '/'))) {
            wyswietl_blad(2);
        }

        // Jesli wprowadzilismy symbol zakonczenia wprowadzania wyrazenia
        // Ta instrukcja nie jest w kolejnym ifie, bo po wyjsciu z mnozenia/dzielenia, mogl byc znak \n, wiec
        // trzeba tutaj to sprawdzic - jesli tak bylo, to trzeba zakonczyc program
        if (znak == '\n' && poprzednio_cyfra) {
            ustaw_jako_przeciwna(&liczba2, &ujemna);
            liczba1 = oblicz(operacja, liczba1, liczba2);
            break;
        }
    } while (znak = getchar());

    printf("\n\nWynik: %d", liczba1);
    return 0;
}

int wczytuj_mnozenie_dzielenie(int *znak, int liczba1) {
    int operacja, liczba2;
    bool poprzednio_cyfra, ujemna;

    poprzednio_cyfra = true;
    operacja = *znak;
    liczba2 = 1; // Liczba neutralna dla mnozenia i dzielenia
    ujemna = false;

    do {
        // Jesli wprowadzilismy znak, ktory konczy wewnetrzna petle
        if ((*znak == '\n' || *znak == '+' || *znak == '-') && poprzednio_cyfra) {
            ustaw_jako_przeciwna(&liczba2, &ujemna);
            liczba1 = oblicz(operacja, liczba1, liczba2);
            break;
        // Jesli wczesniej byla cyfra, a teraz jest + lub - to wykonaj poprzednia operacje
        //   i zdefiniuj nowa jako nastepna
        } else if (poprzednio_cyfra && (*znak == '*' || *znak == '/')) {
            ustaw_jako_przeciwna(&liczba2, &ujemna);
            liczba1 = oblicz(operacja, liczba1, liczba2);
            poprzednio_cyfra = false;
            operacja = *znak;
        // Jesli cyfra, to wczytuj liczbe
        } else if (czy_cyfra(*znak)) {
            // Jesli poprzednio byl znak, to rozpocznij wczytywanie nowej liczby
            if (!poprzednio_cyfra) {
                poprzednio_cyfra = true;
                liczba2 = 0;
            // Jesli nie, to kontunuuj wczytywanie
            } else {
                liczba2 *= 10;
            }
            liczba2 += cyfra(*znak);
        // Jesli wczesniej byl znak, a teraz jest -, to zdefiniuj nastepna liczbe jako ujemna
        } else if (!poprzednio_cyfra && *znak == '-') {
            ujemna = true;
        // Jesli bedzie spacja, zignoruj, w przeciwnym wypadku wyswietl blad
        } else if (*znak != ' ') {
            wyswietl_blad(2);
        }
    } while (*znak = getchar());

    // Zwracamy wynik, a w *znak jest znak kolejnej operacji
    return liczba1;
}

// Zwraca true, jesli znak jest cyfra
bool czy_cyfra(int znak) {
    return (znak >= ZERO && znak <= (ZERO+9));
}

// Zwraca cyfre gdyby znak byl cyfra
int cyfra(int znak) {
    return (znak - ZERO);
}

int oblicz(int operacja, int liczba1, int liczba2) {
    // Wykonaj odpowiednia operacje
    if (operacja == '+') {
        return (liczba1 + liczba2);
    } else if (operacja == '-') {
        return (liczba1 - liczba2);
    } else if (operacja == '*') {
        return (liczba1 * liczba2);
    } else if (operacja == '/') {
        if (liczba2 == 0)
            wyswietl_blad(5);
        return (liczba1 / liczba2);
    // Lub wyswietl blad
    } else {
        wyswietl_blad(4);
    }
}

void wyswietl_blad(int typ) {
    if (typ == 2) {
        printf("BLAD: Nieprawidlowy znak.");
    } else if (typ == 3) {
        printf("BLAD: Brak pierwszej liczby.");
    } else if (typ == 4) {
        printf("BLAD: Niedozwolona operacja.");
    } else if (typ == 5) {
        printf("BLAD: Nie mozna dzielic przez 0.");
    } else {
        printf("BLAD: Wystapil blad.");
    }
    exit(typ);
}

void ustaw_jako_przeciwna(int *liczba, bool *ujemna) {
    if (*ujemna) {
        (*liczba) *= (-1);
        *ujemna = false;
    }
}
