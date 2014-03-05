#include "subjects.h"

FILE * subjects_open_database(char * mode) {
  FILE * subjects_file;

  static char db_path[1024];
  strcpy(db_path, homedir());
  strcat(db_path, SUBJECTS_DB);

  subjects_file = fopen(db_path, mode);

  if (subjects_file == NULL) {
    subjects_file = fopen(db_path, "wb");
    if (subjects_file == NULL) {
      terminate("Nie udalo sie utworzyc pliku bazy danych.\n");
    } else {
      fclose(subjects_file);
      subjects_file = fopen(db_path, mode);
      if (subjects_file == NULL) {
        terminate("Nie udalo sie otworzyc pliku bazy danych.\n");
      }
    }
  }

  return subjects_file;
}

Subject subjects_find_by_name(char * name) {
  FILE * subjects_file = subjects_open_database("rb");
  Subject tmp_subject;

  while (!feof(subjects_file)) {
    fread(&tmp_subject, sizeof(Subject), 1, subjects_file);
    if (!feof(subjects_file) && strcmp(tmp_subject.name, name) == 0) {
      return tmp_subject;
    }
  }
  fclose(subjects_file);

  tmp_subject.id = -1;
  return tmp_subject;
}

Subject subjects_find_last(void) {
  FILE * subjects_file = subjects_open_database("rb");
  Subject tmp_subject;

  tmp_subject.id = -1;
  while (!feof(subjects_file)) {
    fread(&tmp_subject, sizeof(Subject), 1, subjects_file);
  }
  fclose(subjects_file);

  return tmp_subject;
}

void subjects_insert(Subject * new_subject) {
  int last_subject_id = subjects_find_last().id;

  if (last_subject_id == -1) {
    new_subject->id = 1;
  } else {
    new_subject->id = last_subject_id + 1;
  }

  FILE * subjects_file = subjects_open_database("ab");
  fwrite(new_subject, sizeof(Subject), 1, subjects_file);
  fclose(subjects_file);
}

int subjects_count(void) {
  FILE * subjects_file = subjects_open_database("rb");
  int size;
  fseek(subjects_file, 0, SEEK_END);
  size = ftell(subjects_file) / sizeof(Subject);
  fclose(subjects_file);
  return size;
}

void subjects_load(Subject tab[], int amount) {
  FILE * subjects_file = subjects_open_database("rb");
  fread(tab, sizeof(Subject), amount, subjects_file);
  fclose(subjects_file);
}

void subjects_edit(Subject * subject) {
  int amount = subjects_count();
  Subject all_subjects[amount];
  subjects_load(all_subjects, amount);

  for (int i=0;i<amount;i++) {
    if (all_subjects[i].id == subject->id) {
      strcpy(all_subjects[i].name, subject->name);
    }
  }

  FILE * subjects_file = subjects_open_database("wb");
  fwrite(all_subjects, sizeof(Subject), amount, subjects_file);
  fclose(subjects_file);
}

Subject subjects_find_by_id(int id) {
  FILE * subjects_file = subjects_open_database("rb");
  Subject tmp_subject;

  while (!feof(subjects_file)) {
    fread(&tmp_subject, sizeof(Subject), 1, subjects_file);
    if (!feof(subjects_file) && id == tmp_subject.id) {
      return tmp_subject;
    }
  }
  fclose(subjects_file);

  tmp_subject.id = -1;
  return tmp_subject;
}

bool subjects_remove_by_id(int remove_id) {
  int amount = subjects_count();
  Subject all_subjects[amount];
  subjects_load(all_subjects, amount);

  FILE * subjects_file = subjects_open_database("wb");
  bool removed = false;
  for (int i=0;i<amount;i++) {
    if (all_subjects[i].id == remove_id) {
      removed = true;
    } else {
      fwrite(&all_subjects[i], sizeof(Subject), 1, subjects_file);
    }
  }
  fclose(subjects_file);

  return removed;
}
