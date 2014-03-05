#include "interaction.h"

// Menu główne
void interaction_menu(void) {
  int c;
  do {
    printf(LC_MAIN_MENU);
    printf_prompt("Wybor opcji: ");
    c = get_visible();
    switch (c) {
      case '1':
        interaction_timer_choice();
        break;
      case '2':
        interaction_subjects_menu();
        break;
      case '3':
        interaction_activities_menu();
        break;
      case '4':
        interaction_statistics_menu();
        break;
      case '0':
        break;
      default:
        printf_error("Nieprawidlowa opcja.\n");
    }
  } while (c != '0');
}

// Menu 'Zarządzanie przedmiotami'
void interaction_subjects_menu(void) {
  int c;
  do {
    printf(LC_SUBJECTS_MENU);
    printf_prompt("Wybor opcji: ");
    c = get_visible();
    switch (c) {
      case '1':
        interaction_subjects_list();
        break;
      case '2':
        interaction_subjects_insert();
        break;
      case '3':
        interaction_subjects_edit();
        break;
      case '4':
        interaction_subjects_remove();
        break;
      case '0':
        break;
      default:
        printf(FONT_RED FONT_BOLD "Nieprawidlowa opcja.\n" FONT_NONE);
    }
  } while (c != '0');
}

// Helper interface for prompting subject's name
void interaction_subjects_prompt_name(Subject * subject) {
  int found_subject_id;
  bool valid;

  do {
    valid = true;
    printf_prompt("Podaj nazwe przedmiotu: ");
    scanf("%s", subject->name);

    found_subject_id = subjects_find_by_name(subject->name).id;
    if (found_subject_id > 0) {
      valid = false;
      printf_error("Taka nazwa jest juz zajeta, wprowadz inna!\n");
    }

    if (strlen(subject->name) > SUBJECTS_MAX_LENGTH) {
      valid = false;
      printf_error("Nazwa jest za dluga (max. " SUBJECTS_MAX_LENGTH_STR " znakow)!\n");
    }
  } while (!valid);
}

// Interfejs dodawania przedmiotu
void interaction_subjects_insert(void) {
  Subject new_subject;

  interaction_subjects_prompt_name(&new_subject);

  subjects_insert(&new_subject);
}

// Interfejs wyświetlania listy przedmiotów
void interaction_subjects_list(void) {
  int amount = subjects_count();
  Subject all_subjects[amount];
  subjects_load(all_subjects, amount);

  printf(FONT_UNDERLINE "| Numer | Nazwa               |\n");
  for (int i=0;i<amount;i++) {
    printf("| %5.d | %-" SUBJECTS_MAX_LENGTH_STR "." SUBJECTS_MAX_LENGTH_STR "s |\n", all_subjects[i].id, all_subjects[i].name);
  }
  printf(FONT_NONE);
}

// Editing a subject
void interaction_subjects_edit(void) {
  Subject edit_subject;
  int edit_id;
  interaction_subjects_list();
  printf_prompt("Podaj numer elementu do edycji: ");
  scanf("%d", &edit_id);

  edit_subject = subjects_find_by_id(edit_id);
  if (edit_subject.id > 0) {
    interaction_subjects_prompt_name(&edit_subject);
  } else {
    printf_error("Nie znaleziono elementu o numerze %d.\n", edit_id);
  }

  subjects_edit(&edit_subject);
}

// Interfejs usuwania przedmiotu
void interaction_subjects_remove(void) {
  int remove_id;
  interaction_subjects_list();
  printf_prompt("Podaj numer elementu do usuniecia: ");
  scanf("%d", &remove_id);

  if (subjects_remove_by_id(remove_id)) {
    printf("Element o numerze %d usunieto.\n", remove_id);
  } else {
    printf_error("Nie znaleziono elementu o numerze %d.\n", remove_id);
  }
}

// Menu 'Zarządzanie aktywnościami'
void interaction_activities_menu(void) {
  int c;
  do {
    printf(LC_ACTIVITIES_MENU);
    printf_prompt("Wybor opcji: ");
    c = get_visible();
    switch (c) {
      case '1':
        interaction_activities_list();
        break;
      case '2':
        interaction_activities_insert();
        break;
      case '3':
        interaction_activities_edit();
        break;
      case '4':
        interaction_activities_remove();
        break;
      case '0':
        break;
      default:
        printf_error("Nieprawidlowa opcja.\n");
    }
  } while (c != '0');
}

