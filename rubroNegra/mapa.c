#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

struct smapa {
    int chave;
    int dado;
    char vermelho; // 1 = vermelho, 0 = preto
    struct smapa* esq;
    struct smapa* dir;
};

typedef enum {OK, RED, LEFTRED, RIGHTRED} Result;

int rotacoesRB = 0;

static Mapa* cria_no(int chave, int dado) {
    Mapa* n = (Mapa*) malloc(sizeof(Mapa));
    if (n) {
        n->chave = chave;
        n->dado = dado;
        n->vermelho = 1; // novo nó sempre vermelho
        n->esq = n->dir = NULL;
    }
    return n;
}

Mapa* cria(void) {
    return NULL;
}

void destroi(Mapa* m) {
    if (m) {
        destroi(m->esq);
        destroi(m->dir);
        free(m);
    }
}

Mapa* busca(Mapa* m, int chave) {
    if (!m) return NULL;

    if (chave == m->chave) return m;
    if (chave < m->chave) return busca(m->esq, chave);
    return busca(m->dir, chave);
}

static Mapa* rotaciona_dir(Mapa* m) {
    rotacoesRB++;

    Mapa* x = m->esq;
    m->esq = x->dir;
    x->dir = m;
    return x;
}

static Mapa* rotaciona_esq(Mapa* m) {
    rotacoesRB++;

    Mapa* x = m->dir;
    m->dir = x->esq;
    x->esq = m;
    return x;
}

static Mapa* trocaCores(Mapa* m) {
    char cor = m->vermelho;
    m->vermelho = !cor;

    if (m->esq) m->esq->vermelho = cor;
    if (m->dir) m->dir->vermelho = cor;

    return m;
}

static Mapa* corrigeEsq(Mapa* m, Result* status) {
    switch (*status) {
        case OK:
            break;

        case RED:
            if (m->vermelho) *status = LEFTRED;
            else *status = OK;
            break;

        case LEFTRED:
            if (!m->dir || !m->dir->vermelho) {
                m = rotaciona_dir(m);
                m = trocaCores(m);
                *status = OK;
            } else {
                m = trocaCores(m);
                *status = RED;
            }
            break;

        case RIGHTRED:
            if (!m->dir || !m->dir->vermelho) {
                m->esq = rotaciona_esq(m->esq);
                m = rotaciona_dir(m);
                m = trocaCores(m);
                *status = OK;
            } else {
                m = trocaCores(m);
                *status = RED;
            }
            break;
    }
    return m;
}

static Mapa* corrigeDir(Mapa* m, Result* status) {
    switch (*status) {
        case OK:
            break;

        case RED:
            if (m->vermelho) *status = RIGHTRED;
            else *status = OK;
            break;

        case RIGHTRED:
            if (!m->esq || !m->esq->vermelho) {
                m = rotaciona_esq(m);
                m = trocaCores(m);
                *status = OK;
            } else {
                m = trocaCores(m);
                *status = RED;
            }
            break;

        case LEFTRED:
            if (!m->esq || !m->esq->vermelho) {
                m->dir = rotaciona_dir(m->dir);
                m = rotaciona_esq(m);
                m = trocaCores(m);
                *status = OK;
            } else {
                m = trocaCores(m);
                *status = RED;
            }
            break;
    }
    return m;
}

static Mapa* insereRec(Mapa* m, int chave, int dado, Result* status) {
    if (!m) {
        *status = RED;
        return cria_no(chave, dado);
    }

    if (chave < m->chave) {
        m->esq = insereRec(m->esq, chave, dado, status);
        m = corrigeEsq(m, status);
    }
    else if (chave > m->chave) {
        m->dir = insereRec(m->dir, chave, dado, status);
        m = corrigeDir(m, status);
    }

    return m;
}

Mapa* insere(Mapa* m, int chave, int dado) {
    Result status;

    m = insereRec(m, chave, dado, &status);

    // raiz sempre preta
    if (m) m->vermelho = 0;

    return m;
}