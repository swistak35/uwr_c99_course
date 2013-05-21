#define MAX_ZBIOR 1000

typedef int ELEMENT;
typedef ELEMENT ZBIOR[MAX_ZBIOR];

void suma_zbiorow(const ZBIOR zbior1, const ZBIOR zbior2, ZBIOR wynik);
void czyszczenie_zbioru(ZBIOR wynik);
void dodaj_element(ZBIOR wynik, ELEMENT e);
void usun_element(ZBIOR wynik, ELEMENT e);
void przekroj_zbiorow(const ZBIOR zbior1, const ZBIOR zbior2, ZBIOR wynik);
