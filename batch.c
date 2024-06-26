#include <stdio.h>
#include <stdlib.h>

#include "batch.h"
#include "util.h"
#include "menu.h"
#include "ticket.h"

void showBatch(Batch *batch) {
    printf("Numero do Lote: %d\n", batch->ID);
    printf("Numero do Ingresso: %d\n", batch->ticketNumber);
    printf("Preco do Ingresso: %.2f\n", batch->ticketPrice);
}

Batch* createBatch(int ID, int maxTicketAvailable) {
  Batch *batch = (Batch*) malloc(sizeof(Batch));

  batch->ID = ID;
  menu_name("CADASTRO DE LOTE", LOW);

  batch->ticketNumber = getTicketQuantity(maxTicketAvailable);
  batch->ticketPrice = inputDouble("Digite o preco do ingresso: ");

  printf("\n[LOTE CADASTRADO COM SUCESSO!]\n");
  return batch;
}

BatchList* createBatchList(int capacity) {
  BatchList *list = (BatchList*) malloc(sizeof(BatchList));

  list->batches = (Batch**) malloc(sizeof(Batch*) * capacity);
  list->length = 0;
  list->capacity = capacity;

  return list;
}

void resizeBatchList(BatchList *list) {
  list->capacity *= 2;
  list->batches = (Batch**) realloc(
    list->batches,
    sizeof(Batch*) * list->capacity
  );
}

void addBatch(BatchList *list, Batch *batch) {
  if (list->length == list->capacity) {
    resizeBatchList(list);
  }

  list->batches[list->length++] = batch;
}

void freeBatchList(BatchList *list) {
  for (int i = 0; i < list->length; i++) {
    free(list->batches[i]);
  }

  free(list->batches);
  free(list);
}

void updateBatch(Batch *batch, int maxTicketAvailable) {
  menu_name("ATUALIZANDO LOTE", LOW);
  printf("LOTE: [%d]\n", batch->ID);

  batch->ticketNumber = getTicketQuantity(maxTicketAvailable);
  batch->ticketPrice = inputDouble("Digite o novo preço do ingresso: ");
  batch->ticketNumber = getTicketQuantity(maxTicketAvailable);

  printf("\n[LOTE ATUALIZADO COM SUCESSO!]\n");
}

void listBatches(BatchList *list) {
  menu_name("LISTA DE LOTES", LOW);

  for (int i = 0; i < list->length; i++) {
    showBatch(list->batches[i]);
  }
}

int findBatch(int ID, BatchList *list) {
  for (int i = 0; i < list->length; i++) {
    if (list->batches[i]->ID == ID) {
      return i;
    }
  }

  return -1;
}

Batch* getBatch(int pos, BatchList *list) {
  if (pos < 0 || pos >= list->length) {
    return NULL;
  }

  return list->batches[pos];
}

void updateBatchMenu(BatchList *list, int maxTicketsAvailable) {
  int batchId = inputInt("Informe o Id do lote: ");

  Batch *batch = getBatch(
    findBatch(batchId, list),
    list
  );

  if (batch == NULL) {
    printf("\n\n\t-> Lote não encontrada!\n\n");
    return;
  }

  updateBatch(batch, maxTicketsAvailable);
}

void batchMenu(BatchList *list) {
  static struct OptionMenuItem batchMenuItems[4] = {
    { "Novo", CLEAR },
    { "Atualizar", CLEAR },
    { "Listar", CLEAR },
  };

  int option = 0;
  int availableTickets = 0;

  for (int i = 0; i < list->length; i++) {
    availableTickets -= list->batches[i]->ticketNumber;
  }

  do {
    menu_name("LOTES", HIGH);
    option = optionMenu(batchMenuItems, 4, "Voltar", CLEAR);

    switch (option) {
      case 1:
        createBatch(list->length, availableTickets);
        break;
      case 2:
        updateBatchMenu(list, availableTickets);
        break;
      case 3:
        listBatches(list);
        break;
    }
  } while (option != 0);
}
