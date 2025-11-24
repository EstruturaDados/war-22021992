#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> // Para corrigir acentuação no terminal

// Estrutura que guarda os dados de um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Estrutura que guarda os dados de um jogador
typedef struct {
    char nome[30];
    char cor[10];
    char* missao; // missão alocada dinamicamente
} Jogador;

// Função para cadastrar territórios
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
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== Mapa de Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s\n", i + 1, mapa[i].nome);
        printf("Cor: %s | Tropas: %d\n", mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula um ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Você não pode atacar um território da mesma cor!\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("Resultado: O defensor resistiu!\n");
        atacante->tropas -= 1;
    }
}

// Função para mostrar a missão do jogador
void exibirMissao(const char* nomeJogador, const char* missao) {
    printf("\nMissão de %s: %s\n", nomeJogador, missao);
}

// Função que sorteia uma missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função que verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    int countJogador = 0;
    int somaTropas = 0;
    int existeVermelho = 0;
    int existeAzul = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            countJogador++;
            somaTropas += mapa[i].tropas;
        }
        if (strcmp(mapa[i].cor, "vermelha") == 0 || strcmp(mapa[i].cor, "vermelho") == 0) {
            existeVermelho = 1;
        }
        if (strcmp(mapa[i].cor, "azul") == 0) {
            existeAzul = 1;
        }
    }

    if (strstr(missao, "Conquistar 3 territórios")) return countJogador >= 3;
    if (strstr(missao, "vermelha")) return existeVermelho == 0;
    if (strstr(missao, "20 tropas")) return somaTropas >= 20;
    if (strstr(missao, "azul")) return existeAzul == 0;
    if (strstr(missao, "Dominar metade do mapa")) return countJogador >= (tamanho / 2);

    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int qtdJogadores) {
    free(mapa);
    for (int i = 0; i < qtdJogadores; i++) {
        free(jogadores[i].missao);
    }
    free(jogadores);
}

int main() {
    setlocale(LC_ALL, ""); // Corrige acentuação
    srand(time(NULL));     // Inicializa aleatoriedade

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);

    int qtdJogadores;
    printf("\nDigite o número de jogadores: ");
    scanf("%d", &qtdJogadores);

    Jogador* jogadores = (Jogador*) calloc(qtdJogadores, sizeof(Jogador));

    // Missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territórios",
        "Eliminar todas as tropas da cor vermelha",
        "Ter ao menos 20 tropas somadas",
        "Eliminar todas as tropas da cor azul",
        "Dominar metade do mapa"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Cadastro dos jogadores
    for (int i = 0; i < qtdJogadores; i++) {
        printf("\nCadastro do jogador %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", jogadores[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", jogadores[i].cor);

        jogadores[i].missao = (char*) malloc(120 * sizeof(char));
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        exibirMissao(jogadores[i].nome, jogadores[i].missao);
    }

    // Loop de turnos
    int vencedor = -1;
    int continuar = 1;

    while (continuar && vencedor == -1) {
        for (int j = 0; j < qtdJogadores && vencedor == -1; j++) {
            printf("\n--- Turno de %s (%s) ---\n", jogadores[j].nome, jogadores[j].cor);
            exibirMapa(mapa, n);

            int idxAtacante, idxDefensor;
            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &idxAtacante);
            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &idxDefensor);

            if (idxAtacante >= 1 && idxAtacante <= n && idxDefensor >= 1 && idxDefensor <= n) {
                if (strcmp(mapa[idxAtacante - 1].cor, jogadores[j].cor) == 0) {
                    atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
                } else {
                    printf("[ERRO] Você só pode atacar a partir de um território da sua cor.\n");
                }
            } else {
                printf("[ERRO] Índices inválidos.\n");
            }

            if (verificarMissao(jogadores[j].missao, mapa, n, jogadores[j].cor)) {
                vencedor = j;
                printf("\n=== VITÓRIA! ===\n");
                printf("%s cumpriu a missão: %s\n", jogadores[j].nome, jogadores[j].missao);
            }
        }

        if (vencedor == -1) {
            printf("\nDeseja continuar jogando? (1 = sim, 0 = não): ");
            scanf("%d", &continuar);
        }
    }

    if (vencedor == -1) {
        printf("\nJogo encerrado sem vencedor.\n");
    }

    liberarMemoria(mapa, jogadores, qtdJogadores);
    return 0;
}
