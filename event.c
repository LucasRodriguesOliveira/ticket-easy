#include <stdio.h>
#include <stdlib.h>

struct Event {

    char *title;
    char *description;
    int ticketQuantity;

};

void updateEvent(struct Event *event);

int main() { 

    int r;
    struct Event event;

        printf ("\n\n\n[CADASTRO DE EVENTOS]\n\n\n");
        printf ("Digite o nome do evento: \n");
        event.title = malloc(sizeof(char) * 50);
        scanf ("%s", event.title);

        printf("Digite a descricao do evento: \n");
        event.description = malloc(sizeof(char) * 1000);
        scanf("%s", event.description);

        printf("Digite a quantidade de ingressos para o evento: \n");
        scanf("%d", &event.ticketQuantity);

        printf("\n\n[EVENTO CADASTRADO COM SUCESSO!]\n\n");
        printf("- EVENTO: %s\n", event.title);
        printf("- DESCRICAO: %s\n", event.description);
        printf("- QUANTIDADE DE INGRESSOS: %d\n", event.ticketQuantity);

        printf ("\n\nDeseja fazer alguma alteracao?\n");
        printf ("SIM = 1\nNAO = 2\n");
        scanf ("%d", &r);

        if (r==1){
            updateEvent(&event); 

        }else {
            printf ("\n\nGostaria de seguir para o cadastro de lotes?\n");
        } 
        return 0;
}

// Adicionar tela de confirmação
       
     void updateEvent(struct Event *event){
     int r2;

         printf("\n\n[ATUALIZACAO DE EVENTO]\n\n");   
         printf("Selecione a opcao que deseja atualizar\n");
         printf("\n1-Nome do evento\n2-Descricao do evento\n3-Numero de ingressos\n4-Todos\n");
         scanf("%d", &r2);

        switch (r2){

        case 1:
            printf("Digite o novo nome do evento:\n");
            scanf("%s", event->title);
            break;
        case 2:
            printf("Digite a nova descricao do evento:\n");
            scanf("%s", event->description);
            break;
        case 3:
            printf("Digite a nova quantidade de ingressos:\n");
            scanf("%d", &event->ticketQuantity);
            break;
        case 4:
            printf("Digite o novo nome do evento:\n");
            scanf("%s", event->title);
            printf("Digite a nova descricao do evento:\n");
            scanf("%s", event->description);
            printf("Digite a nova quantidade de ingressos:\n");
            scanf("%d", &event->ticketQuantity);
            break;
        default:
            break;
    }
         printf("[EVENTO ATUALIZADO COM SUCESSO!]\n\n"); 
         printf("- EVENTO: %s\n",event->title);
         printf("- DESCRICAO: %s\n",event->description);
         printf("- QUANTIDADE DE INGRESSOS: %d\n",event->ticketQuantity);
}
