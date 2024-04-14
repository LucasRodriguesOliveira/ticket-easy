#include "event.c"

#include <stdio.h>
#include <stdlib.h>

Event createEvent();
void updateEvent(Event*);
char *inputStr(char const *msg);
int inputInt(char const *msg);

int main() {
  Event e = createEvent();

  printf("Event created!\n");
  printf("Name=%s\n", e.name);
  printf("Description=%s\n", e.description);
  printf("TicketQuantity=%i\n", e.ticketQuantity);
  printf("Status=%i\n", e.status);

  updateEvent(&e);
  printf("Novo título: [%s]", e.name);

  return 0;
}

char *inputStr(char const *msg) {
  printf("%s", msg);
  fflush(stdin);

  char *str = malloc(sizeof(char) * 30);

  fgets(str, 30, stdin);

  return str;
}

int inputInt(char const *msg) {
  printf("%s", msg);
  fflush(stdin);

  int value;
  scanf("%d", &value);

  return value;
}

void updateEvent(Event *e) {
  int option;

  printf("Deseja atualizar o titulo?\n");
  printf("\t0 -> Sim\n");
  printf("\t1 -> Não\n");
  scanf("%d", &option);

  if (option == 0) {
    printf("\nInforme o novo título: ");
    char newTitle[30];
    scanf("%s", newTitle);

    printf("Titulo atualizado: [%s]\n", newTitle);

    e->name = newTitle;
  }
}
