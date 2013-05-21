#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct element {
  double value;
  struct element * pointer;
};

struct element * list_init();
struct element * list_unshift(struct element * list, double value);
struct element * list_push(struct element * list, double value);
double list_shift(struct element * list);
double list_fetch_first(struct element * list);
bool is_empty(struct element * list);
struct element * list_join(struct element * first_list, struct element * second_list);
struct element * list_copy(struct element * source_list);
int list_count(struct element * list);
struct element * list_add_in_order(struct element * list, double value);

