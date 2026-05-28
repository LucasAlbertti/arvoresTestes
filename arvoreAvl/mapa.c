#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

int total_rotacoes_avl = 0; // Inicia o contador

struct smapa {
  int chave;
  int conteudo;
  short int bf;
  struct smapa* esq;
  struct smapa* dir;
};

static Mapa* cria_no(int c, int novodado);
static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu);
static Mapa* remove_avl2(Mapa *m, int chave, int *diminuiu);
static Mapa* corrige_dir(Mapa *m);
static Mapa* corrige_esq(Mapa *m);
static Mapa* rotaciona_dir(Mapa *m);
static Mapa* rotaciona_esq(Mapa *m);

static Mapa* cria_no(int c, int novodado) {
  Mapa *m = (Mapa*)malloc(sizeof(Mapa));
  if (m != NULL) {
    m->esq = m->dir = NULL;
    m->chave = c;
    m->conteudo = novodado;
    m->bf = 0;
  }
  return m;
}

Mapa* cria() {
  return NULL;
}

Mapa* insere(Mapa* m, int chave, int novodado) {
  int cresceu = 0;
  return insere2(m, chave, novodado, &cresceu);
}

Mapa* remove_avl(Mapa* m, int chave) {
  int diminuiu = 0;
  return remove_avl2(m, chave, &diminuiu);
}

static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu) {
  if (m == NULL) {
    m = cria_no(chave, novodado);
    *cresceu = 1;
  }
  else if (chave < m->chave) {
    m->esq = insere2(m->esq, chave, novodado, cresceu);
    if(*cresceu) {
      switch (m->bf) {
        case 1:
          m = corrige_esq(m);
          *cresceu = 0;
          break;
        case 0:
          m->bf = 1;
          break;
        case -1:
          m->bf = 0;
          *cresceu = 0;
          break;
      }
    }
  }
  else if (chave > m->chave) {
    m->dir = insere2(m->dir, chave, novodado, cresceu);
    if(*cresceu) {
      switch (m->bf) {
        case 1:
          m->bf = 0;
          *cresceu = 0;
          break;
        case 0:
          m->bf = -1;
          break;
        case -1:
          m = corrige_dir(m);
          *cresceu = 0;
          break;
      }
    }
  }
  return m;
}

static Mapa* remove_avl2(Mapa *m, int chave, int *diminuiu) {
  if (m == NULL) {
    *diminuiu = 0;
    return NULL;
  }
  if (chave < m->chave) {
    m->esq = remove_avl2(m->esq, chave, diminuiu);
    if (*diminuiu) {
      switch (m->bf) {
        case 1: m->bf = 0; break;
        case 0: m->bf = -1; *diminuiu = 0; break;
        case -1:
          m = corrige_dir(m);
          if (m->bf != 0) *diminuiu = 0;
          break;
      }
    }
  } else if (chave > m->chave) {
    m->dir = remove_avl2(m->dir, chave, diminuiu);
    if (*diminuiu) {
      switch (m->bf) {
        case -1: m->bf = 0; break;
        case 0: m->bf = 1; *diminuiu = 0; break;
        case 1:
          m = corrige_esq(m);
          if (m->bf != 0) *diminuiu = 0;
          break;
      }
    }
  } else {
    if (m->esq == NULL || m->dir == NULL) {
      Mapa *temp = m->esq ? m->esq : m->dir;
      free(m);
      *diminuiu = 1;
      return temp;
    } else {
      Mapa *temp = m->dir;
      while (temp->esq != NULL) temp = temp->esq;
      m->chave = temp->chave;
      m->conteudo = temp->conteudo;
      m->dir = remove_avl2(m->dir, temp->chave, diminuiu);
      if (*diminuiu) {
        switch (m->bf) {
          case -1: m->bf = 0; break;
          case 0: m->bf = 1; *diminuiu = 0; break;
          case 1:
            m = corrige_esq(m);
            if (m->bf != 0) *diminuiu = 0;
            break;
        }
      }
    }
  }
  return m;
}

static Mapa* corrige_esq(Mapa *m) {
  if (m->esq->bf == 1) {
    m->bf = m->esq->bf = 0;
    return rotaciona_dir(m);
  }
  else if (m->esq->bf == -1) {
    if (m->esq->dir->bf == 1) { m->bf = -1; m->esq->bf = 0; }
    else if (m->esq->dir->bf == -1) { m->bf = 0; m->esq->bf = 1; }
    else { m->bf = m->esq->bf = 0; }
    m->esq->dir->bf = 0;
    m->esq = rotaciona_esq(m->esq);
    return rotaciona_dir(m);
  }
  else if (m->esq->bf == 0) {
    m->bf = 1;
    m->esq->bf = -1;
    return rotaciona_dir(m);
  }
  return m;
}

static Mapa* corrige_dir(Mapa *m) {
  if (m->dir->bf == -1) {
    m->bf = m->dir->bf = 0;
    return rotaciona_esq(m);
  }
  else if (m->dir->bf == 1) {
    if (m->dir->esq->bf == -1) { m->bf = 1; m->dir->bf = 0; }
    else if (m->dir->esq->bf == 1) { m->bf = 0; m->dir->bf = -1; }
    else { m->bf = 0; m->dir->bf = 0; }
    m->dir->esq->bf = 0;
    m->dir = rotaciona_dir(m->dir);
    return rotaciona_esq(m);
  }
  else if (m->dir->bf == 0) {
    m->bf = -1;
    m->dir->bf = 1;
    return rotaciona_esq(m);
  }
  return m;
}

static Mapa* rotaciona_dir(Mapa *m) {
  total_rotacoes_avl++; // Contador
  Mapa* esq = m->esq;
  m->esq = esq->dir;
  esq->dir = m;
  return esq;
}

static Mapa* rotaciona_esq(Mapa *m) {
  total_rotacoes_avl++; // Contador
  Mapa* dir = m->dir;
  m->dir = dir->esq;
  dir->esq = m;
  return dir;
}

int busca (Mapa *m, int chave) {
  if (m == NULL) return -1;
  else if (m->chave == chave) return m->conteudo;
  else if (chave < m->chave) return busca(m->esq, chave);
  else if (chave > m->chave) return busca(m->dir, chave);
  else return -1;
}

void destroi (Mapa *m) {
  if (m != NULL) {
    destroi(m->esq);
    destroi(m->dir);
    free(m);
  }
}

int iguais (Mapa* m1, Mapa* m2) {
  if (m1==NULL) return (m2==NULL);
  if (m2==NULL) return 0;
  return (m1->chave == m2->chave) && iguais(m1->esq, m2->esq) && iguais(m1->dir, m2->dir);
}

int altura (Mapa* m) {
  if (m==NULL) return 0;
  return ((m->bf == -1) ? altura(m->dir) : altura(m->esq)) + 1;
}

static void mostra_mapa_int_aux(Mapa* m, int nivel) {
  if (m == NULL) return;
  for (int i = 0; i < nivel; i++) printf("  ");
  printf("%d:%d\n", m->chave, m->bf);
  mostra_mapa_int_aux(m->esq, nivel + 1);
  mostra_mapa_int_aux(m->dir, nivel + 1);
}

void mostra (Mapa* m) {
  printf("Arvore:\n");
  mostra_mapa_int_aux(m, 0);
  printf ("\n");
}