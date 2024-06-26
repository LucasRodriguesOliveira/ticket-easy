#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "area.h"
#include "batch.h"
#include "menu.h"
#include "util.h"
#include "ticket.h"
#include "event.h"

void showArea(Area *area) {
  printf("\n[AREA %d]\n", area->ID);
  printf("NOME: %s\n", area->name);
  printf("DESCRICAO: %s\n", area->description);
}

Area* createArea(int ID, int maxTicketAvailable) {
  Area *area = (Area*) malloc(sizeof(Area));

  area->ID = ID;
  area->name = inputStr("Digite o nome da area: ", 50);
  area->description = inputStr("Digite a descricao da area: ", 100);
  area->ticketQuantity = getTicketQuantity(maxTicketAvailable);

  return area;
}

AreaList* createAreaList(int capacity) {
  AreaList *list = (AreaList*) malloc(sizeof(AreaList));
  list->areas = malloc(sizeof(Area*) * capacity);
  list->length = 0;
  list->capacity = capacity;

  return list;
}

void resizeAreaList(AreaList *areaList) {
  areaList->capacity *= 2;
  areaList->areas = realloc(
    areaList->areas,
    sizeof(Area*) * areaList->capacity
  );
}

void addArea(AreaList *list, Area *area) {
  if (list->length == list->capacity) {
    resizeAreaList(list);
  }

  list->areas[list->length++] = area;
}

void freeAreaList(AreaList *list) {
  for (int i = 0; i < list->length; i++) {
    freeBatchList(list->areas[i]->batchList);
    free(list->areas[i]);
  }

  free(list->areas);
  free(list);
}

void updateArea(Area *area, int maxTicketAvailable) {
  menu_name("ATUALIZACAO DE AREA", MID);
  printf("Area: [%d]\n", area->ID);

  area->name = inputStr("Digite o novo nome da area: ", 50);
  area->description = inputStr("Digite a nova descricao da area: ", 100);
  area->ticketQuantity = getTicketQuantity(maxTicketAvailable);

  printf("\n[AREA ATUALIZADA COM SUCESSO!]\n");
}

void showAreas(AreaList *list) {
  menu_name("LISTA DE AREAS", MID);
  for (int i = 0; i < list->length; i++) {
    showArea(list->areas[i]);
    menu_name("Lotes:", LOW);
    listBatches(list->areas[i]->batchList); // Lista os lotes da area
  }
}

int findArea(int ID, AreaList *list) {
  for (int i = 0; i < list->length; i++) {
    if (list->areas[i]->ID == ID) {
      return i;
    }
  }

  return -1;
}

Area* getArea(int pos, AreaList *list) {
  if (pos < 0 || pos >= list->length) {
    return NULL;
  }

  return list->areas[pos];
}

Area* createAreaMenu(AreaList *list, int maxTicketsAvailable) {
  menu_name("CADASTRO DE AREAS", MID);
  Area *area = createArea(list->length, maxTicketsAvailable);
  menu_name("AREA CADASTRADA COM SUCESSO", LOW);

  area->batchList = createBatchList(1);

  int option = confirmMenu("Deseja cadastrar os lotes?");

  if (option == CONFIRM_YES) {
    printf("\n[CADASTRO DE LOTES PARA A AREA %s]\n", area->name);
    int qt = inputInt("Digite quantos lotes voce deseja cadastrar: ");

    int availableTickets = area->ticketQuantity;

    for (int i = 0; i < qt; i++) {
      printf("\n[LOTE %d]\n", i + 1);

      Batch *batch = createBatch(
        area->batchList->length,
        availableTickets
      );

      addBatch(area->batchList, batch);

      availableTickets -= batch->ticketNumber;
    }
  }

  return area;
}

void updateAreaMenu(AreaList *list, int maxTicketsAvailable) {
  int areaId = inputInt("Informe o Id da area: ");

  Area *area = getArea(
    findArea(areaId, list),
    list
  );

  if (area == NULL) {
    printf("\n\n\t-> Área não encontrada!\n\n");
    return;
  }

  updateArea(area, maxTicketsAvailable);
}

void areaBatchMenu(AreaList *list) {
  int areaId = inputInt("Informe o Id da area: ");

  Area *area = getArea(
    findArea(areaId, list),
    list
  );

  if (area == NULL) {
    printf("\n\n\t-> Área não encontrada!\n\n");
    return;
  }

  batchMenu(area->batchList);
}

void areaMenu(AreaList *list) {
  static struct OptionMenuItem areaMenuItems[4] = {
    { "Novo", CLEAR },
    { "Atualizar", CLEAR },
    { "Listar", CLEAR },
    { "Lotes", NO_CLEAR },
  };

  int option = 0;
  int availableTickets = 0;

  for (int i = 0; i < list->length; i++) {
    availableTickets -= list->areas[i]->ticketQuantity;
  }

  do {
    menu_name("AREA", HIGH);
    option = optionMenu(areaMenuItems, 4, "Voltar", CLEAR);

    switch (option) {
      case 1:
        createAreaMenu(list, availableTickets);
        break;
      case 2:
        updateAreaMenu(list, availableTickets);
        break;
      case 3:
        showAreas(list);
        break;
      case 4:
        areaBatchMenu(list);
        break;
    }
  } while (option != 0);
}
