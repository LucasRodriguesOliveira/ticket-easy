#include "util.h"

#ifndef MENU_H
#define MENU_H

enum CONFIRM_OPTIONS {
  CONFIRM_NO,
  CONFIRM_YES,
};

enum MENU_LEVEL {
  MAIN,
  HIGH,
  MID,
  LOW,
};

struct OptionMenuItem {
  char name[30];
  enum CLEAR_CONSOLE clearOption;
};

/**
 * @param items dynamic array of menu items to iterate and show each option
 * @param size size of items array. Since it's a pointer, it's a way to know when to stop
 * @param end_msg message to ask if the user wants to stop showing this menu
*/
int optionMenu(struct OptionMenuItem* items, int size, char const *end_msg, enum CLEAR_CONSOLE clearOption);

/**
 * @param msg mensagem a ser apresentada ao usuário para confirmação
*/
enum CONFIRM_OPTIONS confirmMenu(char const *msg);

void hrc(int sz, char c);
void hr(int sz);

void menu_name(char const *name, enum MENU_LEVEL level);

#endif
