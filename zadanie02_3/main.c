#include <stdio.h>
#include <stdbool.h>

// Odcisk palca danego tekstu to wyliczona na podstawie wszystkich znaków tekstu pewna liczba.
// W najprostszym wariancie może to być suma kodów znaków. Na początku programu obliczany jest
// odcisk palca ze wzorca. W czasie przetwarzania tekstu liczone są odciski palca kolejnych
// fragmentów tekstu o długości wzorca (odcisk palca dla następnego fragmentu tekstu powinien
// być wyliczany za pomocą stałej liczby prostych operacji z dostępnych danych,
// np. w najprostszym wariancie przez dodanie do odcisku palca poprzedniego fragmentu tekstu
// kodu kolejnego znaku i odjęcie kodu znaku rozpoczynającego poprzedni fragment).
// Dokładne porównanie fragmentu ze wzorcem wykonujemy tylko wtedy, gdy zgadzają się ich
// odciski palców. Na końcu wypisać dodatkowo, ile razy zgodziły się odciski palców oraz
// ile było rzeczywistych trafień. Opis innej funkcji odcisku palca
// można znaleźć w: http://pl.wikipedia.org/wiki/Algorytm_Karpa-Rabina

// Uwagi: wzorzec powinien być przekazany jako argument wywołania programu - wtedy mozna go
// szukać w dowolnym pliku przekierowanym na standardowe wejście. Wiersze zawierające wzorzec
// powinny byc wypisywane.

int main(void) {
  int wzorzec[100];
  int tekst[10000];
  bool zgodnosc;
  int znak;
  
  int zgodny_odcisk = 0;
  int zgodny_wzorzec = 0;
  int odcisk_wzorca = 0;
  int dlugosc_wzorca = 0;
  int odcisk_fragmentu = 0;
  int dlugosc_fragmentu = 0;

  // Wczytywanie wzorca - aby przerwać, Ctrl+D
  while ((znak=getchar()) != EOF) {
    wzorzec[dlugosc_wzorca] = znak;
    odcisk_wzorca += znak;
    dlugosc_wzorca++;
  }

  // Żeby zacząć wpisywanie tekstu od nowej linii
  putchar('\n');
  
  // Wczytywanie tekstu
  while((znak=getchar()) != EOF) {
    tekst[dlugosc_fragmentu] = znak;
    odcisk_fragmentu += znak;
    dlugosc_fragmentu++;
    
    // Jeśli fragment jest wystarczająco długi, żeby mógł się w nim zmieścić wzorzec
    if (dlugosc_fragmentu >= dlugosc_wzorca) {
      // Jeśli odciski są takie same
      if (odcisk_fragmentu == odcisk_wzorca) {
        zgodny_odcisk++;
        
        // Zakładamy zgodność tekstu i szukamy błędu
        zgodnosc = true;
        for(int i=0;i<dlugosc_wzorca;i++) {
          if (wzorzec[i] != tekst[dlugosc_fragmentu-dlugosc_wzorca+i])
            zgodnosc = false;
        }
        if (zgodnosc == true)
          zgodny_wzorzec++;
      }
      
      odcisk_fragmentu -= tekst[dlugosc_fragmentu - dlugosc_wzorca];
    }
  }
  
  // Informacje
  printf("Wystąpień odcisku: %d\nWystąpień wzorca: %d\n", zgodny_odcisk, zgodny_wzorzec);
  printf("Dlugosc wzorca: %d\nOdcisk wzorca: %d\n", dlugosc_wzorca, odcisk_wzorca);
  return 0;
}
