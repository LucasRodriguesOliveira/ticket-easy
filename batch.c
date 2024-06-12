#include <stdio.h>
#include <windows.h>

// Declaração da struct do lote
struct Batch{
    int batchNumber;
    int ticketNumber;
    float ticketPrice; 
};

void updateBatch(struct Batch *batchEvent);

int main() {
    char ReplyNewBatch[4];
    int replyInfoBatch;
    struct Batch batchEvent;

    do {
        // Coleta e leitura do cadastro de lote
        printf("\n[---------- Cadastro de Lote -----------]\n\n\n");
        printf("Numero do Lote: ");
        scanf("%d", &batchEvent.batchNumber);
        printf("Numero de ingressos para o lote: ");
        scanf("%d", &batchEvent.ticketNumber);
        printf("Digite o preco (em R$) do ingresso deste lote: ");
        scanf("%f", &batchEvent.ticketPrice);

        // Confirmando o cadastro
        printf("\n[---------- Lote Cadastrado Com Sucesso!!! -----------]\n\n\n");
        printf("Lote numero: %d\n", batchEvent.batchNumber);
        printf("Numero de ingressos destinado ao lote: %d\n", batchEvent.ticketNumber);
        printf("Preco (em R$) dos ingressos do lote %d: R$%.2f\n\n", batchEvent.batchNumber, batchEvent.ticketPrice);

        // Pergunta se deseja se deseja alterar alguma informação
        printf("Deseja realizar alguma alteracao?");
        printf("-([1]SIM//[0]NAO)\n");
        scanf("%d", &replyInfoBatch);

        if(replyInfoBatch==1){
            updateBatch(&batchEvent);
        }else{
        }

        // Pergunta se deseja cadastrar mais um lote
        printf("\n\nDeseja cadastrar mais um lote para o evento X? (S/N)\n");
        scanf("%s", ReplyNewBatch);
    } while (ReplyNewBatch[0] == 's' || ReplyNewBatch[0] == 'S');
    printf("Deseja ir para o cadatro da Area?\n\n");
    printf("Programa encerrado!!!");
    return 0;
}

//função caso queira fazer alguma alteração
void updateBatch(struct Batch *batchEvent){
    int replyBatch;
    printf("[---------- Atualizacao de Lote -----------]\n\n\n\n");   
    printf("O que deseja alterar?");
    printf("\n1-Numero do lote\n2-Numero de ingressos do lote\n3-Preco dos ingressos do lote\n4-Todos\n");
    scanf("%d", &replyBatch);

    switch (replyBatch){

        case 1:
            printf("Digite o novo numero do lote: ");
            scanf("%d", &batchEvent->batchNumber);
            break;
        case 2:
            printf("Digite o novo numero de ingressos para o lote: ");
            scanf("%d", &batchEvent->ticketNumber);
            break;
        case 3:
            printf("Digite o novo preco (em R$) do ingresso deste lote: ");
            scanf("%f", &batchEvent->ticketPrice);
            break;
        case 4:
            printf("Digite o novo numero do lote: ");
            scanf("%d", &batchEvent->batchNumber);
            printf("Digite o novo numero de ingressos para o lote: ");
            scanf("%d", &batchEvent->ticketNumber);
            printf("Digite o novo preco (em R$) do ingresso deste lote: ");
            scanf("%f", &batchEvent->ticketPrice);
            break;
        default:
            break;
    }
    printf("[---------- Atualizacao de Lote -----------]\n\n\n\n"); 
    printf("Lote numero: %d\n",batchEvent->batchNumber);
    printf("Numero de ingressos destinado ao lote: %d\n", batchEvent->ticketNumber);
    printf("Preco (em R$) dos ingressos do lote %d: R$%.2f\n", batchEvent->batchNumber, batchEvent->ticketPrice);
    

}