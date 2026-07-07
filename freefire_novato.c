#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[10];

int contador = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listar() {
    if (contador > 0) {
        printf("\n\n                    ITENS NA MOCHILA (%d/10)", contador);
        printf("\n------------------------------------------------------------------");
        printf("\nNOME                           | TIPO                 | QUANTIDADE");
        printf("\n------------------------------------------------------------------");
        for (int i = 0; i < contador; i++) {
            printf("\n%-30s | %-20s | %d", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("\n------------------------------------------------------------------");
        }
        limparBuffer();
        printf("\n\nPressione ENTER para continuar...");
        getchar();
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

void adicionar() {
    if (contador < 10) {
        printf("\n--- Adicionar Item ---");
        printf("\nNome: ");
        scanf("%s", mochila[contador].nome);
        printf("Tipo: ");
        scanf("%s", mochila[contador].tipo);
        printf("Quantidade: ");
        scanf("%d", &mochila[contador].quantidade);
        printf("\nItem \"%s\" adicionado com sucesso!", mochila[contador].nome);
        contador++;        
        listar();
    } else {
        printf("\n\nA mochila ja contem o limite de 10 itens!");
    }
}

void remover() {
    if (contador > 0) {
        char nome[30];
        printf("\n--- Remover Item ---");
        printf("\nNome: ");
        scanf("%s", nome);
        Item temp[10];
        int i = 0, t = 0;
        for (i = 0; i < contador; i++) { //adicionar num array temporário somente os itens que permanecerão
            if (strcmp(mochila[i].nome, nome) != 0) temp[t++] = mochila[i];
        }
        if (t == i) {
            printf("\nNenhum item foi removido!");
        } else {
            memcpy(mochila, temp, sizeof(temp)); //copiar o array temporário de volta para a mochila
            contador--;
            listar();
        }
    } else {
        printf("\n\nA mochila ja esta vazia!");
    }
}

int main() {
    int opcao;
    do {
        printf("\n\n-----------------------------------------------");
        printf("\n|  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  |");
        printf("\n-----------------------------------------------");
        printf("\nItens na mochila: %d/10", contador);
        printf("\n\n1. Adicionar Item");
        printf("\n2. Remover Item");
        printf("\n3. Listar Itens");
        printf("\n0. Sair");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar();
                break;
            case 2:
                remover();
                break;
            case 3:
                listar();
                break;
        }

    } while (opcao >= 1 && opcao <= 3);

    return 0;
}