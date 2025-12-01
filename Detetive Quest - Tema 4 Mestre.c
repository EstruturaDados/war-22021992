#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// -------------------------
// Estruturas de dados
// -------------------------

// Nó da árvore da mansão (árvore binária fixa)
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    char pista[100];         // Pista associada (pode ser vazia)
    struct Sala *esquerda;   // Caminho à esquerda
    struct Sala *direita;    // Caminho à direita
} Sala;

// Nó da árvore de pistas (BST)
typedef struct PistaNode {
    char pista[100];         // Conteúdo da pista
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// -------------------------
// Utilidades
// -------------------------

// Verifica se a pista já existe na BST (para evitar duplicatas)
int existePista(PistaNode *raiz, const char *pista) {
    if (!raiz) return 0;
    int cmp = strcmp(pista, raiz->pista);
    if (cmp == 0) return 1;
    if (cmp < 0) return existePista(raiz->esquerda, pista);
    return existePista(raiz->direita, pista);
}

// -------------------------
// Criação de nós
// -------------------------

// criarSala: cria dinamicamente um cômodo com nome e pista
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        printf("[ERRO] Falha ao alocar memória para Sala.\n");
        exit(1);
    }
    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';

    if (pista) {
        strncpy(nova->pista, pista, sizeof(nova->pista) - 1);
        nova->pista[sizeof(nova->pista) - 1] = '\0';
    } else {
        nova->pista[0] = '\0';
    }

    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// inserirPista: insere uma pista na BST em ordem alfabética
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (!pista || pista[0] == '\0') return raiz; // ignora pistas vazias

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        if (!novo) {
            printf("[ERRO] Falha ao alocar memória para PistaNode.\n");
            exit(1);
        }
        strncpy(novo->pista, pista, sizeof(novo->pista) - 1);
        novo->pista[sizeof(novo->pista) - 1] = '\0';
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // Se igual, não insere duplicata (mantém um único registro)
    return raiz;
}

// -------------------------
// Exibição
// -------------------------

// exibirPistas: imprime pistas da BST em ordem alfabética (in-order)
void exibirPistas(PistaNode *raiz) {
    if (raiz) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// -------------------------
// Exploração da mansão com diário e contador
// -------------------------

// explorarSalasComPistas: navega pela árvore binária, coleta pistas, registra caminho e conta pistas
void explorarSalasComPistas(Sala *atual, PistaNode **pistasBST, char caminho[][50], int *nSalas, int *totalPistas) {
    char escolha;

    while (atual) {
        // Registro do cômodo visitado (diário)
        strncpy(caminho[*nSalas], atual->nome, 49);
        caminho[*nSalas][49] = '\0';
        (*nSalas)++;

        printf("\nVocê está na: %s\n", atual->nome);

        // Coleta de pista (evitando duplicatas)
        if (atual->pista[0] != '\0') {
            if (!existePista(*pistasBST, atual->pista)) {
                printf("Pista encontrada: %s\n", atual->pista);
                *pistasBST = inserirPista(*pistasBST, atual->pista);
                (*totalPistas)++;
            } else {
                printf("Pista repetida ignorada: %s\n", atual->pista);
            }
        } else {
            printf("Nenhuma pista neste cômodo.\n");
        }

        printf("Escolha o caminho: (e = esquerda, d = direita, s = sair): ");
        if (scanf(" %c", &escolha) != 1) {
            printf("\n[ERRO] Entrada inválida. Encerrando exploração.\n");
            break;
        }

        if (escolha == 'e') {
            if (atual->esquerda) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho à esquerda.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita) {
                atual = atual->direita;
            } else {
                printf("Não há caminho à direita.\n");
            }
        } else if (escolha == 's') {
            printf("Você decidiu encerrar a exploração.\n");
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }
}

// -------------------------
// Relatórios finais
// -------------------------

void exibirDiarioCaminho(char caminho[][50], int nSalas) {
    if (nSalas == 0) {
        printf("\nNenhuma sala visitada.\n");
        return;
    }
    printf("\n=== Diário de exploração (trajeto) ===\n");
    for (int i = 0; i < nSalas; i++) {
        printf("%2d) %s\n", i + 1, caminho[i]);
    }
}

// -------------------------
// Liberação (boa prática)
// -------------------------

// liberarMansao: libera recursivamente a árvore das salas
void liberarMansao(Sala *raiz) {
    if (!raiz) return;
    liberarMansao(raiz->esquerda);
    liberarMansao(raiz->direita);
    free(raiz);
}

// liberarPistas: libera recursivamente a BST das pistas
void liberarPistas(PistaNode *raiz) {
    if (!raiz) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

// -------------------------
// Programa principal
// -------------------------
int main() {
    setlocale(LC_ALL, "");

    // Montagem do mapa fixo da mansão (árvore binária)
    Sala *hall        = criarSala("Hall de Entrada", "Pegada misteriosa no tapete");
    Sala *salaEstar   = criarSala("Sala de Estar", "Copo quebrado no chão");
    Sala *cozinha     = criarSala("Cozinha", "Faca suja de sangue");
    Sala *biblioteca  = criarSala("Biblioteca", "Livro antigo aberto em página suspeita");
    Sala *jardim      = criarSala("Jardim", "Pegadas levando ao portão");
    Sala *quarto      = criarSala("Quarto", "Carta rasgada em pedaços");
    Sala *porao       = criarSala("Porão", "Caixa trancada com cadeado");

    // Conexões (estrutura fixa)
    hall->esquerda = salaEstar;
    hall->direita  = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita  = jardim;

    cozinha->esquerda = quarto;
    cozinha->direita  = porao;

    // BST de pistas inicialmente vazia
    PistaNode *pistas = NULL;

    // Diário de exploração (trajeto) e contador de pistas
    char caminho[100][50]; // até 100 salas visitadas no diário
    int nSalas = 0;
    int totalPistas = 0;

    // Início da exploração
    printf("=== Detective Quest: Coleta de Pistas (Etapa 3) ===\n");
    explorarSalasComPistas(hall, &pistas, caminho, &nSalas, &totalPistas);

    // Exibir relatórios
    printf("\n=== Pistas coletadas (ordem alfabética) ===\n");
    if (pistas) {
        exibirPistas(pistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }

    printf("\nTotal de pistas coletadas: %d\n", totalPistas);
    exibirDiarioCaminho(caminho, nSalas);

    // Liberação da memória (boa prática)
    liberarMansao(hall);
    liberarPistas(pistas);

    return 0;
}
