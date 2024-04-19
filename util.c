#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int inputInt(char const *msg) {
  printf("%s", msg);

  int value;
  scanf("%d", &value);
  fflush(stdin);

  return value;
}

char *inputStr(char const *msg) {
  printf("%s", msg);

  char *str = malloc(sizeof(char) * 30);

  scanf("%s", str);
  fflush(stdin);

  return str;
}

void clearConsole() {
  system("clear");
}

void clrB(enum CLEAR_CONSOLE option) {
  if (option == CLEAR_BEFORE || option == CLEAR_BOTH) {
      clearConsole();
    }
}

void clrA(enum CLEAR_CONSOLE option) {
  if (option == CLEAR_AFTER || option == CLEAR_BOTH) {
      clearConsole();
    }
}
