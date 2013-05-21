#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct element {
  int value;
  struct element * sublist;
  bool czy_lista;
  struct element * pointer;
} LElement;

void status(LElement * list);
void substatus(LElement * list, int depth);
void status_tab(int amount);
LElement * list_init();
LElement * list_push_value(LElement * list, int value);
LElement * list_push_list(LElement * list);
bool is_empty(LElement * list);
LElement * list_merge(LElement * first_list, LElement * second_list);
LElement * list_flat(LElement * list);
