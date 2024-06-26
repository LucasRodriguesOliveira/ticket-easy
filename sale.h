#include "event.h"
#include "ticket.h"

#ifndef SALE_H
#define SALE_H

struct Sale {
  int ID;
  Event *event;
  double total;
};

typedef struct Sale Sale;

struct SaleList {
  Sale **sales;
  int length;
  int capacity;
};

typedef struct SaleList SaleList;

Sale* createSale(int ID, Event *event);
SaleList* createSaleList(int capacity);
void makeSale(SaleList *saleList, EventList *eventList, TicketList *ticketList);
void freeSaleList(SaleList *list);

#endif
