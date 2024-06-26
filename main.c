#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "util.h"
#include "event.h"
#include "ticket.h"
#include "sale.h"

struct OptionMenuItem menuItems[2] = {
  { "Nova Venda", CLEAR },
  { "Eventos", CLEAR },
};

int main() {
  int option = 0;
  EventList *eventList = loadEvents(1);
  TicketList *ticketList = createTicketList(1);
  SaleList *saleList = createSaleList(1);

  do {
    menu_name("PRINCIPAL", MAIN);
    option = optionMenu(menuItems, 2, "Finalizar Programa", CLEAR);

    switch (option) {
      case 1:
        eventMenu(eventList);
        break;
      case 2:
        makeSale(saleList, eventList, ticketList);
        break;
      case 0:
        break;
      default:
        return 1;
    }
  } while (option != 0);

  return 0;
}
