#ifndef UTIL_H
#define UTIL_H

enum CLEAR_CONSOLE {
  CLEAR,
  NO_CLEAR,
};

char* inputStr(char const *msg, int str_sz);
int inputInt(char const *msg);
double inputDouble(char const *msg);

void clearConsole();
void shouldClear(enum CLEAR_CONSOLE);

#endif