// Helper interface for prompting activity's name
void interaction_activities_prompt_name(Activity * activity) {
  int found_activity_id;
  bool valid;

  do {
    valid = true;
    printf_prompt("Podaj nazwe aktywnosci: ");
    scanf("%s", activity->name);

    found_activity_id = activities_find_by_name(activity->name).id;
    if (found_activity_id > 0) {
      valid = false;
      printf_error("Taka nazwa jest juz zajeta, wprowadz inna!\n");
    }

    if (strlen(activity->name) > ACTIVITIES_MAX_LENGTH) {
      valid = false;
      printf_error("Nazwa jest za dluga (max. " ACTIVITIES_MAX_LENGTH_STR " znakow)!\n");
    }
  } while (!valid);
}

// Interfejs dodawania aktywności
void interaction_activities_insert(void) {
  Activity new_activity;

  interaction_activities_prompt_name(&new_activity);

  activities_insert(&new_activity);
}

// Editing an activity
void interaction_activities_edit(void) {
  Activity edit_activity;
  int edit_id;
  interaction_activities_list();
  printf_prompt("Podaj numer elementu do edycji: ");
  scanf("%d", &edit_id);

  edit_activity = activities_find_by_id(edit_id);
  if (edit_activity.id > 0) {
    interaction_activities_prompt_name(&edit_activity);
  } else {
    printf_error("Nie znaleziono elementu o numerze %d.\n", edit_id);
  }

  activities_edit(&edit_activity);
}

// Interfejs wyświetlania listy aktywności
void interaction_activities_list(void) {
  int amount = activities_count();
  Activity all_activities[amount];
  activities_load(all_activities, amount);

  printf(FONT_UNDERLINE "| Numer | Nazwa               |\n");
  for (int i=0;i<amount;i++) {
    printf("| %5.d | %-" ACTIVITIES_MAX_LENGTH_STR "." ACTIVITIES_MAX_LENGTH_STR "s |\n", all_activities[i].id, all_activities[i].name);
  }
  printf(FONT_NONE);
}

// Interfejs usuwania aktywności
void interaction_activities_remove(void) {
  int remove_id;
  interaction_activities_list();
  printf_prompt("Podaj numer elementu do usuniecia: ");
  scanf("%d", &remove_id);

  if (activities_remove_by_id(remove_id)) {
    printf("Element o numerze %d usunieto.\n", remove_id);
  } else {
    printf_error("Nie znaleziono elementu o numerze %d.\n", remove_id);
  }
}

// Interfejs rozpoczynania mierzenia czasu - wybór przedmiotu i aktywności
void interaction_timer_choice(void) {
  int subject_id, activity_id;
  int found_id;

  interaction_subjects_list();
  do {
    printf_prompt("Podaj numer przedmiotu, ktorego chcesz sie uczyc (0 aby wyjsc): ");
    scanf("%d", &subject_id);

    if (subject_id == 0)
      return;

    found_id = subjects_find_by_id(subject_id).id;
    if (found_id == -1) {
      printf_error("Podales nieprawidlowy numer, sprobuj jeszcze raz.\n");
    }
  } while (found_id == -1);

  interaction_activities_list();
  do {
    printf_prompt("Podaj numer aktywnosci, ktora chcesz wykonywac (0 aby wyjsc): ");
    scanf("%d", &activity_id);

    if (activity_id == 0)
      return;

    found_id = activities_find_by_id(activity_id).id;
    if (found_id == -1) {
      printf_error("Podales nieprawidlowy numer, sprobuj jeszcze raz.\n");
    }
  } while (found_id == -1);

  interaction_timer_start(subject_id, activity_id);
}

// Interfejs uruchamiany w przypadku uruchomienia programu z 2 parametrami - nazwą przedmiotu i aktywności
void interaction_timer_by_argv(char * subject_name, char * activity_name) {
  int subject_id = subjects_find_by_name(subject_name).id;
  int activity_id = activities_find_by_name(activity_name).id;

  if (subject_id == -1) {
    terminate("Podales nieprawidlowa nazwe przedmiotu.");
  }
  if (activity_id == -1) {
    terminate("Podales nieprawidlowa nazwe aktywnosci.");
  }

  interaction_timer_start(subject_id, activity_id);
  exit(0);
}

// Właściwy interfejs mierzenia czasu
void interaction_timer_start(int subject_id, int activity_id) {
  Timer current_timer;
  int c;
  char info[16];

  timer_start(&current_timer, subject_id, activity_id);

  printf("Rozpoczeto zliczanie czasu.\n");

  do {
    printf("Aby zakonczyc, wpisz 'z', aby zapauzowac, wpisz 'p'\n");
    c = get_visible();
    switch (c) {
      case 'z':
        timer_stop_and_save(&current_timer);
        printf("Uczyles sie przez %s!\n", parse_difftime(current_timer.diff, info));
        break;
      case 'p':
        interaction_timer_pause(&current_timer);
        break;
      default:
        printf_error("Nieprawidlowa opcja.\n");
    }
  } while (c != 'z');
}

