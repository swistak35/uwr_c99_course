#include "support.h"

// Zakończenie programu i wyświetlenie błędu
void terminate(char * error) {
  fprintf(stderr, "Wystapil blad krytyczny: %s\n", error);
  exit(1);
}

// Pobranie za pomocą getchar pierwszego drukowalnego znaku w buforze
int get_visible(void) {
  int c;
  while((c = getchar()) && isspace(c));
  return c;
}

// Porównywarki, potrzebne do bsearcha
int compare_subject_ids(const void * a, const void * b) {
  return (((Subject*)a)->id - ((Subject*)b)->id);
}

int compare_activity_ids(const void * a, const void * b) {
  return (((Activity*)a)->id - ((Activity*)b)->id);
}

// Wieloargumentowa funkcja printf, czerwony kolor i pogrubienie
int printf_error(const char *format, ...) {
  int n;
  va_list ap;

  printf(FONT_RED FONT_BOLD);
  va_start(ap, format);
  n = vprintf(format, ap);
  va_end(ap);
  printf(FONT_NONE);

  return n;
}

// Wieloargumentowa funkcja printf, zielony kolor i pogrubienie
int printf_prompt(const char *format, ...) {
  int n;
  va_list ap;

  printf(FONT_GREEN FONT_BOLD);
  va_start(ap, format);
  n = vprintf(format, ap);
  va_end(ap);
  printf(FONT_NONE);

  return n;
}

// Wyświetlenie ilości sekund w formacie '11h, 35m, 24s'
char * parse_difftime(time_t diff, char * str) {
  int hours = diff / 3600;
  int minutes = (diff % 3600) / 60;
  int seconds = diff % 60;

  if (hours >= 10000) {
    sprintf(str, "%dh, %dm", hours, minutes);
  } else {
    sprintf(str, "%dh, %dm, %ds", hours, minutes, seconds);
  }
  return str;
}

// Home dir
char * homedir(void) {
  return getenv(HOME_VARIABLE);
}
