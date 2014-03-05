#define INCLUDED_STATISTICS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef INCLUDED_SUPPORT
  #include "support.h"
#endif
#ifndef INCLUDED_ACTIVITIES
  #include "activities.h"
#endif
#ifndef INCLUDED_TIMER
  #include "timer.h"
#endif
#ifndef INCLUDED_SUBJECTS
  #include "subjects.h"
#endif

void statistics_subjects_sum(Subject all_subjects[], time_t sums[], int amount);
void statistics_activities_sum(Activity all_activities[], time_t sums[], int amount);
void statistics_subjects_mean(Subject all_subjects[], time_t means[], int amount);
void statistics_subjects_wdays_mean(time_t means[]);
