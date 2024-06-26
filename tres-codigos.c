#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>

// Estrutura para Lotes
typedef struct {
    int batchNumber;
    int ticketNumber;
    float ticketPrice;
} Batch;

// Estrutura para Areas
typedef struct area {
    char name[50];
    char description[100];
    Batch batches[20]; // Lotes associados à área
    int batchCount;    // Contador de lotes
} Area;

// Estrutura para Eventos
typedef struct {
    char *title;
    char *description;
    int ticketQuantity;
    int ID;
    int numAreas; // Numero de areas associadas ao evento
    Area *areas;  // Areas associadas ao evento
} Event;

// Declaracao das funcoes para Eventos
void menuEvents();
void registerEvent(Event *schedule, int *cont, int *i);
void updateEvent(Event *schedule, int cont);
void searchEvent(Event schedule[], int cont);
void listEvents(Event schedule[], int cont);

// Declaracao das funcoes para Areas
void createAreas(Area lista[], int tam);
void updateAreas(Area lista[], int tam);
void showAreas(Area lista[], int tam);
void searchArea(Area lista[], int tam);

// Declaracao das funcoes para Lotes
void registerBatch(Batch *batch, int *batchCount);
void updateBatch(Batch *batches, int batchCount);
void listBatches(Batch *batches, int batchCount);
void menuBatch();

// Main
int main() {
    Event schedules[20];
    int contEvents = 0; // Contador para eventos cadastrados
    int indexEvent = 0; // Indice para a proxima posicao no array de eventos
    int option;

    // Gerenciamento de Eventos
    do {
        menuEvents();
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                registerEvent(&schedules[indexEvent], &contEvents, &indexEvent);
                break;
            case 2:
                updateEvent(schedules, contEvents);
                break;
            case 3:
                searchEvent(schedules, contEvents);
                break;
            case 4:
                listEvents(schedules, contEvents);
                break;
            case 5:
                printf("Finalizando o programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                system("pause");
                system("cls");
        }
    } while (option != 5);

    // Libera a memoria alocada para titulos e descricoes dos eventos
    for (int i = 0; i < contEvents; i++) {
        free(schedules[i].title);
        free(schedules[i].description);
        free(schedules[i].areas); // Libera a memoria alocada para as areas
    }

    return 0;
}

// Funcoes para o gerenciamento de eventos
void menuEvents() {
    printf("\nMenu - Eventos:\n");
    printf("1. Cadastrar Evento\n");
    printf("2. Atualizar Evento\n");
    printf("3. Pesquisar Evento\n");
    printf("4. Apresentar todos os Eventos\n");
    printf("5. Finalizar Programa\n");
}

void registerEvent(Event *schedule, int *cont, int *i) {
    int r;
    int numAreas;
    schedule->title = malloc(sizeof(char) * 50);
    schedule->description = malloc(sizeof(char) * 1000);

    system("cls");
    printf("\n[CADASTRO DE EVENTOS]\n");
    printf("Digite o nome do evento: ");
    fgets(schedule->title, 50, stdin);
    strtok(schedule->title, "\n");

    printf("Digite a descricao do evento: ");
    fgets(schedule->description, 1000, stdin);
    strtok(schedule->description, "\n");

    printf("Digite a quantidade de ingressos para o evento: ");
    scanf("%d", &schedule->ticketQuantity);
    fflush(stdin);

    schedule->ID = *cont + 1;

    printf("\n[EVENTO CADASTRADO COM SUCESSO!]\n");
    printf("EVENTO: %s\n", schedule->title);
    printf("ID do evento: %d\n", schedule->ID);
    printf("DESCRICAO: %s\n", schedule->description);
    printf("QUANTIDADE DE INGRESSOS: %d\n", schedule->ticketQuantity);

    printf("\nDeseja fazer alguma alteracao?\n");
    printf("1. Sim\n2. Nao\n");
    scanf("%d", &r);
    fflush(stdin);

    if (r == 1) {
        updateEvent(schedule, *cont);
    }

    // Cadastro das Areas associadas ao evento
    printf("\n[CADASTRO DE AREAS PARA O EVENTO]\n");
    printf("Digite quantas areas voce deseja cadastrar para este evento: ");
    scanf("%d", &numAreas);
    fflush(stdin);

    schedule->numAreas = numAreas;
    schedule->areas = malloc(sizeof(Area) * numAreas);

    createAreas(schedule->areas, numAreas);

    (*cont)++;
    (*i)++;

    system("pause");
    system("cls");
}

