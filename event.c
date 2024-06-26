#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"
#include "area.h"
#include "menu.h"
#include "util.h"
#include "ticket.h"

static int event_sz = 0;

Event* createEvent(int ID) {
  Event *e = (Event*) malloc(sizeof(Event));

  e->title = inputStr("Digite o nome do evento: ", 50);
  e->description = inputStr("Digite a descricao do evento: ", 100);
  e->ticketQuantity = inputInt("Digite a quantidade de ingressos para o evento: ");
  e->ID = ID;

  return e;
}

void updateEvent(Event *event) {
  menu_name("ATUALIZACAO DE EVENTO", HIGH);

  event->title = inputStr("Digite o novo nome do evento: ", 50);
  event->description = inputStr("Digite a nova descricao do evento: ", 100);
  event->ticketQuantity = inputInt("Digite a quantidade de ingressos");

  int availableQuantity = event->ticketQuantity;
  for(int i = 0; i < event->areaList->length; i++) {
    Area *a = event->areaList->areas[i];

    printf("Atualizar a quantidade de ingressos das areas do evento\n");
    printf("-> Area [%d]: %s\n", a->ID, a->name);
    hrc(25, '-');

    a->ticketQuantity = getTicketQuantity(availableQuantity);
    availableQuantity -= a->ticketQuantity;
  }

  printf("\n[EVENTO ATUALIZADO COM SUCESSO!]\n");
  showEvent(event);

  showAreas(event->areaList); // Mostra as áreas associadas
}

void showEvent(Event *e) {
  printf("ID: %d\n", e->ID);
  printf("NOME: %s\n", e->title);
  printf("DESCRICAO: %s\n", e->description);
  printf("QUANTIDADE DE INGRESSOS: %d\n", e->ticketQuantity);
}

void listEvents(EventList *list) {
  menu_name("LISTA DE EVENTOS", HIGH);

  for (int i = 0; i < list->length; i++) {
    showEvent(list->events[i]);
    showAreas(list->events[i]->areaList); // Mostra as areas associadas
  }
}

int findEvent(int ID, EventList *list) {
  for (int i = 0; i < list->length; i++) {
    if (list->events[i]->ID == ID) {
      return i;
    }
  }

  return -1;
}

Event* getEvent(int pos, EventList *list) {
  if (pos < 0 || pos >= list->length) {
    return NULL;
  }

  return list->events[pos];
}

void resizeEventList(EventList *eventList) {
  eventList->capacity *= 2;
  eventList->events = realloc(
    eventList->events,
    sizeof(Event*) * eventList->capacity
  );
}

EventList* loadEvents(int capacity) {
  EventList *eventList = (EventList*) malloc(sizeof(EventList));

  eventList->events = (Event**) malloc(sizeof(Event*) * capacity);
  eventList->length = 0;
  eventList->capacity = capacity;

  return eventList;
}

int saveEvents(Event *events) {
  free(events);

  return 1;
}

void addEvent(EventList *eventList, Event *event) {
  if (eventList->length == eventList->capacity) {
    resizeEventList(eventList);
  }

  eventList->events[eventList->length++] = event;
}

void updateMenu(EventList *list) {
  int ID = inputInt("Informe o ID do evento: ");

  Event *e = getEvent(
    findEvent(ID, list),
    list
  );

  if (e == NULL) {
    printf("\n\n\tEvento não encontrado!!\n\n");
    return;
  }

  updateEvent(e);
}

void createEventMenu(EventList *list) {
  menu_name("CADASTRO DE EVENTOS", HIGH);
  Event *event = createEvent(list->length);
  menu_name("EVENTO CADASTRADO COM SUCESSO!", MID);

  event->areaList = createAreaList(1);

  // Cadastro das Areas associadas ao evento
  int option = confirmMenu("Deseja cadastrar as Areas para este evento?");

  if (option == CONFIRM_YES) {
    printf("\n[CADASTRO DE AREAS PARA O EVENTO]\n");
    int qt = inputInt("Digite quantas areas voce deseja cadastrar para este evento: ");

    int availableTickets = event->ticketQuantity;

    for (int i = 0; i < qt; i++) {
      printf("\n[AREA %d]\n", i + 1);

      Area *area = createAreaMenu(
        event->areaList,
        availableTickets
      );

      availableTickets -= area->ticketQuantity;
    }
  }

  showEvent(event);

  addEvent(list, event);
}

void eventAreaMenu(EventList *list) {
  int eventId = inputInt("Informe o ID do evento: ");
  Event *event = getEvent(
    findEvent(eventId, list),
    list
  );

  if (event == NULL) {
    printf("\n\n\t->Evento não encontrado!\n\n");
    return;
  }

  areaMenu(event->areaList);
}

void eventMenu(EventList *list) {
  static struct OptionMenuItem eventMenuItems[4] = {
    { "Novo", CLEAR },
    { "Atualizar", CLEAR },
    { "Listar", CLEAR },
    { "Areas", NO_CLEAR },
  };

  int option = 0;

  do {
    menu_name("EVENTOS", HIGH);
    option = optionMenu(eventMenuItems, 4, "Voltar", CLEAR);

    switch (option) {
      case 1:
        createEventMenu(list);
        break;
      case 2:
        updateMenu(list);
        break;
      case 3:
        listEvents(list);
        break;
      case 4:
        eventAreaMenu(list);
        break;
    }
  } while (option != 0);
}
