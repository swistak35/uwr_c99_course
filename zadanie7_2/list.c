#include "list.h"

// 1
struct element * list_init() {
  return NULL;
}

// 2
struct element * list_unshift(struct element * list, double value) {
  struct element * new_element;

  new_element = (struct element *) malloc(sizeof(struct element));

  if (is_empty(list))
    list = new_element;

  new_element->value = value;
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return list;
}

// 3
struct element * list_push(struct element * list, double value) {
  struct element * new_element;

  new_element = (struct element *) malloc(sizeof(struct element));

  if (is_empty(list))
    list = new_element;

  new_element->value = value;
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return new_element;
}

// 4
double list_shift(struct element ** list_ptr) {
  struct element * list = *list_ptr;
  if (is_empty(list))
    return nan("empty");

  struct element * shifting_element = (list->pointer);
  double return_value = shifting_element->value;

  // Jesli jest tylko jeden element
  if (shifting_element->pointer == shifting_element) {
    *list_ptr = list_init();
  } else {
    struct element * first_new_element = shifting_element->pointer;
    list->pointer = first_new_element;
  }

  free(shifting_element);
  return return_value;
}

// 5
double list_fetch_first(struct element * list) {
  if (is_empty(list))
    return nan("empty");
  struct element * first_element = list->pointer;
  return first_element->value;
}

// 6
bool is_empty(struct element * list) {
  return (list == NULL);
}

struct element * list_join(struct element * first_list, struct element * second_list) {
  if (is_empty(first_list)) {
    return second_list;
  }

  if (is_empty(second_list)) {
    return first_list;
  }

  struct element * new_first_element = first_list->pointer;

  first_list->pointer = second_list->pointer;
  second_list->pointer = new_first_element;

  return second_list;
}

// 8
struct element * list_copy(struct element * source_list) {
  struct element * destination_list;
  struct element * next_element;
  destination_list = list_init();

  if (!is_empty(source_list)) {
    next_element = source_list;
    do {
      next_element = next_element->pointer;
      destination_list = list_push(destination_list, next_element->value);
    } while (next_element != source_list);
  }

  return destination_list;
}

// 9
int list_count(struct element * list) {
  struct element * next_element;
  int count = 0;

  if (!is_empty(list)) {
    next_element = list;
    do {
      next_element = next_element->pointer;
      count++;
    } while (next_element != list);
  }
  return count;
}

// 10
struct element * list_add_in_order(struct element * list, double value) {
  struct element * next_element;
  struct element * new_element;

  if (is_empty(list)) {
    list = list_unshift(list, value);
  } else {
    next_element = list;

    do {
      if ((next_element->pointer)->value > value) {
        new_element = (struct element *) malloc(sizeof(struct element));
        new_element->value = value;
        new_element->pointer = next_element->pointer;
        next_element->pointer = new_element;
        return list;
      }
      next_element = next_element->pointer;
    } while (next_element != list);

    if (next_element == list) {
      list = list_push(list, value);
    }
  }
  return list;
}

