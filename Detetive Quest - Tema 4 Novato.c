#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// -------------------------
// Estrutura da sala (nó da árvore)
// -------------------------
typedef struct Sala {
    char nome[50];           // Nome da sala
    struct Sala *esquerda;   // Caminho à esquerda
    struct Sala *direita;    // Caminho à direita
} Sala;

// -------------------------
// Função que cria uma sala dinamicamente
// -------------------------
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// -------------------------
// Função que permite explorar a mansão
// -------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na: %s\n", atual->nome);

        // Se não há caminhos, fim da exploração
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim da exploração! Não há mais caminhos.\n");
            break;
        }

        printf("Escolha o caminho: (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho à esquerda!\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho à direita!\n");
            }
        } else if (escolha == 's') {
