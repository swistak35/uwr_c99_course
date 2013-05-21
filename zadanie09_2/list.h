#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct element {
  char value;
  struct element * pointer;
};

struct element * list_init();
struct element * list_push(struct element * list, char value);
char list_shift(struct element ** list_ptr);
bool is_empty(struct element * list);
