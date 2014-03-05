#define INCLUDED_SUBJECTS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifndef INCLUDED_SUPPORT
  #include "support.h"
#endif

#define SUBJECTS_DB "/.carrot-subjects.bin"
#define SUBJECTS_MAX_LENGTH 19
#define SUBJECTS_MAX_LENGTH_STR "19"

typedef struct subject {
  int id;
  char name[SUBJECTS_MAX_LENGTH+1];
} Subject;

// Otworzenie pliku z bazą danych
FILE * subjects_open_database(char * mode);

// Znalezienie aktywności po nazwie
Subject subjects_find_by_name(char * name);

// Znalezienie ostatniej aktywności w db
Subject subjects_find_last(void);

// Dodanie aktywności
void subjects_insert(Subject * new_subject);

// Zliczenie aktywności w db
int subjects_count(void);

// Załadowanie aktywności do tablicy
void subjects_load(Subject tab[], int amount);

// Znalezienie aktywności po ID
Subject subjects_find_by_id(int id);

// Usunięcie aktywności o danym ID
bool subjects_remove_by_id(int remove_id);

// Edycja przedmiotu
void subjects_edit(Subject * subject);
