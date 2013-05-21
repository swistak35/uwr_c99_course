#include <stdbool.h>
#include <stdlib.h>

struct stack_element {
  int * table;
  struct stack_element * pointer;
};

struct stack_element * list_init();
struct stack_element * list_unshift(struct stack_element * list, int * table, int table_size);
void list_shift(struct stack_element ** list_ptr, int ** table_ptr, int table_size);
bool is_empty(struct stack_element * list);
