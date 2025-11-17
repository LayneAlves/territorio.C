/*
    Projeto: WAR estruturado - Interatividade e Ataque
    Autor: Layne Alves da Silva 
    Objetivo: Adicionar a funcionalidade de ataque entre territórios,
              usando ponteiros e alocação dinâmica.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//FUNÇÕES 

// Cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("= Cadastro do território %d =\n", i + 1);

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
        printf("\n");
    }
}

// Exibir territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n= Dados dos Territórios =\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simular ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1; // valor entre 1 e 6
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 %s (dado: %d) ataca %s (dado: %d)\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("⚔️  %s conquistou o território %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas vão pro novo território
    } else {
        printf("💀 %s perdeu uma tropa!\n", atacante->nome);
        atacante->tropas--;
    }
}

// Liberar memória alocada
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

//FUNÇAO PRINCIPAL
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(NULL)); // garante números aleatórios diferentes a cada execução

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);
    getchar(); // limpa o '\n'

    // Alocação dinâmica dos territórios
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    // Cadastra os territórios
    cadastrarTerritorios(mapa, n);

    // Mostra os territórios
    exibirTerritorios(mapa, n);

    // Escolha de ataque
    int iAtacante, iDefensor;
    printf("\nEscolha o índice do território ATACANTE: ");
    scanf("%d", &iAtacante);
    printf("Escolha o índice do território DEFENSOR: ");
    scanf("%d", &iDefensor);

    // Validação simples
    if (iAtacante < 0 || iAtacante >= n || iDefensor < 0 || iDefensor >= n) {
        printf("Índices inválidos!\n");
    } else if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
        printf("❌ Você não pode atacar um território da mesma cor!\n");
    } else {
        atacar(&mapa[iAtacante], &mapa[iDefensor]);
    }

    // Mostra situação final
    exibirTerritorios(mapa, n);

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}