void updateEvent(Event *schedules, int cont) {
    int r2, id;

    system("cls");
    printf("\n[ATUALIZACAO DE EVENTO]\n");
    printf("Digite o ID do evento a ser atualizado: ");
    scanf("%d", &id);
    fflush(stdin);

    for (int i = 0; i < cont; i++) {
        if (schedules[i].ID == id) {
            printf("Selecione a opcao que deseja atualizar:\n");
            printf("1. Nome do evento\n2. Descricao do evento\n3. Numero de ingressos\n4. Areas do evento\n5. Lotes do evento\n6. Todos\n");
            scanf("%d", &r2);
            fflush(stdin);

            switch (r2) {
                case 1:
                    printf("Digite o novo nome do evento: ");
                    fgets(schedules[i].title, 50, stdin);
                    strtok(schedules[i].title, "\n");
                    break;
                case 2:
                    printf("Digite a nova descricao do evento: ");
                    fgets(schedules[i].description, 1000, stdin);
                    strtok(schedules[i].description, "\n");
                    break;
                case 3:
                    printf("Digite a nova quantidade de ingressos: ");
                    scanf("%d", &schedules[i].ticketQuantity);
                    fflush(stdin);
                    break;
                case 4:
                    updateAreas(schedules[i].areas, schedules[i].numAreas);
                    break;
                case 5: {
                    int areaIndex;
                    printf("Digite o índice da área cujos lotes deseja atualizar (1 a %d): ", schedules[i].numAreas);
                    scanf("%d", &areaIndex);
                    fflush(stdin);
                    if (areaIndex > 0 && areaIndex <= schedules[i].numAreas) {
                        updateBatch(schedules[i].areas[areaIndex - 1].batches, schedules[i].areas[areaIndex - 1].batchCount);
                    } else {
                        printf("Índice de área inválido.\n");
                    }
                    break;
                }
                case 6:
                    printf("Digite o novo nome do evento: ");
                    fgets(schedules[i].title, 50, stdin);
                    strtok(schedules[i].title, "\n");
                    printf("Digite a nova descricao do evento: ");
                    fgets(schedules[i].description, 1000, stdin);
                    strtok(schedules[i].description, "\n");
                    printf("Digite a nova quantidade de ingressos: ");
                    scanf("%d", &schedules[i].ticketQuantity);
                    fflush(stdin);
                    updateAreas(schedules[i].areas, schedules[i].numAreas);
                    for (int j = 0; j < schedules[i].numAreas; j++) {
                        updateBatch(schedules[i].areas[j].batches, schedules[i].areas[j].batchCount);
                    }
                    break;
                default:
                    printf("Opcao invalida.\n");
                    system("pause");
                    return;
            }
            printf("\n[EVENTO ATUALIZADO COM SUCESSO!]\n");
            printf("EVENTO: %s\n", schedules[i].title);
            printf("DESCRICAO: %s\n", schedules[i].description);
            printf("QUANTIDADE DE INGRESSOS: %d\n", schedules[i].ticketQuantity);
            showAreas(schedules[i].areas, schedules[i].numAreas); // Mostra as áreas associadas
            system("pause");
            system("cls");
            return;
        }
    }

    printf("Evento com ID %d nao encontrado.\n", id);
    system("pause");
    system("cls");
}


void searchEvent(Event schedule[], int cont) {
    int id;
    system("cls");
    printf("Digite o ID do evento a ser pesquisado: ");
    scanf("%d", &id);
    fflush(stdin);

    for (int i = 0; i < cont; i++) {
        if (schedule[i].ID == id) {
            printf("\n[REGISTRO ENCONTRADO]\n");
            printf("EVENTO: %s\n", schedule[i].title);
            printf("DESCRICAO: %s\n", schedule[i].description);
            printf("QUANTIDADE DE INGRESSOS: %d\n", schedule[i].ticketQuantity);
            showAreas(schedule[i].areas, schedule[i].numAreas); // Mostra as areas associadas
            system("pause");
            system("cls");
            return;
        }
    }
    printf("Evento com ID %d nao encontrado.\n", id);
    system("pause");
    system("cls");
}

void listEvents(Event schedule[], int cont) {
    system("cls");
    printf("\n[LISTA DE EVENTOS]\n");

    for (int i = 0; i < cont; i++) {
        printf("ID: %d\n", schedule[i].ID);
        printf("EVENTO: %s\n", schedule[i].title);
        printf("DESCRICAO: %s\n", schedule[i].description);
        printf("QUANTIDADE DE INGRESSOS: %d\n", schedule[i].ticketQuantity);
        showAreas(schedule[i].areas, schedule[i].numAreas); // Mostra as areas associadas
        printf("\n");
    }
    system("pause");
    system("cls");
}

