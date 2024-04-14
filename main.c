#include <stdio.h>
#include <stdlib.h>

struct Event {
  char *name;
  char *description;
  int ticketQuantity;
};

char *inputStr(char const *msg);
int inputInt(char const *msg);

struct Event createEvent();
struct Event *findEvent(int id);
void listEvent();
void updateEvent();

struct Event events[3];

int main() {
  printf("Sistema de cadastro de eventos\n");

  int option;
  do {
    printf("Menu:\n");
    printf("\t1 -> Cadastrar evento\n");
    printf("\t2 -> Lista Eventos\n");
    printf("\t3 -> Atualizar Evento\n");
    printf("\n\t0 -> Finalizar aplicação\n");
    scanf("%d", &option);

    if (option < 0 || option > 3) {
      printf("Opção inválida!\n");
      continue;
    }

    switch (option)
    {
    case 1:
      struct Event e = createEvent();
      printf("Fim createEvent\n");
      events[0] = e;
      events[1] = e;
      events[2] = e;
      break;
    case 2:
      listEvent();
      break;
    case 3:
      updateEvent();
      break;
    }
  } while (option != 0);

  return 0;
}

char *inputStr(char const *msg) {
  printf("%s", msg);
  fflush(stdin);

  char *str = malloc(sizeof(char) * 30);

  scanf("%s", str);

  return str;
}

int inputInt(char const *msg) {
  printf("%s", msg);
  fflush(stdin);

  int value;
  scanf("%d", &value);

  return value;
}

struct Event createEvent() {
  system("clear");
  printf("[Criação de evento]\n\n");
  char *name = inputStr("Informe o nome do evento: ");
  char *desc = inputStr("Informe a descrição do evento: ");
  int qt = inputInt("Informe a quantidade de ingressos: ");

  struct Event e = {
    name,
    desc,
    qt,
  };

  printf("\nEvento cadastrado com sucesso!");

  return e;
}

struct Event *findEvent(int id) {
  printf("Encontrrar evento...\n");
  struct Event *e = &events[id];

  printf("Evento: [%s]\n", e->name);

  return e;
}

void listEvent() {
  printf("Listar evento...\n");
  for (int i = 0; i < 3; i++) {
    printf("Evento: %s\n", events[i].name);
  }
}

void updateEvent() {
  int id;
  printf("Atualizar evento...\n");

  printf("Informe o id do evento\n");
  scanf("%d", &id);
  struct Event *e = findEvent(id);

  printf("Novo nome do evento [%s]: ", (*e).name);
  scanf("%s", e->name);
  printf("Novo evento: %s\n", e->name);
  // - >
  // ->
}
