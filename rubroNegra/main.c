#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"

extern int rotacoesRB;

#define N 10000

int main() {

    Mapa *rb = cria();

    int valores[N];

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        valores[i] = rand() % 100000;
    }

    rotacoesRB = 0;

    clock_t inicio = clock();

    for (int i = 0; i < N; i++) {
        rb = insere(rb, valores[i], valores[i]);
    }

    clock_t fim = clock();

    double tempoInsercao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    inicio = clock();

    for (int i = 0; i < N; i++) {
        busca(rb, valores[i]);
    }

    fim = clock();

    double tempoBusca = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n===== RESULTADOS RUBRO-NEGRA =====\n");
    printf("Insercoes: %d\n", N);
    printf("Tempo insercao: %f segundos\n", tempoInsercao);
    printf("Tempo busca: %f segundos\n", tempoBusca);
    printf("Rotacoes: %d\n", rotacoesRB);

    destroi(rb);

    return 0;
}