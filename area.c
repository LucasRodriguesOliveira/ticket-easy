#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Declaração da struct da área
struct area
{
    char name[50];
    char description[100];
};

typedef struct area area;

int tam;

area createArea(char *name, char *description);
// void updateArea(area *a);

int main()
{

    // printf("digite quantas areas voce deseja cadastrar: ");
    // scanf("%d", &tam);
    // fflush(stdin);

    // area lista[tam];
    // int i;
    // for (i = 0; i < tam; i++)
    // {
    //     printf("\narea %d:\n", i + 1);
    //     puts("nome: ");
    //     scanf("%100[^\n]s", lista[i].name);
    //     fflush(stdin);

    //     puts("descricao: ");
    //     scanf("%100[^\n]s", lista[i].description);
    //     fflush(stdin);
    // }
    // system("cls");

    // puts("Seus dados: \n");
    // for (i = 0; i < tam; i++)
    // {

    //     printf("-----------area %d -------------\n", i + 1);
    //     printf("\nnome: %s\n", lista[i].name);
    //     printf("descricao: %s\n\n\n", lista[i].description);
    // }
    // printf("------------------------------\n");
    char name[30];
    char description[50];

    printf("Informe o nome:\n");
    scanf("%s", name);

    printf("Informe a descrição:\n");
    scanf("%s", description);

    area a = createArea(name, description);

    printf("%s - %s", a.name, a.description);
}

area createArea(char *name, char *description) {
    area a;
    strcpy(a.name, name);
    strcpy(a.description, description);

    return a;
}