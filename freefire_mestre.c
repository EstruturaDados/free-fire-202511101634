#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

Item mochila[20];

int contador = 0;
bool ordenado = false;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listar() {
    if (contador > 0) {
        printf("\n\n                          ITENS NA MOCHILA (%d/10)", contador);
        printf("\n-------------------------------------------------------------------------------");
        printf("\nNOME                           | TIPO                 | QUANTIDADE | PRIORIDADE");
        printf("\n-------------------------------------------------------------------------------");
        for (int i = 0; i < contador; i++) {
            printf("\n%-30s | %-20s | %-10d | %d", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
            printf("\n-------------------------------------------------------------------------------");
        }
        limparBuffer();
        printf("\n\nPressione ENTER para continuar...");
        getchar();
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

void adicionar() {
    if (contador < 20) {
        printf("\n--- Adicionar Item ---");
        printf("\nNome: ");
        scanf("%s", mochila[contador].nome);
        printf("Tipo: ");
        scanf("%s", mochila[contador].tipo);
        printf("Quantidade: ");
        scanf("%d", &mochila[contador].quantidade);
        printf("Prioridade: ");
        scanf("%d", &mochila[contador].prioridade);
        printf("\nItem \"%s\" adicionado com sucesso!", mochila[contador].nome);
        contador++;        
        listar();
    } else {
        printf("\n\nA mochila ja contem o limite de 20 itens!");
    }
}

void descartar() {
    if (contador > 0) {
        char nome[30];
        printf("\n--- Descartar Item ---");
        printf("\nNome: ");
        scanf("%s", nome);
        Item temp[20];
        int i = 0, t = 0;
        for (i = 0; i < contador; i++) { //adicionar num array temporário somente os itens que permanecerão
            if (strcmp(mochila[i].nome, nome) != 0) temp[t++] = mochila[i];
        }
        if (t == i) {
            printf("\n\nNenhum item foi removido!");
        } else {
            memcpy(mochila, temp, sizeof(temp)); //copiar o array temporário de volta para a mochila
            contador--;
            listar();
        }
    } else {
        printf("\n\nA mochila ja esta vazia!");
    }
}

void bubbleSortNome() {
    Item temp;
    int comparacoes = 0;
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                comparacoes++;
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    ordenado = true;
    printf("\nMochila organizada por nome!");
    printf("\nTotal de comparacoes: %d", comparacoes);
    listar();
}

void insertionSortTipo() {
    Item chave;
    int comparacoes = 0, j;
    for (int i = 1; i < contador; i++) {
        chave = mochila[i];
        j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    ordenado = false;
    printf("\nMochila organizada por tipo!");
    printf("\nTotal de comparacoes: %d", comparacoes);
    listar();
}

void selectionSortPrioridade() {
    Item temp;
    int comparacoes = 0, menor;
    for (int i = 0; i < contador - 1; i++) {
        menor = i;
        for (int j = i + 1; j < contador; j++) {
            comparacoes++;
            if (mochila[j].prioridade < mochila[menor].prioridade) menor = j;
        }
        if (menor != i) {
            temp = mochila[i];
            mochila[i] = mochila[menor];
            mochila[menor] = temp;
        }
    }
    ordenado = false;
    printf("\nMochila organizada por prioridade!");
    printf("\nTotal de comparacoes: %d", comparacoes);
    listar();
}

void buscarBinaria() {
    if (contador > 0) {
        if (ordenado) {
            char nome[30];
            printf("\n--- Buscar Item (Binaria) ---");
            printf("\nNome: ");
            scanf("%s",nome);
            int comparacoes = 0, inicio = 0, fim = contador - 1;
            while (inicio <= fim) {
                comparacoes++;
                int meio = (inicio + fim) / 2;
                int r = strcmp(nome, mochila[meio].nome);
                if (r == 0) {
                    printf("\nItem encontrado na posição %d do vetor, ou seja, no indice %d", meio + 1, meio);
                    goto finalizar;
                } else if (r < 0) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            }
            printf("\nItem nao encontrado!");
            finalizar:
            printf("\nTotal de comparacoes: %d", comparacoes);
            listar();
        } else {
                printf("\nPara fazer uma busca binaria o vetor precisa estar ordenado!");
            }
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

int main() {
    menu:
    int opcao_menu;
    do {
        printf("\n\n------------------------------------");
        printf("\n|  PLANO DE FUGA - CODIGO DA ILHA  |");
        printf("\n------------------------------------");
        printf("\nItens na Mochila: %d/10", contador);
        printf("\nStatus da Ordenacao por Nome: %s", ordenado ? "ORDENADO" : "NAO ORDENADO");
        printf("\n\n1. Adicionar Componente");
        printf("\n2. Descartar Componente");
        printf("\n3. Listar Componentes (Inventario)");
        printf("\n4. Organizar Mochila (Ordenar componentes)");
        printf("\n5. Buscar Componente (Busca binaria por nome)");
        printf("\n0. ATIVAR TORRE DE FUGA (Sair)");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao_menu);

        switch (opcao_menu) {
            case 1:
                adicionar();
                break;
            case 2:
                descartar();
                break;
            case 3:
                listar();
                break;
            case 4:
                int opcao_organizar;
                printf("\nComo desejar organizar os componentes?");
                printf("\n1. Por Nome");
                printf("\n2. Por Tipo");
                printf("\n3. Por Prioridade");
                printf("\n0. Cancelar");
                printf("\n\nEscolha uma opcao: ");
                scanf("%d", &opcao_organizar);

                switch (opcao_organizar) {
                    case 1:
                        bubbleSortNome();
                        break;
                    case 2:
                        insertionSortTipo();
                        break;
                    case 3:
                        selectionSortPrioridade();
                        break;
                    default:
                        goto menu;
                }
                break;
            case 5:
                buscarBinaria();
                break;
            case 0:
                break;
            default:
                goto menu;
        }
    } while (opcao_menu >= 1 && opcao_menu <= 5);

    return 0;
}