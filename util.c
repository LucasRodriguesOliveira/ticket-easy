#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int inputInt(char const *msg) {
  printf("%s", msg);

  int value;
  scanf("%d", &value);
  int c;
  while((c = getchar()) != '\n' && c != EOF);

  return value;
}

double inputDouble(char const *msg) {
  printf("%s", msg);

  double value;
  scanf("%lf", &value);
  int c;
  while((c = getchar()) != '\n' && c != EOF);

  return value;
}

char* inputStr(char const *msg, int str_sz) {
  printf("%s", msg);

  char *str = malloc(sizeof(char) * str_sz);

  fgets(str, str_sz, stdin);
  strtok(str, "\n");

  return str;
}

void clearConsole() {
  system("clear");
}

void shouldClear(enum CLEAR_CONSOLE option) {
  if (option == CLEAR) {
    clearConsole();
  }
}
