#include "statistics.h"

// Tabela przedmiotów, a obok suma czasów poświęconych na dany przedmiot
void statistics_subjects_sum(Subject all_subjects[], time_t sums[], int amount) {
  Timer tmp_timer;
  Subject * found_subject;
  int index;

  for (int i=0;i<amount;i++) {
    sums[i] = 0;
  }

  FILE * timer_file = timer_open_database("rb");

  while (!feof(timer_file)) {
    fread(&tmp_timer, sizeof(Timer), 1, timer_file);
    if (!feof(timer_file)) {
      found_subject = bsearch(&tmp_timer.subject_id, all_subjects, amount, sizeof(Subject), compare_subject_ids);
      if (found_subject != NULL) {
        index = found_subject - all_subjects;
        sums[index] += tmp_timer.diff;
      }
    }
  }
}

// Tabela aktywności, a obok suma czasów poświęconych na daną aktywność
void statistics_activities_sum(Activity all_activities[], time_t sums[], int amount) {
  Timer tmp_timer;
  Activity * found_activity;
  int index;

  for (int i=0;i<amount;i++) {
    sums[i] = 0;
  }

  FILE * timer_file = timer_open_database("rb");

  while (!feof(timer_file)) {
    fread(&tmp_timer, sizeof(Timer), 1, timer_file);
    if (!feof(timer_file)) {
      found_activity = bsearch(&tmp_timer.activity_id, all_activities, amount, sizeof(Activity), compare_activity_ids);
      if (found_activity != NULL) {
        index = found_activity - all_activities;
        sums[index] += tmp_timer.diff;
      }
    }
  }
}

// Tabela przedmiotów, a obok średnia czasów poświęconych na dany przedmiot
void statistics_subjects_mean(Subject all_subjects[], time_t means[], int amount) {
  Timer tmp_timer;
  Subject * found_subject;
  int counts[amount];
  int index;

  for (int i=0;i<amount;i++) {
    means[i] = 0;
    counts[i] = 0;
  }

  FILE * timer_file = timer_open_database("rb");

  while (!feof(timer_file)) {
    fread(&tmp_timer, sizeof(Timer), 1, timer_file);
    if (!feof(timer_file)) {
      found_subject = bsearch(&tmp_timer.subject_id, all_subjects, amount, sizeof(Subject), compare_subject_ids);
      if (found_subject != NULL) {
        index = found_subject - all_subjects;
        means[index] += tmp_timer.diff;
        counts[index]++;
      }
    }
  }

  for (int i=0;i<amount;i++) {
    if (counts[i] > 0) {
      means[i] /= counts[i];
    }
  }
}

// Tabela dni tygodnia, a obok średnia czasów nauki w danym dniu
void statistics_subjects_wdays_mean(time_t means[]) {
  Timer tmp_timer;
  int counts[7];
  struct tm * timeinfo;

  for (int i=0;i<7;i++) {
    means[i] = 0;
    counts[i] = 0;
  }

  FILE * timer_file = timer_open_database("rb");

  while (!feof(timer_file)) {
    fread(&tmp_timer, sizeof(Timer), 1, timer_file);
    if (!feof(timer_file)) {
      timeinfo = localtime(&(tmp_timer.start));
      means[timeinfo->tm_wday] += tmp_timer.diff;
      counts[timeinfo->tm_wday]++;
    }
  }

  for (int i=0;i<7;i++) {
    if (counts[i] > 0) {
      means[i] /= counts[i];
    }
  }
}
