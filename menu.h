#include "util.h"

#ifndef MENU_H
#define MENU_H

enum CONFIRM_OPTIONS {
  CONFIRM_NO,
  CONFIRM_YES,
};

typedef void (*Function)();

struct OptionMenuItem {
  char name[30];
  Function fn;
  enum CLEAR_CONSOLE clearOption;
};

/**
 * @param items dynamic array of menu items to iterate and show each option
 * @param size size of items array. Since it's a pointer, it's a way to know when to stop
 * @param end_msg message to ask if the user wants to stop showing this menu
 * 
 * Como utilizar (veja esse comentário diretamente, fica esquisito pelo intellisense):
 * 
 * #define MENU_SIZE 4
 * 
 * struct OptionMenuItem options[MENU_SIZE] = {
    { "First Option", first, CLEAR_BEFORE   },
    { "Second Option", second, CLEAR_AFTER },
    { "Third Option", third, CLEAR_BOTH },
    { "Fourth Option", fourth, NO_CLEAR },
  };
 * 
  optionMenu(
    options, // Lista de itens
    MENU_SIZE, // Tamanho da lista de itens
    "Finalizar programa", // Qualquer mensagem que preferir
    CLEAR_AFTER // Método de limpeza do console
  );
*/
void optionMenu(struct OptionMenuItem* items, int size, char const *end_msg, enum CLEAR_CONSOLE clearOption);

/**
 * @param msg mensagem a ser apresentada ao usuário para confirmação
*/
enum CONFIRM_OPTIONS confirmMenu(char const *msg);

#endif
