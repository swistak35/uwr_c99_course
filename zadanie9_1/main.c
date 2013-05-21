#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Napisać program, który dla zadanych jako parametry wywołania programu nazwy pliku oraz
// liczby n podzieli wskazany plik na n prawie równych części (różniących się co najwyżej o jeden)
// i zapisze każdą część do odrębnego pliku wynikowego. Nazwy plików wynikowych powinny być
// tworzone z nazwy pliku źródłowego poprzez dodanie kolejnych liczb na końcu nazwy pliku.
// Jeśli plik źródłowy jest tekstowy, to podział powinien nastąpić względem liczby wierszy,
// jeśli jest binarny to względem liczby bajtów. Domyślnie traktujemy plik źródłowy jako binarny.
// Opcja -t jako pierwszy parametr wywołania programu powinna wskazywać, że plik trzeba
// potraktować jako tekstowy.

// Uwagi: Tylko pierwszy plik wynikowy jest poszerzany o dodatkowy bajt/wiersz, a powinno ich być
// tyle ile wynosi reszta z dzilenia count % split.


int main(int argc, char *argv[]) {
  int split;
  bool tekstowy = false;
  char source_filename[1024];

  if (argc < 2) {
    printf("Za malo parametrow!\n");
    exit(1);
  }

  sscanf(argv[1], "%d", &split);
  sscanf(argv[2], "%s", &source_filename);

  if (argc == 4 && argv[3][0] == '-' && argv[3][1] =='t')
    tekstowy = true;

  char source_path[768];
  char source_ext[256];

  char destination_filename[1024];
  int count, chunk, end, last_dot, last_slash;
  char str[10000];
  char byte;
  FILE * destination;
  FILE * source;

  last_dot = -1;
  last_slash = -1;
  for (int i=strlen(source_filename)-1;i>=0;i--) {
    if (source_filename[i] == '.' && last_dot < 0) {
      last_dot = i;
    }

    if (source_filename[i] == '/' && last_slash < 0) {
      last_slash = i;
    }
  }

//  printf("Bump. %d %d %d %s\n", last_dot, last_slash, strlen(source_filename), source_filename);
  if (last_dot > last_slash) {
    for (int j=0;j<last_dot;j++) {
      source_path[j] = source_filename[j];
    }
    source_path[last_dot] = '\0';

    for (int j=0;j<(strlen(source_filename) - last_dot);j++) {
      source_ext[j] = source_filename[j + last_dot];
    }
    source_ext[strlen(source_filename) - last_dot] = '\0';
  } else {
    strcpy(source_path, source_filename);
    source_ext[0] = '\0';
  }

//  printf("Sciezka: %s\n", source_path);
//  printf("Rozszerzenie: %s\n", source_ext);

  source = fopen(source_filename, (tekstowy ? "r" : "rb"));

  count = 0;
  if (tekstowy) {
    while (!feof(source)) {
      fgets(str, 10000, source);
      count++;
    }
  } else {
    while(fgetc(source) != EOF)
      count++;
  }
  rewind(source);

  chunk = count/split;

  for (int i=0;i<split;i++) {
    sprintf(destination_filename, "%s-%d%s", source_path, i+1, source_ext);
    destination = fopen(destination_filename, (tekstowy ? "w" : "wb"));

    if (chunk*split < count)
      end = chunk + 1;
    else
      end = chunk;

    if (tekstowy) {
      for (int j=0;j<end;j++) {
        fgets(str, 10000, source);

        if (!feof(source)) {
          fputs(str, destination);
        }
      }
    } else {
      for (int j=0;j<end;j++) {
        byte = fgetc(source);

        if (byte != EOF) {
          fputc(byte, destination);
        }
      }
    }

    count -= end;
    fclose(destination);
  }

  return 0;
}

