#ifndef BATCH_H
#define BATCH_H

// Estrutura para Lotes
struct Batch {
  int ID;
  int ticketNumber;
  float ticketPrice;
};

typedef struct Batch Batch;

struct BatchList {
  Batch **batches;
  int length;
  int capacity;
};

typedef struct BatchList BatchList;

Batch* createBatch(int ID, int maxTicketAvailable);
BatchList* createBatchList(int capacity);
void updateBatch(Batch *batch, int maxTicketAvailable);
void listBatches(BatchList *list);
int findBatch(int ID, BatchList *list);
Batch* getBatch(int pos, BatchList *list);
void addBatch(BatchList *list, Batch *batch);
void freeBatchList(BatchList *list);
void batchMenu(BatchList *list);

#endif
