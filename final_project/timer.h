#define INCLUDED_TIMER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#ifndef INCLUDED_SUPPORT
  #include "support.h"
#endif

#define TIMER_DB "/.carrot-timer.bin"

typedef struct timer {
  time_t start;
  int subject_id;
  int activity_id;
  time_t diff;
} Timer;

// Otwarcie pliku z bazą danych
FILE * timer_open_database(char * mode);

// Rozpoczęcie odliczania czasu
void timer_start(Timer * current_timer, int subject_id, int activity_id);

// Zatrzymanie liczenia czasu
void timer_stop(Timer * current_timer);

// Zaaplikowanie licznika pauzy do innego licznika
void timer_pause(Timer * current_timer, Timer * pause_timer);

// Zatrzymanie licznika i zapisanie do bazy
void timer_stop_and_save(Timer * current_timer);

