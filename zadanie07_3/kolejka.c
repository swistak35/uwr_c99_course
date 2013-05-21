#include "kolejka.h"

bool queue_init(Queue ** my_queue) {
  *my_queue = (Queue *) malloc(sizeof(Queue));

  return (*my_queue != NULL);
}

bool queue_isempty(Queue * my_queue) {
  return (my_queue->begin == NULL && my_queue->end == NULL);
}

bool queue_unshift(Queue * my_queue, double new_element_value) {
  QElement * new_qelement;
  QElement * previous_first_qelement;

  new_qelement = (QElement *) malloc(sizeof(QElement));

  if (new_qelement == NULL)
    return false;

  new_qelement->value = new_element_value;

  if (queue_isempty(my_queue)) {
    my_queue->end = new_qelement;
  } else {
    previous_first_qelement = my_queue->begin;
    new_qelement->next = previous_first_qelement;
    previous_first_qelement->previous = new_qelement;
  }

  my_queue->begin = new_qelement;

  return true;
}

bool queue_push(Queue * my_queue, double new_element_value) {
  QElement * new_qelement;
  QElement * previous_last_qelement;

  new_qelement = (QElement *) malloc(sizeof(QElement));

  if (new_qelement == NULL)
    return false;

  new_qelement->value = new_element_value;

  if (queue_isempty(my_queue)) {
    my_queue->begin = new_qelement;
  } else {
    previous_last_qelement = my_queue->end;
    new_qelement->previous = previous_last_qelement;
    previous_last_qelement->next = new_qelement;
  }

  my_queue->end = new_qelement;

  return true;
}

double queue_fetch_first(Queue * my_queue) {
  return (queue_isempty(my_queue) ? nan("empty") : my_queue->begin->value);
}

double queue_fetch_last(Queue * my_queue) {
  return (queue_isempty(my_queue) ? nan("empty") : my_queue->end->value);
}

double queue_shift(Queue * my_queue) {
  double element;
  QElement * first_element;
  element = queue_fetch_first(my_queue);

  if (isnan(element)) {
    return nan("empty");
  } else {
    first_element = my_queue->begin;

    // jeśli kolejka jest jednoelementowa
    if (my_queue->end == first_element) {
      my_queue->begin = NULL;
      my_queue->end = NULL;
    } else {
      my_queue->begin = first_element->next;
    }

    free(first_element);
    return element;
  }
}

double queue_pop(Queue * my_queue) {
  double element;
  QElement * last_element;
  element = queue_fetch_last(my_queue);

  if (isnan(element)) {
    return nan("empty");
  } else {
    last_element = my_queue->end;

    // jeśli kolejka jest jednoelementowa
    if (my_queue->begin == last_element) {
      my_queue->begin = NULL;
      my_queue->end = NULL;
    } else {
      my_queue->end = last_element->previous;
    }

    free(last_element);
    return element;
  }
}

void queue_purge(Queue * my_queue) {
  QElement * element;
  QElement * previous;

  if (!queue_isempty(my_queue)) {
    element = my_queue->begin;

    do {
      previous = element;
      free(previous);
      if (element == my_queue->end) break;
      element = element->next;
    } while (true);

    my_queue->begin = NULL;
    my_queue->end = NULL;
  }
}

