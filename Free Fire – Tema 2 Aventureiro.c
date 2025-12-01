#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// -------------------------
// Estruturas
// -------------------------

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// -------------------------
// Funções para VETOR
// -------------------------

void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= 10) {
        printf("\n[ERRO] Mochila cheia!\n");
        return;
    }
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[*qtd].nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[*qtd].tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    (*qtd)++;
    printf("\nItem inserido no vetor!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia.\n");
        return;
    }
    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);
    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("\nItem removido do vetor!\n");
            break;
        }
    }
    if (!encontrado) printf("\nItem não encontrado.\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia.\n");
        return;
    }
    printf("\n=== Itens no vetor ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char* nome) {
    int comparacoes = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado no vetor!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return i;
        }
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoes);
    return -1;
}

void ordenarVetor(Item mochila[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                Item temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("\nVetor ordenado por nome!\n");
}

int buscarBinariaVetor(Item mochila[], int qtd, char* nome) {
    int inicio = 0, fim = qtd - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\nItem encontrado com busca binária!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoes);
    return -1;
}

// -------------------------
// Funções para LISTA ENCADEADA
// -------------------------

No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("\n[ERRO] Falha de memória.\n");
        return inicio;
    }
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicio; // insere no início
    printf("\nItem inserido na lista!\n");
    return novo;
}

No* removerItemLista(No* inicio) {
    if (!inicio) {
        printf("\nLista vazia.\n");
        return inicio;
    }
    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);
    No* atual = inicio;
    No* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("\nItem removido da lista!\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("\nItem não encontrado.\n");
    return inicio;
}

void listarItensLista(No* inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia.\n");
        return;
    }
    printf("\n=== Itens na lista encadeada ===\n");
    No* atual = inicio;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista(No* inicio, char* nome) {
    int comparacoes = 0;
    No* atual = inicio;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado na lista!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("\nItem não encontrado. Comparações: %d\n", comparacoes);
}

void liberarLista(No* inicio) {
    No* atual = inicio;
    while (atual) {
        No* prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

// -------------------------
// Programa principal
// -------------------------

int main() {
    setlocale(LC_ALL, "");

    Item mochilaVetor[10];
    int qtd = 0;
    No* mochilaLista = NULL;

    int opcao, estrutura;
    char nomeBusca[30];
    int rodando = 1;

    while (rodando) {
        printf("\n=== Sistema de Mochila ===\n");
        printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n0 - Sair\n");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\n--- Mochila com Vetor ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n5 - Ordenar\n6 - Buscar Binária\n0 - Voltar\n");
                scanf("%d", &opcao);
                switch (opcao) {
                    case 1: inserirItemVetor(mochilaVetor, &qtd); break;
                    case 2: removerItemVetor(mochilaVetor, &qtd); break;
                    case 3: listarItensVetor(mochilaVetor, qtd); break;
                    case 4:
                        printf("\nDigite o nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarSequencialVetor(mochilaVetor, qtd, nomeBusca);
                        break;
                    case 5: ordenarVetor(mochilaVetor, qtd); break;
                    case 6:
                        printf("\nDigite o nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarBinariaVetor(mochilaVetor, qtd, nomeBusca);
                        break;
                    case 0: /* voltar */ break;
                    default: printf("\n[ERRO] Opção inválida.\n");
                }
            } while (opcao != 0);
        } else if (estrutura == 2) {
            do {
                printf("\n--- Mochila com Lista Encadeada ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n0 - Voltar\n");
                scanf("%d", &opcao);
                switch (opcao) {
                    case 1: mochilaLista = inserirItemLista(mochilaLista); break;
                    case 2: mochilaLista = removerItemLista(mochilaLista); break;
                    case 3: listarItensLista(mochilaLista); break;
                    case 4:
                        printf("\nDigite o nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        break;
                    case 0: /* voltar */ break;
                    default: printf("\n[ERRO] Opção inválida.\n");
                }
            } while (opcao != 0);
        } else if (estrutura == 0) {
            rodando = 0;
        } else {
            printf("\n[ERRO] Escolha inválida.\n");
        }
    }

    // Libera memória da lista antes de sair
    liberarLista(mochilaLista);

    printf("\nEncerrando... Até a próxima!\n");
    return 0;
}
