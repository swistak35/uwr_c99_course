#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 3

struct Queue {
  double tab[MAX_SIZE];
  // wskazuje pierwszy element w kolejce
  double * begin;
  // wskazuje na następny element za ostatnim
  double * end;
  // wskazuje odpowiednio na pierwszy i ostatni element tablicy, zawsze
  double * tab_begin;
  double * tab_end;
  int licznik;
};

void queue_flush(struct Queue * kolejka);
bool queue_push(struct Queue * kolejka, double element);
void queue_display(struct Queue * kolejka);
double queue_fetch(struct Queue * kolejka);
bool queue_if_empty(struct Queue * kolejka);
bool queue_if_full(struct Queue * kolejka);
double queue_pop(struct Queue * kolejka);
