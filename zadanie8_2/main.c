#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Rozważamy wyrażenia arytmetyczne zbudowane z liczb rzeczywistych, operatorów dodawania (+),
// odejmowania (-), mnożenia (*) i dzielenia (/) oraz nawiasów. Operatory są lewostronnie łączne,
// a mnożenie i dzielenie mają wyższy priorytet niż dodawanie i odejmowanie. Takie wyrażenia
// mogą być reprezentowane przez drzewa wyrażenia, gdzie w liściach są liczby, a w węzłach pośrednich
// operatory. Napisać funkcję, która czyta wyrażenie zakończone znakiem średnika i tworzy dla niego
// drzewo wyrażenia. Drzewo powinno być zbudowane z węzłów dynamicznie tworzonych w stercie.
// Druga funkcja powinna wypisywać drzewo wyrażenia na standardowym wyjściu w postaci prefiksowej,
// czyli najpierw operator, a później jego argumenty. Na przykład wyrażenie ((2)+3)*(7-(5));
// powinno zostać wypisane jako (* (+ 2 3) (- 7 5)). Program główny powinien czytać ciągi
// wyrażeń i wypisywać je w postaci prefiksowej.



typedef struct tree_node {
  union {
    int operation;
    double number;
  } value;
  bool is_number;
  struct tree_node * left_node;
  struct tree_node * right_node;
} Node;

Node * node_init(bool is_number);
void terminate(char * error);
int char_buffer_pop();
void char_buffer_push(int chr);
void printf_tree(Node * tree);
Node * read_number();
Node * part_of_multiplication();
Node * part_of_sum();
Node * read_and_calculate_expression();
void set_as_negative(Node ** tree);

Node * node_init(bool is_number) {
  Node * new_node;
  new_node = malloc(sizeof(Node));
  new_node->left_node = NULL;
  new_node->right_node = NULL;
  new_node->is_number = is_number;
  return new_node;
}

void terminate(char * error) {
  printf("ERROR: %s\n", error);
  exit(1);
}

int char_buffer_pop() {
  int chr;

  while ((chr=getchar()) != EOF && isspace(chr));

  return chr;
}

void char_buffer_push(int chr) {
  ungetc(chr, stdin);
}

void printf_tree(Node * tree) {
  if (tree->is_number) {
    printf(" %.2lf", tree->value.number);
  } else {
    printf(" (%c", tree->value.operation);
    printf_tree(tree->left_node);
    printf_tree(tree->right_node);
    printf(")");
  }
}

void set_as_negative(Node ** tree_ptr) {
  Node * tree = *tree_ptr;
  Node * temp;
  if (tree->is_number) {
    tree->value.number = -(tree->value.number);
  } else {
    temp = tree;
    tree = node_init(false);
    tree->value.operation = '-';

    tree->left_node = node_init(true);
    tree->left_node->value.number = 0;

    tree->right_node = temp;
    *tree_ptr = tree;
  }
}

Node * read_number() {
  int chr;
  Node * number_node = node_init(true);
  double number = 0.0;
  double shift = 1.0;

  while ((chr = getchar()) != EOF && isdigit(chr))
    number = 10.0 * number + (chr - '0');

  if (chr == '.') {
    while ((chr = getchar()) != EOF && isdigit(chr)) {
      number = 10.0 * number + (chr - '0');
      shift *= 10.0;
    }
  }

  char_buffer_push(chr);
  number_node->value.number = (number / shift);
  return number_node;
}

Node * part_of_multiplication() {
  int chr;
  Node * result;
  bool negative = false;

  if ((chr = char_buffer_pop()) == '-')
    negative = true;
  else
    char_buffer_push(chr);

  chr = char_buffer_pop();

  if (isdigit(chr)) {
    char_buffer_push(chr);
    result = read_number();
  } else if (chr == '(') {
    result = read_and_calculate_expression();
    if ((chr = char_buffer_pop()) != ')') {
      terminate("Illegar char; expected ')'.");
    }
  } else {
    terminate("Illegal char; expected '(' or digit.");
  }

  if (negative) set_as_negative(&result);
  return result;
}

Node * part_of_sum() {
  int chr;
  Node * tree;
  Node * right;
  Node * temp;

  tree = part_of_multiplication();

  while ((chr = char_buffer_pop()) == '*' || chr == '/') {
    right = part_of_multiplication();

    temp = tree;
    tree = node_init(false);
    tree->value.operation = chr;

    tree->left_node = temp;
    tree->right_node = right;
  }

  char_buffer_push(chr);
  return tree;
}

Node * read_and_calculate_expression() {
  Node * tree;
  Node * right;
  Node * temp;

  int chr;

  tree = part_of_sum();

  while ((chr = char_buffer_pop()) == '+' || chr == '-') {
    right = part_of_sum();

    temp = tree;
    tree = node_init(false);
    tree->value.operation = chr;

    tree->left_node = temp;
    tree->right_node = right;
  }

  char_buffer_push(chr);
  return tree;
}

int main() {
  int chr;
  Node * tree = NULL;

  while ((chr = char_buffer_pop()) != EOF) {
    char_buffer_push(chr);

    tree = read_and_calculate_expression();

    if ((chr = char_buffer_pop()) == ';') {
      printf_tree(tree);
    } else {
      terminate("Illegal char.");
    }
  }
  return 0;
}
