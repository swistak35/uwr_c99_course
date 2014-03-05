#define INCLUDED_SUPPORT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#ifndef INCLUDED_SUBJECTS
  #include "subjects.h"
#endif
#ifndef INCLUDED_ACTIVITIES
  #include "activities.h"
#endif

#if defined(__linux__)
  #define HOME_VARIABLE "HOME"
#else
  #define HOME_VARIABLE "USERPROFILE"
#endif

// Różne specjalne ciągi do wyświetlania ciekawych rzeczy w terminalu linuksowym
// Jeśli system != linux, to po prostu "bajerów" nie ma.
#if defined(__linux__)
  #define FONT_BLINK "\033[05m"
  #define FONT_UNDERLINE "\033[04m"
  #define FONT_BOLD "\033[01m"
  #define FONT_NONE "\033[00m"
  #define FONT_RED "\033[31m"
  #define FONT_GREEN "\033[32m"
#else
  #define FONT_BLINK ""
  #define FONT_UNDERLINE ""
  #define FONT_BOLD ""
  #define FONT_NONE ""
  #define FONT_RED ""
  #define FONT_GREEN ""
#endif

// Zakończenie programu i wyświetlenie błędu
void terminate(char * error);

// Pobranie za pomocą getchar pierwszego drukowalnego znaku w buforze
int get_visible(void);

// Porównywarki, potrzebne do bsearcha
int compare_subject_ids(const void * a, const void * b);
int compare_activity_ids(const void * a, const void * b);

// Wieloargumentowe funkcje printf, jedna czerwona, druga zielona, obie pogrubione
int printf_error(const char *format, ...);
int printf_prompt(const char *format, ...);

// Wyświetlenie ilości sekund w formacie '11h, 35m, 24s'
char * parse_difftime(time_t diff, char * str);

// Zwraca katalog domowy
char * homedir(void);
