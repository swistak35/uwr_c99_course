#include "activities.h"

FILE * activities_open_database(char * mode) {
  FILE * activities_file;

  static char db_path[1024];
  strcpy(db_path, homedir());
  strcat(db_path, ACTIVITIES_DB);

  activities_file = fopen(db_path, mode);

  if (activities_file == NULL) {
    activities_file = fopen(db_path, "wb");
    if (activities_file == NULL) {
      terminate("Nie udalo sie utworzyc pliku bazy danych.\n");
    } else {
      fclose(activities_file);
      activities_file = fopen(db_path, mode);
      if (activities_file == NULL) {
        terminate("Nie udalo sie otworzyc pliku bazy danych.\n");
      }
    }
  }

  return activities_file;
}

Activity activities_find_by_name(char * name) {
  FILE * activities_file = activities_open_database("rb");
  Activity tmp_activity;

  while (!feof(activities_file)) {
    fread(&tmp_activity, sizeof(Activity), 1, activities_file);
    if (!feof(activities_file) && strcmp(tmp_activity.name, name) == 0) {
      return tmp_activity;
    }
  }
  fclose(activities_file);

  tmp_activity.id = -1;
  return tmp_activity;
}

void activities_edit(Activity * activity) {
  int amount = activities_count();
  Activity all_activities[amount];
  activities_load(all_activities, amount);

  for (int i=0;i<amount;i++) {
    if (all_activities[i].id == activity->id) {
      strcpy(all_activities[i].name, activity->name);
    }
  }

  FILE * activities_file = activities_open_database("wb");
  fwrite(all_activities, sizeof(Activity), amount, activities_file);
  fclose(activities_file);
}

Activity activities_find_last(void) {
  FILE * activities_file = activities_open_database("rb");
  Activity tmp_activity;

  tmp_activity.id = -1;
  while (!feof(activities_file)) {
    fread(&tmp_activity, sizeof(Activity), 1, activities_file);
  }
  fclose(activities_file);

  return tmp_activity;
}

void activities_insert(Activity * new_activity) {
  int last_activity_id = activities_find_last().id;

  if (last_activity_id == -1) {
    new_activity->id = 1;
  } else {
    new_activity->id = last_activity_id + 1;
  }

  FILE * activities_file = activities_open_database("ab");
  fwrite(new_activity, sizeof(Activity), 1, activities_file);
  fclose(activities_file);
}

int activities_count(void) {
  FILE * activities_file = activities_open_database("rb");
  int size;
  fseek(activities_file, 0, SEEK_END);
  size = ftell(activities_file) / sizeof(Activity);
  fclose(activities_file);
  return size;
}

void activities_load(Activity tab[], int amount) {
  FILE * activities_file = activities_open_database("rb");
  fread(tab, sizeof(Activity), amount, activities_file);
  fclose(activities_file);
}

Activity activities_find_by_id(int id) {
  FILE * activities_file = activities_open_database("rb");
  Activity tmp_activity;

  while (!feof(activities_file)) {
    fread(&tmp_activity, sizeof(Activity), 1, activities_file);
    if (!feof(activities_file) && id == tmp_activity.id) {
      return tmp_activity;
    }
  }
  fclose(activities_file);

  tmp_activity.id = -1;
  return tmp_activity;
}

bool activities_remove_by_id(int remove_id) {
  int amount = activities_count();
  Activity all_activities[amount];
  activities_load(all_activities, amount);

  FILE * activities_file = activities_open_database("wb");
  bool removed = false;
  for (int i=0;i<amount;i++) {
    if (all_activities[i].id == remove_id) {
      removed = true;
    } else {
      fwrite(&all_activities[i], sizeof(Activity), 1, activities_file);
    }
  }
  fclose(activities_file);

  return removed;
}
