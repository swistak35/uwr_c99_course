#include "list.h"

struct element * list_init() {
  return NULL;
}

struct element * list_push(struct element * list, char value) {
  struct element * new_element;

  new_element = (struct element *) malloc(sizeof(struct element));

  if (is_empty(list))
    list = new_element;

  new_element->value = value;
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return new_element;
}

char list_shift(struct element ** list_ptr) {
  struct element * list = *list_ptr;
  if (is_empty(list))
    return nan("empty");

  struct element * shifting_element = (list->pointer);
  char return_value = shifting_element->value;

  if (shifting_element->pointer == shifting_element) {
    *list_ptr = list_init();
  } else {
    struct element * first_new_element = shifting_element->pointer;
    list->pointer = first_new_element;
  }

  free(shifting_element);
  return return_value;
}

bool is_empty(struct element * list) {
  return (list == NULL);
}
