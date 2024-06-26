#include <stdlib.h>
#include <stdio.h>

#include "sale.h"
#include "event.h"
#include "util.h"
#include "ticket.h"
#include "area.h"
#include "batch.h"
#include "menu.h"

Sale* createSale(int ID, Event *event) {
  Sale *sale = (Sale*) malloc(sizeof(Sale));

  sale->ID = ID;
  sale->event = event;
  sale->total = 0.0;

  return sale;
}

SaleList* createSaleList(int capacity) {
  SaleList *list = (SaleList*) malloc(sizeof(SaleList));

  list->sales = (Sale**) malloc(sizeof(Sale*) * capacity);
  list->length = 0;
  list->capacity = capacity;

  return list;
}

void resizeSaleList(SaleList *list) {
  list->capacity *= 2;
  list->sales = (Sale**) realloc(
    list->sales,
    sizeof(Sale*) * list->capacity
  );
}

void addSale(SaleList *list, Sale *sale) {
  if (list->length == list->capacity) {
    resizeSaleList(list);
  }

  list->sales[list->length++] = sale;
}

void freeSaleList(SaleList *list) {
  for (int i = 0; i < list->length; i++) {
    list->sales[i] = NULL;
    free(list->sales[i]);
  }

  free(list->sales);
  free(list);
}

void makeSale(
  SaleList *saleList,
  EventList *eventList,
  TicketList *ticketList
) {
  Event *event = getEvent(
    findEvent(
      inputInt("Informe o ID do evento: "),
      eventList
    ),
    eventList
  );

  if (event == NULL) {
    printf("\n\n\t-> Evento não existe!!\n\n");
  }

  Area *area = getArea(
    findArea(
      inputInt("Informe o ID da Area: "),
      event->areaList
    ),
    event->areaList
  );

  if (event == NULL) {
    printf("\n\n\t-> Area não existe!!\n\n");
  }

  Batch *batch = getBatch(
    findBatch(
      inputInt("Infome o ID do Lote: "),
      area->batchList
    ),
    area->batchList
  );

  if (batch == NULL) {
    printf("\n\n\t-> Lote não existe!!\n\n");
  }

  TicketList *batchList = getTicketsByBatchId(ticketList, batch->ID);

  if (batchList->length == batch->ticketNumber) {
    printf("\nEste Lote não possui mais ingressos disponíveis!\n");
  }

  int qt = inputInt("Quantos ingreços deseja comprar?\n");
  double total = (double)batch->ticketPrice * (double)qt;

  printf("\n\n\t->Preço final: [%lf]\n\n", total);

  int option = confirmMenu("Deseja finalizar a compra?");

  if (option == CONFIRM_NO) {
    return;
  }

  printf("Evento: [%d] - %s", event->ID, event->title);
  printf("Area: [%d] - %s", area->ID, area->name);
  printf("Lote: [%d]", batch->ID);
  printf("\n\n\t\tRegistrando ingressos...\n\n");
  for (int i = 0; i < qt; i++) {
    Ticket *ticket = createTicket(ticketList->length, batch->ID);
    addTicket(ticketList, ticket);
    printf("->Ingresso [%d] adicionado ao lote [%d]\n", ticket->ID, batch->ID);
  }

  printf("\n\n\t\tVENDA REALIZADA COM SUCESSO!\n\n");
  Sale *sale = createSale(saleList->length, event);
}
