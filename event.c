enum Status {
  ACTIVE,
  INACTIVE,
};

typedef enum Status EventStatus;

struct Event {
  char const *name;
  char const *description;
  int ticketQuantity;
  EventStatus status;
};

typedef struct Event Event;

Event createEvent() {
  char const *name = inputStr("Informe o nome:\n");
  char const *description = inputStr("Informe a descrição:\n");
  int ticketQuantity = inputInt("Informe a quantidade de ingressos:\n");

  Event e = { name, description, ticketQuantity, INACTIVE };
  return e;
}
