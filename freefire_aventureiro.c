#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[10];

typedef struct No{
    Item dados;
    struct No *proximo;
} No;

No *inicio = NULL;

int contador = 0;
bool ordenado = false;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listarVetor() {
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

void adicionarVetor() {
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
        listarVetor();
    } else {
        printf("\n\nA mochila ja contem o limite de 10 itens!");
    }
}

void removerVetor() {
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
            printf("\n\nNenhum item foi removido!");
        } else {
            memcpy(mochila, temp, sizeof(temp)); //copiar o array temporário de volta para a mochila
            contador--;
            listarVetor();
        }
    } else {
        printf("\n\nA mochila ja esta vazia!");
    }
}

void buscarVetorSequencial() {
    if (contador > 0) {
        char nome[30];
        printf("\n--- Buscar Item (Sequencial) ---");
        printf("\nNome: ");
        scanf("%s",nome);
        int comparacoes = 0, posicao = -1;
        for (int i = 0; i < contador; i++){
            comparacoes++;
            if (strcmp(mochila[i].nome, nome) == 0) {
                posicao = i;
                break;
            }
        }
        if (posicao >= 0) {
            printf("\nItem encontrado na posição %d do vetor, ou seja, no indice %d", posicao + 1, posicao);
        } else {
            printf("\nItem nao encontrado!");
        }
        printf("\nTotal de comparacoes: %d", comparacoes);
        listarVetor();
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

void buscarVetorBinaria() {
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
            listarVetor();
        } else {
                printf("\nPara fazer uma busca binaria o vetor precisa estar ordenado!");
            }
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

void ordenarVetor() {
    if (contador > 1) {
        for (int i = 0; i < contador - 1; i++) {
            for (int j = 0; j < contador - 1 - i; j++) { //sempre ignorar o elementos que já estão na sua posição final
                if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                    Item temp = mochila[j];
                    mochila[j] = mochila[j + 1];
                    mochila[j + 1] = temp;
                }
            }
        }
        printf("\nVetor ordenado com sucesso!");
        listarVetor();
    } else {
        printf("\n\nA mochila precisa ter ao menos 2 itens!");
    }
}

void listarLista() {
    if (contador > 0) {
        printf("\n\n                    ITENS NA MOCHILA (%d/10)", contador);
        printf("\n------------------------------------------------------------------");
        printf("\nNOME                           | TIPO                 | QUANTIDADE");
        printf("\n------------------------------------------------------------------");
        No *aux = inicio;
        while (aux != NULL) {
            printf("\n%-30s | %-20s | %d", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            printf("\n------------------------------------------------------------------");
            aux = aux->proximo;
        }
        limparBuffer();
        printf("\n\nPressione ENTER para continuar...");
        getchar();
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

void adicionarLista() {
    if (contador < 10) {
        No *novo = (No*) malloc(sizeof(No));
        printf("\n--- Adicionar Item ---");
        printf("\nNome: ");
        scanf("%s", novo->dados.nome);
        printf("Tipo: ");
        scanf("%s", novo->dados.tipo);
        printf("Quantidade: ");
        scanf("%d", &novo->dados.quantidade);
        novo->proximo = NULL;
        if (inicio == NULL) {
            inicio = novo;
        } else {
            No *aux = inicio;
            while (aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
        printf("\nItem \"%s\" adicionado com sucesso!", novo->dados.nome);
        contador++;        
        listarLista();
    } else {
        printf("\n\nA mochila ja contem o limite de 10 itens!");
    }
}

void removerLista() {
    if (contador > 0) {
        char nome[30];
        printf("\n--- Remover Item ---");
        printf("\nNome: ");
        scanf("%s", nome);
        No *atual = inicio;
        No *anterior = NULL;
        while (atual != NULL && strcmp(atual->dados.nome,nome) != 0) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL) {
            printf("\n\nNenhum item foi removido!");
        } else {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            contador--;
            listarLista();
        }
    } else {
        printf("\n\nA mochila ja esta vazia!");
    }
}

void buscarListaSequencial() {
    if (contador > 0) {
        char nome[30];
        printf("\n--- Buscar Item (Sequencial) ---");
        printf("\nNome: ");
        scanf("%s",nome);
        int comparacoes = 0;
        No *aux = inicio;
        while (aux != NULL) {
            comparacoes++;
            if (strcmp(aux->dados.nome,nome) == 0) {
                printf("\nItem encontrado na posição %d da lista, ou seja, no indice %d", comparacoes + 1, comparacoes);
                goto finalizar;
            }
            aux = aux->proximo;
        }
        printf("\nItem nao encontrado!");
        finalizar:
        printf("\nTotal de comparacoes: %d", comparacoes);
        listarLista();
    } else {
        printf("\n\nA mochila esta vazia!");
    }
}

int main() {
    menu:
    int opcao_menu = -1;
    do {
        if (opcao_menu < 0) {
            printf("\n\n-----------------------------------------------");
            printf("\n|  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  |");
            printf("\n-----------------------------------------------");
            printf("\nItens na mochila: %d/10", contador);
            printf("\n\n1. Usando Vetor");
            printf("\n2. Usando Lista Encadeada");
            printf("\n0. Sair");
            printf("\n\nEscolha uma opcao: ");
            scanf("%d", &opcao_menu);
        }
        if (opcao_menu == 1) {

            int opcao_vetor;
            printf("\n\n1. Adicionar Item");
            printf("\n2. Remover Item");
            printf("\n3. Listar Itens");
            printf("\n4. Buscar Item (Sequencial)");
            printf("\n5. Buscar Item (Binaria)");
            printf("\n6. Ordenar  Itens");
            printf("\n0. Voltar");
            printf("\n\nEscolha uma opcao: ");
            scanf("%d", &opcao_vetor);
            
            switch (opcao_vetor) {
                case 1:
                    adicionarVetor();
                    break;
                case 2:
                    removerVetor();
                    break;
                case 3:
                    listarVetor();
                    break;
                case 4:
                    buscarVetorSequencial();
                    break;
                case 5:
                    buscarVetorBinaria();
                    break;
                case 6:
                    ordenarVetor();
                    break;
                case 0:
                    goto menu;
                default:
                    opcao_menu = -1;
            }

        } else if (opcao_menu == 2) {

            int opcao_lista;
            printf("\n\n1. Adicionar Item");
            printf("\n2. Remover Item");
            printf("\n3. Listar Itens");
            printf("\n4. Buscar Item (Sequencial)");
            printf("\n0. Voltar");
            printf("\n\nEscolha uma opcao: ");
            scanf("%d", &opcao_lista);
            
            switch (opcao_lista) {
                case 1:
                    adicionarLista();
                    break;
                case 2:
                    removerLista();
                    break;
                case 3:
                    listarLista();
                    break;
                case 4:
                    buscarListaSequencial();
                    break;
                case 0:
                    goto menu;
                default:
                    opcao_menu = -1;
            }
        }

    } while (opcao_menu >= 1 && opcao_menu <= 2);

    free(inicio);

    return 0;
}