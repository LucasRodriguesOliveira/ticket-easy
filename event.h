#include "area.h"

#ifndef EVENT_H
#define EVENT_H

// Estrutura para Eventos
struct Event {
  char *title;
  char *description;
  int ticketQuantity;
  int ID;
  AreaList *areaList;  // Areas associadas ao evento
};

typedef struct Event Event;

struct EventList {
  Event **events;
  int length;
  int capacity;
};

typedef struct EventList EventList;

Event* createEvent(int ID);
void updateEvent(Event *event);
void listEvents(EventList *list);
int findEvent(int ID, EventList *list);
void showEvent(Event *e);
Event* getEvent(int pos, EventList *list);
void eventMenu(EventList *list);
EventList* loadEvents(int capacity);

#endif
