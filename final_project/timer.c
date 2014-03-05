#include "timer.h"

FILE * timer_open_database(char * mode) {
  FILE * timer_file;

  static char db_path[1024];
  strcpy(db_path, homedir());
  strcat(db_path, TIMER_DB);

  timer_file = fopen(db_path, mode);

  if (timer_file == NULL) {
    timer_file = fopen(db_path, "wb");
    if (timer_file == NULL) {
      terminate("Nie udalo sie utworzyc pliku bazy danych.\n");
    } else {
      fclose(timer_file);
      timer_file = fopen(db_path, mode);
      if (timer_file == NULL) {
        terminate("Nie udalo sie otworzyc pliku bazy danych.\n");
      }
    }
  }

  return timer_file;
}

void timer_start(Timer * current_timer, int subject_id, int activity_id) {
  current_timer->start = time(NULL);
  current_timer->subject_id = subject_id;
  current_timer->activity_id = activity_id;
  current_timer->diff = 0;
}

void timer_stop(Timer * current_timer) {
  time_t time_now = time(NULL);
  current_timer->diff += time_now - current_timer->start;
}

void timer_pause(Timer * current_timer, Timer * pause_timer) {
  current_timer->diff -= pause_timer->diff;
}

void timer_stop_and_save(Timer * current_timer) {
  timer_stop(current_timer);

  FILE * timer_file = timer_open_database("ab");
  fwrite(current_timer, sizeof(Timer), 1, timer_file);
  fclose(timer_file);
}
