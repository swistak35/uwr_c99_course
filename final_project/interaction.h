#define INCLUDED_INTERACTION

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
#ifndef INCLUDED_STATISTICS
  #include "statistics.h"
#endif

// Menu główne
#define LC_MAIN_MENU          FONT_BOLD \
                              "===============================\n" \
                              "=== SYSTEM KIJA I MARCHEWKI ===\n" \
                              "====== wersja studencka =======\n" \
                              "===============================\n" \
                              FONT_NONE \
                              "1. Rejestracja czasu\n" \
                              "2. Zarzadzanie przedmiotami\n" \
                              "3. Zarzadzanie aktywnosciami\n" \
                              "4. Statystyki\n" \
                              "0. Wyjscie\n"

// Menu 'Zarządzanie przedmiotami'
#define LC_SUBJECTS_MENU      FONT_BOLD \
                              "===============================\n" \
                              "== Zarzadzanie przedmiotami  ==\n" \
                              FONT_NONE \
                              "1. Lista przedmiotow\n" \
                              "2. Dodaj przedmiot\n" \
                              "3. Edytuj przedmiot\n" \
                              "4. Usun przedmiot\n" \
                              "0. Powrot do menu glownego\n"

// Menu 'Zarządzanie aktywnościami'
#define LC_ACTIVITIES_MENU    FONT_BOLD \
                              "===============================\n" \
                              "== Zarzadzanie aktywnosciami ==\n" \
                              FONT_NONE \
                              "1. Lista aktywnosci\n" \
                              "2. Dodaj aktywnosc\n" \
                              "3. Edytuj aktywnosc\n" \
                              "4. Usun aktywnosc\n" \
                              "0. Powrot do menu glownego\n"

// Menu 'Statystyki'
#define LC_STATISTICS_MENU    FONT_BOLD \
                              "===============================\n" \
                              "========= Statystyki  =========\n" \
                              FONT_NONE \
                              "1. Czas poswiecony na poszczegolne przedmioty\n" \
                              "2. Czas poswiecony na poszczegolne aktywnosci\n" \
                              "3. Srednie czasy poswiecone na przedmiot\n" \
                              "4. Sredni czas nauki w danym dniu tygodnia\n" \
                              "0. Powrot do menu glownego\n"
// Menu główne
void interaction_menu(void);

// Zarządzanie przedmiotami - menu, dodawanie, listowanie, usuwanie
void interaction_subjects_menu(void);
void interaction_subjects_prompt_name(Subject * subject);
void interaction_subjects_insert(void);
void interaction_subjects_edit(void);
void interaction_subjects_list(void);
void interaction_subjects_remove(void);

// Zarządzanie aktywnościami - menu, dodawanie, listowanie, usuwanie
void interaction_activities_menu(void);
void interaction_activities_prompt_name(Activity * activity);
void interaction_activities_insert(void);
void interaction_activities_edit(void);
void interaction_activities_list(void);
void interaction_activities_remove(void);

// Mierzenie czasu - wybór przedmiotu i aktywności, właściwe mierzenie, pauzowanie i specjalny tryb uruchomienia programu
void interaction_timer_choice(void);
void interaction_timer_start(int subject_id, int activity_id);
void interaction_timer_pause(Timer * current_timer);
void interaction_timer_by_argv(char * subject_name, char * activity_name);

// Różne statystyki
void interaction_statistics_menu(void);
void interaction_statistics_subjects_sum(void);
void interaction_statistics_activities_sum(void);
void interaction_statistics_subjects_mean(void);
void interaction_statistics_wdays_mean(void);
