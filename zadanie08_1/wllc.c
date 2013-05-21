#include "wllc.h"

void status(LElement * list) {
  substatus(list, 1);
}

void substatus(LElement * list, int depth) {
  LElement * next_element;

  if (is_empty(list)) {
    status_tab(depth);
    printf("Lista pusta\n");
  } else {
    next_element = list;

    do {
      next_element = next_element->pointer;
      status_tab(depth);
      if (next_element->czy_lista) {
        printf("* [sublist: %p] [next: %p] [addr: %p]\n", next_element->sublist, next_element->pointer, next_element);
        substatus(next_element->sublist, depth+1);
      } else {
        printf("* [value: %d] [next: %p] [addr: %p]\n", next_element->value, next_element->pointer, next_element);
      }
    } while (next_element != list);

    printf("\n");
  }
}

void status_tab(int amount) {
  for(int i=1;i<=amount;i++)
    printf("\t");
}

LElement * list_init() {
  return NULL;
}

LElement * list_push_value(LElement * list, int value) {
  LElement * new_element;

  new_element = (LElement *) malloc(sizeof(LElement));

  if (is_empty(list))
    list = new_element;

  new_element->value = value;
  new_element->czy_lista = false;
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return new_element;
}

LElement * list_push_list(LElement * list) {
  LElement * new_element;

  new_element = (LElement *) malloc(sizeof(LElement));

  if (is_empty(list))
    list = new_element;

  new_element->sublist = list_init();
  new_element->czy_lista = true;
  new_element->pointer = list->pointer;
  list->pointer = new_element;

  return new_element;
}

bool is_empty(LElement * list) {
  return (list == NULL);
}

LElement * list_merge(LElement * first_list, LElement * second_list) {
  if (is_empty(first_list)) {
    return second_list;
  }

  if (is_empty(second_list)) {
    return first_list;
  }

  LElement * new_first_element = first_list->pointer;

  first_list->pointer = second_list->pointer;
  second_list->pointer = new_first_element;

  return second_list;
}

LElement * list_flat(LElement * list) {
  LElement * next_element;
  LElement * new_list;
  new_list = list_init();
  next_element = list;

//  printf("Plaszcze:\n");
//  status(list);
//  getchar();
  do {
    next_element = next_element->pointer;

    if (next_element->czy_lista) {
//      printf("To lista, rekursja!\n");
      new_list = list_merge(new_list, list_flat(next_element->sublist));
    } else {
//      printf("To wartosc!\n");
      new_list = list_push_value(new_list, next_element->value);
    }
  } while(next_element != list);
//  printf("...splaszczylem.\n");


  return new_list;
}
