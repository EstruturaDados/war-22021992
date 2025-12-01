#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// -------------------------
// Estrutura de dados
// -------------------------
typedef struct {
    char nome[30];     // ex: "chip central"
    char tipo[20];     // ex: "controle", "suporte", "propulsão"
    int prioridade;    // 1 a 10
} Componente;

// -------------------------
// Funções auxiliares
// -------------------------

// Remove o '\n' do final lido por fgets
void limparNovaLinha(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') {
        s[n - 1] = '\0';
    }
}

// Mostra todos os componentes
void mostrarComponentes(Componente v[], int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n=== Componentes ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d) Nome: %-20s | Tipo: %-12s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// Copia vetor
void copiarVetor(Componente dest[], Componente src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// -------------------------
// Algoritmos de ordenação
// -------------------------

long bubbleSortNome(Componente v[], int n) {
    long comps = 0;
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comps++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
    return comps;
}

long insertionSortTipo(Componente v[], int n) {
    long comps = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            comps++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
    return comps;
}

long selectionSortPrioridade(Componente v[], int n) {
    long comps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (v[j].prioridade < v[minIdx].prioridade) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Componente tmp = v[i];
            v[i] = v[minIdx];
            v[minIdx] = tmp;
        }
    }
    return comps;
}

// -------------------------
// Busca binária
// -------------------------

int buscaBinariaPorNome(Componente v[], int n, const char *chave, long *comparacoes) {
    int ini = 0, fim = n - 1;
    *comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) return meio;
        if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// -------------------------
// Medição de tempo
// -------------------------

void medirOrdenacao(const char *rotulo,
                    long (*algoritmo)(Componente[], int),
                    Componente v[], int n) {
    clock_t inicio = clock();
    long comps = algoritmo(v, n);
    clock_t fim = clock();
    double segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[%s] Comparações: %ld | Tempo: %.6f s\n", rotulo, comps, segundos);
}

// -------------------------
// Programa principal
// -------------------------
int main() {
    setlocale(LC_ALL, "");

    Componente cadastro[20];
    Componente trabalho[20];
    int n = 0;
    int opcao;
    int ordenadoPorNome = 0;

    printf("Digite a quantidade de componentes (até 20): ");
    scanf("%d", &n);
    if (n < 0) n = 0;
    if (n > 20) n = 20;
    getchar();

    for (int i = 0; i < n; i++) {
        printf("\nCadastro do componente %d:\n", i + 1);

        printf("Nome: ");
        fgets(cadastro[i].nome, sizeof(cadastro[i].nome), stdin);
        limparNovaLinha(cadastro[i].nome);

        printf("Tipo: ");
        fgets(cadastro[i].tipo, sizeof(cadastro[i].tipo), stdin);
        limparNovaLinha(cadastro[i].tipo);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &cadastro[i].prioridade);
        getchar();
    }

    printf("\n=== Cadastro inicial ===\n");
    mostrarComponentes(cadastro, n);

    do {
        printf("\n=== Torre de fuga: ordenação e busca ===\n");
        printf("1 - Ordenar por NOME (Bubble Sort)\n");
        printf("2 - Ordenar por TIPO (Insertion Sort)\n");
        printf("3 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4 - Buscar BINÁRIA por NOME (após ordenar por nome)\n");
        printf("5 - Mostrar componentes atuais\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            copiarVetor(trabalho, cadastro, n);
            medirOrdenacao("Bubble Sort (nome)", bubbleSortNome, trabalho, n);
            mostrarComponentes(trabalho, n);
            ordenadoPorNome = 1;
        } else if (opcao == 2) {
            copiarVetor(trabalho, cadastro, n);
            medirOrdenacao("Insertion Sort (tipo)", insertionSortTipo, trabalho, n);
            mostrarComponentes(trabalho, n);
            ordenadoPorNome = 0;
        } else if (opcao == 3) {
            copiarVetor(trabalho, cadastro, n);
            medirOrdenacao("Selection Sort (prioridade)", selectionSortPrioridade, trabalho, n);
            mostrarComponentes(trabalho, n);
            ordenadoPorNome = 0;
        } else if (opcao == 4) {
            if (!ordenadoPorNome) {
                printf("\n[AVISO] Primeiro ordene por NOME (opção 1).\n");
            } else {
                char chave[30];
                printf("Digite o NOME do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                limparNovaLinha(chave);

                long compsBusca = 0;
                int idx = buscaBinariaPorNome(trabalho, n, chave, &compsBusca);
                if (idx >= 0) {
                    printf("\nComponente-chave encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                           trabalho[idx].nome, trabalho[idx].tipo, trabalho[idx].prioridade);
                    printf("Comparações na busca binária: %ld\n", compsBusca);
                    printf("\n[CONFIRMAÇÃO] Torre pode ser montada!\n");
                } else {
                    printf("\nComponente não encontrado. Comparações: %ld\n", compsBusca);
                }
            }
        } else if (opcao == 5) {
            if (ordenadoPorNome) {
                mostrarComponentes(trabalho, n);
            } else {
                mostrarComponentes(cadastro, n);
            }
        } else if (opcao == 0) {
            printf("\nEncerrando...\n");
        } else {
            printf("\n[ERRO] Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
