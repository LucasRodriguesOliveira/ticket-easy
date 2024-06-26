#ifndef TICKET_H
#define TICKET_H

struct Ticket {
  int ID;
  int batchId;
};

typedef struct Ticket Ticket;

struct TicketList {
  Ticket **tickets;
  int length;
  int capacity;
};

typedef struct TicketList TicketList;

int getTicketQuantity(int max);
Ticket* createTicket(int ID, int batchId);
TicketList* createTicketList(int capacity);
TicketList* getTicketsByBatchId(TicketList *list, int batchId);
void addTicket(TicketList *list, Ticket *ticket);

#endif
