#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "menu.h"
#include "ticket.h"

int getTicketQuantity(int max) {
  int quantity = 0;

  do {
    printf("Ingressos disponíveis: [%d]\n", max);
    quantity = inputInt("Digite o numero do ingresso: ");

    if (quantity < 0 || quantity > max) {
      printf("\n\tQuantia de ingressos Inválida!\n");
    }

    if (quantity == 0) {
      int option = confirmMenu("Deseja realmente atribuir 0 ingressos?");

      if (option == CONFIRM_YES) {
        break;
      }
    }
  } while (quantity <= 0 || quantity > max);
}

Ticket* createTicket(int ID, int batchId) {
  Ticket *ticket = (Ticket*) malloc(sizeof(Ticket));

  ticket->ID = ID;
  ticket->batchId = batchId;

  return ticket;
}

TicketList* createTicketList(int capacity) {
  TicketList *list = (TicketList*) malloc(sizeof(TicketList));

  list->tickets = (Ticket**) malloc(sizeof(Ticket*) * capacity);
  list->length = 0;
  list->capacity = capacity;

  return list;
}

void resizeTicketList(TicketList *list) {
  list->capacity *= 2;
  list->tickets = (Ticket**) realloc(
    list->tickets,
    sizeof(Ticket*) * list->capacity
  );
}

void addTicket(TicketList *list, Ticket *ticket) {
  if (list->length == list->capacity) {
    resizeTicketList(list);
  }

  list->tickets[list->length++] = ticket;
}

void freeTicketList(TicketList *list) {
  for (int i = 0; i < list->length; i++) {
    free(list->tickets[i]);
  }

  free(list->tickets);
  free(list);
}

int findTicket(int ID, TicketList *list) {
  for (int i = 0; i < list->length; i++) {
    if (list->tickets[i]->ID == ID) {
      return i;
    }
  }

  return -1;
}

Ticket* getTicket(int pos, TicketList *list) {
  if (pos < 0 || pos >= list->length) {
    return NULL;
  }

  return list->tickets[pos];
}

TicketList* getTicketsByBatchId(TicketList *list, int batchId) {
  if (list->length == 0) {
    return NULL;
  }

  TicketList *batchTickets = createTicketList(1);

  for (int i = 0; i < list->length; i++) {
    Ticket *ticket = getTicket(
      i,
      list
    );

    if (ticket == NULL) {
      return NULL;
    }

    if (ticket->batchId == batchId) {
      addTicket(batchTickets, ticket);
    }
  }

  return batchTickets;
}
