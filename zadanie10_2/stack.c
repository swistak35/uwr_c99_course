#include "stack.h"

struct stack_element * list_init() {
  return NULL;
}

struct stack_element * list_unshift(struct stack_element * list, int * table, int table_size) {
  struct stack_element * new_element;

  new_element = (struct stack_element *) malloc(sizeof(struct stack_element));

  if (is_empty(list))
    list = new_element;

  new_element->table = malloc(sizeof(int) * table_size);
  memcpy(new_element->table, table, table_size * sizeof(int));
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return list;
}

void list_shift(struct stack_element ** list_ptr, int ** table_ptr, int table_size) {
  struct stack_element * list = *list_ptr;
  struct stack_element * shifting_element = (list->pointer);

  // Jesli jest tylko jeden element
  if (shifting_element->pointer == shifting_element) {
    *list_ptr = list_init();
  } else {
    struct stack_element * first_new_element = shifting_element->pointer;
    list->pointer = first_new_element;
  }

  memcpy(*table_ptr, shifting_element->table, table_size*sizeof(int));
  free(shifting_element->table);
  free(shifting_element);
}

bool is_empty(struct stack_element * list) {
  return (list == NULL);
}
