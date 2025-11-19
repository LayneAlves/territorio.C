/*
    Projeto: Nivel Mestre
    Autor: Layne Alves da Silva
    Objetivo: Demonstrar o uso de structs, ponteiros e alocação dinâmica em C,
              implementando ataques entre territórios e missões estratégicas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

// - Struct -
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -Funções -

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n= Cadastro do território %d =\n", i + 1);

        printf("Digite o nome do território: ");
        fflush(stdin);
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o '\n'
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n= Situação dos Territórios =\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para simular ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 %s (dado: %d) ataca %s (dado: %d)\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("⚔️  %s conquistou o território %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("💀 %s perdeu uma tropa!\n", atacante->nome);
        atacante->tropas--;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}

// -Missões Estratégicas -
#define TOTAL_MISSOES 5

char *missoes[TOTAL_MISSOES] = {
    "Conquistar 3 territorios seguidos",
    "Ter 10 ou mais tropas em um territorio",
    "Controlar todos os territorios de uma cor",
    "Conquistar territorios em posicoes pares"
};

// Atribuir missão aleatória ao jogador
void atribuirMissao(char **missaoDestino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *missaoDestino = (char *) malloc(strlen(missoes[indice]) + 1);
    if (*missaoDestino != NULL) {
        strcpy(*missaoDestino, missoes[indice]);
    }
}

// Exibir missão do jogador
void exibirMissao(char *missao) {
    printf("\n🎯 Sua missão estratégica: %s\n", missao);
}

// Verificar se a missão foi cumprida (lógica simples inicial)
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    if (strcmp(missao, "Ter 10 ou mais tropas em um territorio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10) return 1;
        }
    } 
  
    return 0;
}

// - Main -
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    srand(time(NULL));

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);
    getchar();

    // Alocação dinâmica de territórios
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Atribuir missão ao jogador
    char *missaoJogador = NULL;
    atribuirMissao(&missaoJogador, missoes, TOTAL_MISSOES);
    exibirMissao(missaoJogador);

    exibirTerritorios(mapa, n);

    // Exemplo de ataque
    int iAtacante, iDefensor;
    printf("\nEscolha o indice do territorio ATACANTE: ");
    scanf("%d", &iAtacante);
    printf("Escolha o indice do territorio DEFENSOR: ");
    scanf("%d", &iDefensor);

    if (iAtacante >= 0 && iAtacante < n && iDefensor >= 0 && iDefensor < n) {
        if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) != 0) {
            atacar(&mapa[iAtacante], &mapa[iDefensor]);
        } else {
            printf("❌ Nao pode atacar um territorio da mesma cor!\n");
        }
    }

    // Verificação da missão
    if (verificarMissao(missaoJogador, mapa, n)) {
        printf("\n🏆 Missao cumprida! Voce venceu!\n");
    } else {
        printf("\nMissao ainda nao cumprida.\n");
    }

    exibirTerritorios(mapa, n);

    // Liberar memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}
