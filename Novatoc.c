#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> // Para corrigir acentuação no terminal

// Estrutura que guarda os dados de um território
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para mostrar os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Lista de Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    // Não pode atacar território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Você não pode atacar um território da mesma cor!\n");
        return;
    }

    // Precisa ter mais de 1 tropa para atacar
    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    // Simulação de dados (valores entre 1 e 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu!\n");
        // Defensor muda de dono
        strcpy(defensor->cor, atacante->cor);
        // Tropas do defensor passam a ser metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;
        // Atacante perde metade das tropas
        atacante->tropas /= 2;
    } else {
        printf("Resultado: O defensor resistiu!\n");
        // Atacante perde uma tropa
        atacante->tropas -= 1;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    setlocale(LC_ALL, ""); // Corrige acentuação
    srand(time(NULL));     // Inicializa aleatoriedade

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica para os territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, n);

    // Exibição inicial
    exibirTerritorios(mapa, n);

    // Escolha de ataque
    int idxAtacante, idxDefensor;
    printf("\nEscolha o território atacante (1 a %d): ", n);
    scanf("%d", &idxAtacante);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &idxDefensor);

    // Executa o ataque
    atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);

    // Exibição após ataque
    exibirTerritorios(mapa, n);

    // Liberação de memória
    liberarMemoria(mapa);

    return 0;
}
