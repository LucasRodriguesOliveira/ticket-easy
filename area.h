#include "batch.h"

#ifndef AREA_H
#define AREA_H

// Estrutura para Areas
struct Area {
  int ID;
  char *name;
  char *description;
  int ticketQuantity;
  BatchList *batchList;
};

typedef struct Area Area;

struct AreaList {
  Area **areas;
  int length;
  int capacity;
};

typedef struct AreaList AreaList;

Area* createAreaMenu(AreaList *list, int maxTicketsAvailable) ;
AreaList* createAreaList(int capacity);
void updateArea(Area *area, int maxTicketAvailable);
void showAreas(AreaList *list);
int findArea(int ID, AreaList *list);
Area* getArea(int pos, AreaList *list);
void areaMenu(AreaList *list);
void addArea(AreaList *list, Area *area);
void freeAreaList(AreaList *list);

#endif