// Funcoes para o gerenciamento de areas
void createAreas(Area lista[], int tam) {
    int i, j;

    for (i = 0; i < tam; i++) {
        system("cls");
        printf("\n[CADASTRO DE AREA %d]\n", i + 1);
        printf("Digite o nome da area: ");
        fgets(lista[i].name, 50, stdin);
        strtok(lista[i].name, "\n");

        printf("Digite a descricao da area: ");
        fgets(lista[i].description, 100, stdin);
        strtok(lista[i].description, "\n");

        lista[i].batchCount = 0; // Inicializa o contador de lotes

        printf("\n[CADASTRO DE LOTES PARA A AREA %s]\n", lista[i].name);
        printf("Digite quantos lotes voce deseja cadastrar para esta area: ");
        scanf("%d", &lista[i].batchCount);
        fflush(stdin);

        for (j = 0; j < lista[i].batchCount; j++) {
            printf("\n[LOTE %d]\n", j + 1);
            registerBatch(&lista[i].batches[j], &lista[i].batchCount);
        }
    }
}

void updateAreas(Area lista[], int tam) {
    int i;
    char name[50];

    system("cls");
    printf("\n[ATUALIZACAO DE AREA]\n");
    printf("Digite o nome da area a ser atualizada: ");
    fgets(name, 50, stdin);
    strtok(name, "\n");

    for (i = 0; i < tam; i++) {
        if (strcmp(lista[i].name, name) == 0) {
            printf("Digite o novo nome da area: ");
            fgets(lista[i].name, 50, stdin);
            strtok(lista[i].name, "\n");

            printf("Digite a nova descricao da area: ");
            fgets(lista[i].description, 100, stdin);
            strtok(lista[i].description, "\n");

            printf("\n[AREA ATUALIZADA COM SUCESSO!]\n");
            system("pause");
            system("cls");
            return;
        }
    }

    printf("Area %s nao encontrada.\n", name);
    system("pause");
    system("cls");
}

void showAreas(Area lista[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        printf("\n[AREA %d]\n", i + 1);
        printf("NOME: %s\n", lista[i].name);
        printf("DESCRICAO: %s\n", lista[i].description);
        listBatches(lista[i].batches, lista[i].batchCount); // Lista os lotes da area
    }
}

void searchArea(Area lista[], int tam) {
    int i;
    char name[50];

    system("cls");
    printf("\n[PESQUISA DE AREA]\n");
    printf("Digite o nome da area a ser pesquisada: ");
    fgets(name, 50, stdin);
    strtok(name, "\n");

    for (i = 0; i < tam; i++) {
        if (strcmp(lista[i].name, name) == 0) {
            printf("\n[REGISTRO ENCONTRADO]\n");
            printf("NOME: %s\n", lista[i].name);
            printf("DESCRICAO: %s\n", lista[i].description);
            listBatches(lista[i].batches, lista[i].batchCount); // Lista os lotes da area
            system("pause");
            system("cls");
            return;
        }
    }

    printf("Area %s nao encontrada.\n", name);
    system("pause");
    system("cls");
}

// Funcoes para o gerenciamento de lotes
void registerBatch(Batch *batch, int *batchCount) {
    printf("Digite o numero do lote: ");
    scanf("%d", &batch->batchNumber);
    fflush(stdin);

    printf("Digite o numero do ingresso: ");
    scanf("%d", &batch->ticketNumber);
    fflush(stdin);

    printf("Digite o preco do ingresso: ");
    scanf("%f", &batch->ticketPrice);
    fflush(stdin);

    printf("\n[LOTE CADASTRADO COM SUCESSO!]\n");
}

void updateBatch(Batch *batches, int batchCount) {
    int batchNumber, i;

    printf("Digite o numero do lote a ser atualizado: ");
    scanf("%d", &batchNumber);
    fflush(stdin);

    for (i = 0; i < batchCount; i++) {
        if (batches[i].batchNumber == batchNumber) {
            printf("Digite o novo numero de ingresso: ");
            scanf("%d", &batches[i].ticketNumber);
            fflush(stdin);

            printf("Digite o novo preco do ingresso: ");
            scanf("%f", &batches[i].ticketPrice);
            fflush(stdin);

            printf("\n[LOTE ATUALIZADO COM SUCESSO!]\n");
            return;
        }
    }
    printf("Lote com numero %d nao encontrado.\n", batchNumber);
}

void listBatches(Batch *batches, int batchCount) {
    int i;
    printf("\n[LISTA DE LOTES]\n");
    for (i = 0; i < batchCount; i++) {
        printf("Numero do Lote: %d\n", batches[i].batchNumber);
        printf("Numero do Ingresso: %d\n", batches[i].ticketNumber);
        printf("Preco do Ingresso: %.2f\n", batches[i].ticketPrice);
    }
}

void menuBatch() {
    printf("\nMenu - Lotes:\n");
    printf("1. Cadastrar Lote\n");
    printf("2. Atualizar Lote\n");
    printf("3. Listar Lotes\n");
    printf("4. Sair\n");
}