// Interfejs do pauzowania
void interaction_timer_pause(Timer * current_timer) {
  Timer pause_timer;
  int c;

  timer_start(&pause_timer, 0, 0);
  printf("Aby odpauzowac, wpisz 'p'.\n");
  do {
    c = get_visible();
    if (c == 'p') {
      timer_stop(&pause_timer);
      timer_pause(current_timer, &pause_timer);
    } else {
      printf_error("Nieprawidlowa opcja.\n");
    }
  } while (c != 'p');
}

// Menu 'Statystyki'
void interaction_statistics_menu(void) {
  int c;
  do {
    printf(LC_STATISTICS_MENU);
    printf_prompt("Wybor opcji: ");
    c = get_visible();
    switch (c) {
      case '1':
        interaction_statistics_subjects_sum();
        break;
      case '2':
        interaction_statistics_activities_sum();
        break;
      case '3':
        interaction_statistics_subjects_mean();
        break;
      case '4':
        interaction_statistics_wdays_mean();
        break;
      case '0':
        break;
      default:
        printf_error("Nieprawidlowa opcja.\n");
    }
  } while (c != '0');
}

// Tabela przedmiotów, a obok suma czasów poświęconych na dany przedmiot
void interaction_statistics_subjects_sum(void) {
  int amount = subjects_count();
  Subject all_subjects[amount];
  subjects_load(all_subjects, amount);
  time_t sums[amount];
  char str[16];

  statistics_subjects_sum(all_subjects, sums, amount);

  printf(FONT_UNDERLINE "| Przedmiot           | Suma czasu      |\n");
  for (int i=0;i<amount;i++) {
    printf("| %" SUBJECTS_MAX_LENGTH_STR "." SUBJECTS_MAX_LENGTH_STR "s | %15.15s |\n", all_subjects[i].name, parse_difftime(sums[i], str));
  }
  printf(FONT_NONE);
}

// Tabela aktywności, a obok suma czasów poświęconych na daną aktywność
void interaction_statistics_activities_sum(void) {
  int amount = activities_count();
  Activity all_activities[amount];
  activities_load(all_activities, amount);
  time_t sums[amount];
  char str[16];

  statistics_activities_sum(all_activities, sums, amount);

  printf(FONT_UNDERLINE "| Aktywnosc           | Suma czasu      |\n");
  for (int i=0;i<amount;i++) {
    printf("| %" ACTIVITIES_MAX_LENGTH_STR "." ACTIVITIES_MAX_LENGTH_STR "s | %15.15s |\n", all_activities[i].name, parse_difftime(sums[i], str));
  }
  printf(FONT_NONE);
}

// Tabela przedmiotów, a obok średnia czasów poświęconych na dany przedmiot
void interaction_statistics_subjects_mean(void) {
  int amount = subjects_count();
  Subject all_subjects[amount];
  subjects_load(all_subjects, amount);
  time_t means[amount];
  char str[16];

  statistics_subjects_mean(all_subjects, means, amount);

  printf(FONT_UNDERLINE "| Przedmiot           | Srednia czasu   |\n");
  for (int i=0;i<amount;i++) {
    printf("| %" SUBJECTS_MAX_LENGTH_STR "." SUBJECTS_MAX_LENGTH_STR "s | %15.15s |\n", all_subjects[i].name, parse_difftime(means[i], str));
  }
  printf(FONT_NONE);
}

// Tabela dni tygodnia, a obok średnia czasów nauki w danym dniu
void interaction_statistics_wdays_mean(void) {
  time_t means[7];
  char str[16];

  statistics_subjects_wdays_mean(means);

  printf(FONT_UNDERLINE "| Dzien        | Srednia czasu   |\n");
  printf("| Niedziela    | %15.15s |\n", parse_difftime(means[0], str));
  printf("| Poniedzialek | %15.15s |\n", parse_difftime(means[1], str));
  printf("| Wtorek       | %15.15s |\n", parse_difftime(means[2], str));
  printf("| Sroda        | %15.15s |\n", parse_difftime(means[3], str));
  printf("| Czwartek     | %15.15s |\n", parse_difftime(means[4], str));
  printf("| Piatek       | %15.15s |\n", parse_difftime(means[5], str));
  printf("| Sobota       | %15.15s |\n", parse_difftime(means[6], str));
  printf(FONT_NONE);
}
