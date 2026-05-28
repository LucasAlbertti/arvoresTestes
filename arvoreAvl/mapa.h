#ifndef MAPA_H
#define MAPA_H

typedef struct smapa Mapa;

Mapa* cria();
Mapa* insere(Mapa* m, int chave, int novodado);
Mapa* remove_avl(Mapa* m, int chave);
int busca(Mapa *m, int chave);
void destroi(Mapa *m);
int iguais(Mapa* m1, Mapa* m2);
int altura(Mapa* m);
void mostra(Mapa* m);

extern int total_rotacoes_avl;

#endif