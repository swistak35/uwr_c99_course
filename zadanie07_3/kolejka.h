#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct queue_element {
  double value;
  struct queue_element * previous;
  struct queue_element * next;
} QElement;

typedef struct queue {
  struct queue_element * begin;
  struct queue_element * end;
} Queue;

bool queue_init(Queue ** my_queue);
bool queue_isempty(Queue * my_queue);
bool queue_unshift(Queue * my_queue, double new_element_value);
bool queue_push(Queue * my_queue, double new_element_value);
double queue_fetch_first(Queue * my_queue);
double queue_fetch_last(Queue * my_queue);
double queue_shift(Queue * my_queue);
double queue_pop(Queue * my_queue);
void queue_purge(Queue * my_queue);
