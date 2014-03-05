#define INCLUDED_ACTIVITIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef INCLUDED_SUPPORT
  #include "support.h"
#endif

#define ACTIVITIES_DB "/.carrot-activities.bin"
#define ACTIVITIES_MAX_LENGTH 19
#define ACTIVITIES_MAX_LENGTH_STR "19"

typedef struct activity {
  int id;
  char name[ACTIVITIES_MAX_LENGTH+1];
} Activity;

// Otworzenie pliku z bazą danych
FILE * activities_open_database(char * mode);

// Znalezienie aktywności po nazwie
Activity activities_find_by_name(char * name);

// Znalezienie ostatniej aktywności w db
Activity activities_find_last(void);

// Dodanie aktywności
void activities_insert(Activity * new_activity);

// Zliczenie aktywności w db
int activities_count(void);

// Załadowanie aktywności do tablicy
void activities_load(Activity tab[], int amount);

// Znalezienie aktywności po ID
Activity activities_find_by_id(int id);

// Usunięcie aktywności o danym ID
bool activities_remove_by_id(int remove_id);

// Edycja aktywności
void activities_edit(Activity * activity);
