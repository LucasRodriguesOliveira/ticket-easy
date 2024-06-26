#include <stdio.h>
#include "menu.h"
#include "util.h"

void showOption(char const* name, int value) {
  printf("-> [%i]: %s\n", value, name);
}

enum CONFIRM_OPTIONS confirmMenu(char const* msg) {
  int option = CONFIRM_NO;
  int isInvalid = 1;

  do {
    printf("\n%s\n", msg);
    showOption("Sim", CONFIRM_YES);
    showOption("Não", CONFIRM_NO);
    option = inputInt("\nEscolha: ");

    if (option < 0 || option > 1) {
      isInvalid = 1;
      printf("\t->[ Opção inválida! ]<-\n");
    }
    else {
      isInvalid = 0;
    }
  } while (isInvalid);

  return option;
}

int optionMenu(
  struct OptionMenuItem* items,
  int size,
  char const* end_msg,
  enum CLEAR_CONSOLE clearOption
) {
  int option = 0;

  do {
    for (int i = 0; i < size; i++) {
      struct OptionMenuItem* item = &items[i];
      showOption(item->name, i + 1);
    }
    showOption(end_msg, 0);

    option = inputInt("\nEscolha: ");

    if (option < 0 || option > size) {
      printf("\n\t->[ Opção inválida! ]<-\n");
      continue;
    }

    if (!option) {
      break;
    }

    struct OptionMenuItem* item = &items[option - 1];
    shouldClear(item->clearOption);
    return option;
  } while (option != 0);

  return 0;
}

void hrc(int sz, char c) {
  for (int i = 0; i < sz; i++) {
    printf("%c", c);
  }

  printf("\n\n");
}

void hr(int sz) {
  hrc(sz, '=');
}

void menu_name(char const *name, enum MENU_LEVEL level) {
  printf("[MENU] - [%s]\n", name);

  switch (level) {
    case MAIN:
      hr(45);
      break;
    case HIGH:
      hrc(40, '*');
      break;
    case MID:
      hrc(30, '-');
      break;
    case LOW:
      hrc(20, '.');
      break;
  }
}

