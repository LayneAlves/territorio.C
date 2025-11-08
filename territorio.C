/*
    Projeto: Cadastro de Territórios
    Autor: Layne Alves da Silva 
    Objetivo: Demonstrar o uso de structs em C para armazenar múltiplos registros.
*/

#include <stdio.h>   // Biblioteca para entrada e saída (printf, scanf)
#include <string.h>  // Biblioteca para manipular strings
#include <locale.h>  // Biblioteca para configurar idioma (acentos)
#ifdef _WIN32
#include <windows.h> // Biblioteca para SetConsoleOutputCP (apenas no Windows)
#endif

// Definindo a estrutura "Territorio"
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

int main() {
    // Configuração de idioma e caracteres
    setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Declara um vetor de 5 elementos do tipo Territorio
    Territorio territorios[5];

    // Laço para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("===== Cadastro do território %d =====\n", i + 1);

        // Lendo o nome
        printf("Digite o nome do território: ");
        fflush(stdin); // limpa buffer (pode ser ignorado em Linux)
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove '\n'

        // Lendo a cor
        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Lendo o número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // consome o '\n' deixado pelo scanf

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n===== Dados dos Territórios Cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
