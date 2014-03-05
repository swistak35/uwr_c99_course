#ifndef INCLUDED_INTERACTION
  #include "interaction.h"
#endif

int main(int argc, char** argv) {
  if (argc == 3) {
    interaction_timer_by_argv(argv[1], argv[2]);
  } else {
    interaction_menu();
  }

  return 0;
}
