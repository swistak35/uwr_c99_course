#include "queue.h"

void queue_flush(struct Queue * kolejka) {
  kolejka->begin = &kolejka->tab[0];
  kolejka->end = &kolejka->tab[0];
  kolejka->tab_begin = &kolejka->tab[0];
  kolejka->tab_end = &kolejka->tab[MAX_SIZE-1];
  kolejka->licznik = 0;
}

bool queue_push(struct Queue * kolejka, double element) {
  if (queue_if_full(kolejka))
    return false;

  *kolejka->end = element;

  if (kolejka->end != kolejka->tab_end) {
    kolejka->end++;
  } else {
    kolejka->end = kolejka->tab_begin;
  }

  kolejka->licznik++;
  return true;
}

void queue_display(struct Queue * kolejka) {
  double * it;
  it = kolejka->begin;
  if (queue_if_empty(kolejka))
    return;

  if ((kolejka->begin) < (kolejka->end)) {
    while (it < kolejka->end) {
      printf("%lf ", *it);
      it++;
    }
  } else {
    while (it <= kolejka->tab_end) {
      printf("%lf ", *it);
      it++;
    }
    it = kolejka->tab_begin;
    while (it < kolejka->end) {
      printf("%lf ", *it);
      it++;
    }
  }
}

bool queue_if_empty(struct Queue * kolejka) {
  return (kolejka->licznik == 0);
}

bool queue_if_full(struct Queue * kolejka) {
  return (kolejka->licznik == MAX_SIZE);
}

double queue_fetch(struct Queue * kolejka) {
  if (queue_if_empty(kolejka)) {
    return nan("empty");
  } else {
    return (*kolejka->begin);
  }
}

double queue_pop(struct Queue * kolejka) {
  if (queue_if_empty(kolejka)) {
    return nan("empty");
  } else {
    kolejka->licznik--;
    if (kolejka->begin != kolejka->tab_end) {
      kolejka->begin++;
      return *(kolejka->begin-1);
    } else {
      kolejka->begin = kolejka->tab_begin;
      return *(kolejka->tab_end);
    }
  }
}
