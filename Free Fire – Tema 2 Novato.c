#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Para corrigir acentuação no terminal

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (arma, munição, cura, etc.)
    int quantidade;    // Quantidade do item
} Item;

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= 10) {
        printf("\n[ERRO] Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\nCadastro do item %d:\n", *qtd + 1);
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", mochila[*qtd].nome);

    printf("Digite o tipo do item (arma, munição, cura, etc.): ");
    scanf(" %[^\n]", mochila[*qtd].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);

    (*qtd)++; // aumenta a quantidade de itens cadastrados
    printf("\nItem cadastrado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem(Item mochila[], int *qtd) {
    char nome[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            // desloca os itens para preencher o espaço
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            break;
        }
    }
    if (!encontrado) {
        printf("\n[ERRO] Item não encontrado na mochila.\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int qtd) {
    char nome[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\n[ERRO] Item não encontrado na mochila.\n");
    }
}

int main() {
    setlocale(LC_ALL, ""); // Corrige acentuação

    Item mochila[10]; // vetor estático com capacidade para 10 itens
    int qtd = 0;      // quantidade atual de itens na mochila
    int opcao;

    do {
        printf("\n=== Sistema de Inventário ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nEncerrando o sistema de inventário...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
