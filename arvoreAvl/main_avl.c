#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"

#define NUM_OP 10000

// Função auxiliar para embaralhar o array de chaves
void embaralha(int *array, int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    // Gerando array com 10.000 números únicos
    int *chaves = (int*)malloc(NUM_OP * sizeof(int));
    for (int i = 0; i < NUM_OP; i++) {
        chaves[i] = i + 1;
    }

    // Embaralha para que as inserções não sejam sequenciais
    embaralha(chaves, NUM_OP);

    printf("===================================================\n");
    printf("   TESTE AVL: %d INSERCOES E REMOCOES ALEATORIAS\n", NUM_OP);
    printf("===================================================\n\n");

    clock_t inicio, fim;
    double tempo_avl;

    Mapa *avl = cria();
    total_rotacoes_avl = 0; // Zera o contador de rotações

    inicio = clock();

    // Inserções AVL
    for (int i = 0; i < NUM_OP; i++) {
        avl = insere(avl, chaves[i], chaves[i] * 2);
    }

    // Re-embaralhar para a ordem de remoção ser diferente da inserção
    embaralha(chaves, NUM_OP);

    // Remoções AVL
    for (int i = 0; i < NUM_OP; i++) {
        avl = remove_avl(avl, chaves[i]);
    }

    fim = clock();
    tempo_avl = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo de execucao total (Insercao + Remocao): %f segundos\n", tempo_avl);
    printf("Numero total de rotacoes realizadas: %d\n\n", total_rotacoes_avl);

    destroi(avl);
    free(chaves);

    return 0;
}