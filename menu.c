#include <stdio.h>
#include "menu.h"
#include "util.h"

void showOption(char const* name, int value) {
  printf("\t-> [%i]: %s\n", value, name);
}

enum CONFIRM_OPTIONS confirmMenu(char const* msg) {
  int option = CONFIRM_NO;
  int isInvalid = 1;

  do {
    printf("\nDeseja %s?\n", msg);
    showOption("Sim", CONFIRM_YES);
    showOption("Não", CONFIRM_NO);
    option = inputInt("Escolha: ");

    if (option < 0 || option > 1) {
      isInvalid = 1;
      printf("\t\t->[ Opção inválida! ]<-\n");
    }
    else {
      isInvalid = 0;
    }
  } while (isInvalid);

  return option;
}

void optionMenu(
  struct OptionMenuItem* items,
  int size,
  char const* end_msg,
  enum CLEAR_CONSOLE clearOption
) {
  int option = 0;
  clrB(clearOption);

  do {
    for (int i = 0; i < size; i++) {
      struct OptionMenuItem* item = &items[i];
      showOption(item->name, i + 1);
    }
    showOption(end_msg, 0);

    option = inputInt("Escolha: ");

    if (option < 0 || option > size) {
      printf("\n\t\t->[ Opção inválida! ]<-\n");
      continue;
    }

    if (!option) {
      return;
    }

    struct OptionMenuItem* item = &items[option - 1];
    clrB(item->clearOption);
    item->fn();
    clrA(item->clearOption);

    option = confirmMenu("continuar");

    clrA(clearOption);
  } while (option != 0);
}
