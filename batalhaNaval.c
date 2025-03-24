#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TOTAL_NAVIOS 2

int naviosDestruidos = 0;

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // Navio (oculto para o jogador)
            } else if (tabuleiro[i][j] == 2) {
                printf("X "); // Navio atingido
            }
        }
        printf("\n");
    }
}

void posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;
    }
}

void posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;
    }
}

int verificarNavioDestruido(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    int partesRestantes = 0;

    // Verifica na horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (coluna + i < TAMANHO_TABULEIRO && tabuleiro[linha][coluna + i] == 3) {
            partesRestantes++;
        }
    }

    // Verifica na vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (linha + i < TAMANHO_TABULEIRO && tabuleiro[linha + i][coluna] == 3) {
            partesRestantes++;
        }
    }

    return partesRestantes == 0;
}

void atacar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 3) {
        tabuleiro[linha][coluna] = 2;
        printf("Acertou um navio!\n");

        if (verificarNavioDestruido(tabuleiro, linha, coluna)) {
            naviosDestruidos++;
            printf("Você destruiu um navio!\n");
        }
    } else if (tabuleiro[linha][coluna] == 0) {
        printf("Água! Tente novamente.\n");
    } else {
        printf("Essa posição já foi atacada.\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    int linha, coluna;
    int tentativas = 0;

    // Posicionar os navios
    posicionarNavioHorizontal(tabuleiro, 2, 3);
    posicionarNavioVertical(tabuleiro, 5, 5);

    while (naviosDestruidos < TOTAL_NAVIOS) {
        printf("\nTabuleiro atual:\n");
        exibirTabuleiro(tabuleiro);

        printf("\nNavios destruídos: %d/%d\n", naviosDestruidos, TOTAL_NAVIOS);

        // Solicitar coordenadas para ataque
        printf("\nEscolha uma linha (0-9): ");
        scanf("%d", &linha);
        printf("Escolha uma coluna (0-9): ");
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            printf("Coordenada inválida! Tente novamente.\n");
            continue;
        }

        // Realizar ataque
        atacar(tabuleiro, linha, coluna);
        tentativas++;
    }

    printf("\nParabéns! Você destruiu todos os navios em %d tentativas.\n", tentativas);
    
    return 0;
}