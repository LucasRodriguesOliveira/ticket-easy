#ifndef UTIL_H
#define UTIL_H

enum CLEAR_CONSOLE {
  CLEAR_BEFORE,
  CLEAR_AFTER,
  CLEAR_BOTH,
  NO_CLEAR,
};

char *inputStr(char const *msg);
int inputInt(char const *msg);

void clearConsole();
void clrB(enum CLEAR_CONSOLE);
void clrA(enum CLEAR_CONSOLE);

#endif
