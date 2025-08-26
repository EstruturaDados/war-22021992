#include <stdio.h>
#include <string.h>

/*
🎯 Objetivo
Criar uma struct chamada Territorio.
Usar um vetor estático de 5 elementos para armazenar os territórios.
Cadastrar os dados de cada território: Nome, Cor do Exército, e Número de Tropas.
Exibir o estado atual do mapa.
*/

/*
⚙️ Funcionalidades
- Leitura de dados pelo terminal (fgets e scanf)
- Impressão organizada dos dados de todos os territórios
*/

/*
💡 Conceitos abordados
- struct
- Vetor estático
- Entrada/saída com scanf, fgets, e printf
*/

/* estrutura que guarda o territorio */
struct Territorio {
    char nome[30];   /* nome do territorio */
    char cor[20];    /* cor do exercito */
    int tropas;      /* numero de tropas */
};

int main() {
    struct Territorio territorios[5]; /* vetor com 5 territorios */
    int i; /* contador simples */

    /* aqui vai cadastrar os 5 territorios */
    for (i = 0; i < 5; i++) {
        printf("\nCadastro do territorio %d\n", i + 1);

        /* pega o nome do territorio */
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; /* tira o enter */

        /* pega a cor do exercito */
        printf("Cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0;

        /* pega a quantidade de tropas */
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); /* limpa o enter que sobra */
    }

    /* mostra tudo que foi digitado */
    printf("\n=== Estado do mapa ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0; /* fim do programa */
}