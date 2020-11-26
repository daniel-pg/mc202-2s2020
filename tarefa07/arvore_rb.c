/**
 * Daniel Paulo Garcia © 2020
 *
 * arvore_rb.c
 *
 * Descrição: Implementa as funções do módulo arvore_rb.h
 * Os algoritmos usados aqui foram baseados (i.e. copiados descaradamente hehe) no livro "Introduction to Algorithms",
 * de Thomas H. Cormen.
 */

#include <stdlib.h>

#include "arvore_rb.h"

// Funções auxiliares
void arvore_rotacao_esquerda(arvore_rb *t, nodo_rb *x);
void arvore_rotacao_direita(arvore_rb *t, nodo_rb *y);
void arvore_consertar_insercao(arvore_rb *t, nodo_rb *nd);
void arvore_transplantar(arvore_rb *t, nodo_rb *u, nodo_rb *v);
void arvore_consertar_delecao(arvore_rb *t, nodo_rb *nd);

// Implementações de funções
nodo_rb * __busca_arvore_recursivo(nodo_rb *raiz, const void *k, int (*cmp_chaves) (const void*, const void*));
nodo_rb * __busca_arvore_iterativo(arvore_rb *t, const void *k);
nodo_rb * __arvore_minimo(nodo_rb *raiz);
nodo_rb * __arvore_maximo(nodo_rb *raiz);
void __percorrer_preordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg);
void __percorrer_inordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg);
void __percorrer_posordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg);

// Nó nulo (o T.nil descrito no livro do Cormen). Alocado globalmente (o professor vai me matar agora).
nodo_rb arvore_nodo_nulo = {
        ARVORE_NULL,    /* Nó esquerdo */
        ARVORE_NULL,    /* Nó direito */
        ARVORE_NULL,    /* Nó pai */
        NULL,           /* Chave */
        NEGRO           /* Cor do nó */
};

arvore_rb * arvore_criar(int (*cmp_chaves) (const void*, const void*))
{
    arvore_rb *nova_arvore;

    nova_arvore = malloc(sizeof(*nova_arvore));
    if (!nova_arvore)
        return NULL;
    else
        arvore_inicializar(nova_arvore, cmp_chaves);

    return nova_arvore;
}

void arvore_inicializar(arvore_rb *t, int (*cmp_chaves) (const void*, const void*))
{
    t->raiz = ARVORE_NULL;
    t->cmp_chaves = cmp_chaves;
    t->tmh_arvore = 0;
}

/*
 * Diagrama das rotações de uma árvore.
 * Da esquerda para a direita: rotação à esquerda
 * Da direita para a esquerda: rotação à direita
 *
 *      X               Y
 *    ┌─┴─┐           ┌─┴─┐
 *    α   Y     ⇔     X   γ
 *      ┌─┴─┐       ┌─┴─┐
 *      β   γ       α   β
 */

// Rotação à esquerda
void arvore_rotacao_esquerda(arvore_rb *t, nodo_rb *x)
{
    nodo_rb *y = x->dir;    // Obtém nó y
    x->dir = y->esq;
    if (y->esq != ARVORE_NULL) y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == ARVORE_NULL)
        t->raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

// Rotação à direita
void arvore_rotacao_direita(arvore_rb *t, nodo_rb *y)
{
    nodo_rb *x = y->esq;    // Obtém nó x
    y->esq = x->dir;
    if (x->dir != ARVORE_NULL) x->dir->pai = y;

    x->pai = y->pai;
    if (y->pai == ARVORE_NULL)
        t->raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;

    x->dir = y;
    y->pai = x;
}

void arvore_consertar_insercao(arvore_rb *t, nodo_rb *nd)
{
    nodo_rb *tio;

    while (nd->pai->cor == RUBRO)
    {
        if (nd->pai == nd->pai->pai->esq)
        {
            tio = nd->pai->pai->dir;

            if (tio->cor == RUBRO) {
                nd->pai->cor = NEGRO;
                tio->cor = NEGRO;
                nd->pai->pai->cor = RUBRO;
                nd = nd->pai->pai;
            } else {
                if (nd == nd->pai->dir) {
                    nd = nd->pai;
                    arvore_rotacao_esquerda(t, nd);
                }

                nd->pai->cor = NEGRO;
                nd->pai->pai->cor = RUBRO;
                arvore_rotacao_direita(t, nd->pai->pai);
            }

        } else {
            /* Mesmíssima coisa de antes, basta trocar todos os "esq" e "dir" de lugar */
            tio = nd->pai->pai->esq;

            if (tio->cor == RUBRO) {
                nd->pai->cor = NEGRO;
                tio->cor = NEGRO;
                nd->pai->pai->cor = RUBRO;
                nd = nd->pai->pai;
            } else {
                if (nd == nd->pai->esq) {
                    nd = nd->pai;
                    arvore_rotacao_direita(t, nd);
                }

                nd->pai->cor = NEGRO;
                nd->pai->pai->cor = RUBRO;
                arvore_rotacao_esquerda(t, nd->pai->pai);
            }
        }
    }

    t->raiz->cor = NEGRO;
}

nodo_rb * arvore_inserir(arvore_rb *t, nodo_rb *nd)
{
    nodo_rb *x, *pai;
    int cmp;

    // Iniciamos pela raíz da árvore
    pai = ARVORE_NULL;    // Nó pai
    x = t->raiz;        // Nó auxiliar

    // Executa o programa do ratinho pra fazer o teste de DNA e encontrar o novo pai do nó a ser inserido.
    while (x != ARVORE_NULL)
    {
        cmp = t->cmp_chaves(nd->chave, x->chave);

        // Se encontrarmos uma chave duplicada, retorna NULL e cancela a inserção.
        if (cmp == 0)
            return NULL;

        pai = x;
        if (cmp < 0)
            x = x->esq;
        else
            x = x->dir;
    }

    nd->pai = pai;

    // Insere nó na árvore
    if (pai == ARVORE_NULL)
        t->raiz = nd;
    else if (t->cmp_chaves(nd->chave, pai->chave) < 0)
        pai->esq = nd;
    else
        pai->dir = nd;

    // Inicializa nó
    nd->esq = ARVORE_NULL;
    nd->dir = ARVORE_NULL;
    nd->cor = RUBRO;

    // Restaura propriedades da árvore rubro-negra
    arvore_consertar_insercao(t, nd);
    t->tmh_arvore++;
    return nd;
}

void arvore_transplantar(arvore_rb *t, nodo_rb *u, nodo_rb *v)
{
    if (u->pai == ARVORE_NULL)
        t->raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;

    v->pai = u->pai;
}

void arvore_consertar_delecao(arvore_rb *t, nodo_rb *x)
{
    nodo_rb *w;

    while (x != ARVORE_NULL && x->cor == NEGRO)
    {
        if (x == x->pai->esq) {
            w = x->pai->dir;

            // Caso 1
            if (w->cor == RUBRO) {
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                arvore_rotacao_esquerda(t, x->pai);
                w = x->pai->dir;
            }

            // Caso 2
            if (w->esq->cor == NEGRO && w->dir->cor == NEGRO) {
                w->cor = RUBRO;
                x = x->pai;
            } else {
                // Caso 3
                if (w->dir->cor == NEGRO) {
                    w->esq->cor = NEGRO;
                    w->cor = RUBRO;
                    arvore_rotacao_direita(t, w);
                    w = x->pai->dir;
                }

                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->dir->cor = NEGRO;
                arvore_rotacao_esquerda(t, x->pai);
                x = t->raiz;
            }

        } else {
            /* Mesmíssima coisa de antes, basta trocar todos os "esq" e "dir" de lugar */
            w = x->pai->esq;

            // Caso 1
            if (w->cor == RUBRO) {
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                arvore_rotacao_direita(t, x->pai);
                w = x->pai->esq;
            }

            // Caso 2
            if (w->dir->cor == NEGRO && w->esq->cor == NEGRO) {
                w->cor = RUBRO;
                x = x->pai;
            } else {
                // Caso 3
                if (w->esq->cor == NEGRO) {
                    w->dir->cor = NEGRO;
                    w->cor = RUBRO;
                    arvore_rotacao_esquerda(t, w);
                    w = x->pai->esq;
                }

                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->esq->cor = NEGRO;
                arvore_rotacao_direita(t, x->pai);
                x = t->raiz;
            }
        }
    }

    x->cor = NEGRO;
}

nodo_rb * arvore_deletar_nodo(arvore_rb *t, nodo_rb *nd)
{
    nodo_rb *x, *y;
    enum cor_no cor_orig_y;

    y = nd;
    cor_orig_y = y->cor;

    if (nd->esq == ARVORE_NULL) {
        x = nd->dir;
        arvore_transplantar(t, nd, nd->dir);
    } else if (nd->dir == ARVORE_NULL) {
        x = nd->esq;
        arvore_transplantar(t, nd, nd->esq);
    } else {
        y = __arvore_minimo(nd->dir);
        cor_orig_y = y->cor;
        x = y->dir;

        if (y->pai == nd) {
            x->pai = y;
        } else {
            arvore_transplantar(t, y, y->dir);
            y->dir = nd->dir;
            y->dir->pai = y;
        }

        arvore_transplantar(t, nd, y);

        y->esq = nd->esq;
        y->esq->pai = y;
        y->cor = nd->cor;
    }

    if (cor_orig_y == NEGRO) arvore_consertar_delecao(t, x);

    // Desconecta totalmente o nó da árvore
    nd->esq = ARVORE_NULL;
    nd->dir = ARVORE_NULL;
    nd->pai = ARVORE_NULL;
    nd->cor = NEGRO;

    t->tmh_arvore--;
    return nd;
}

nodo_rb * arvore_deletar(arvore_rb *t, const void *k)
{
    nodo_rb *nd;

    // Busca nó a ser deletado. Se não encontrar, cancela a operação de deleção e retorna NULL
    if ((nd = arvore_buscar(t, k)) == NULL)
        return NULL;

    return arvore_deletar_nodo(t, nd);
}

nodo_rb * __busca_arvore_recursivo(nodo_rb *raiz, const void *k, int (*cmp_chaves) (const void*, const void*))
{
    if (raiz == ARVORE_NULL) return NULL;

    int cmp = cmp_chaves(raiz->chave, k);

    if (cmp == 0)
        return raiz;
    else if (cmp > 0)
        return __busca_arvore_recursivo(raiz->esq, k, cmp_chaves);
    else
        return __busca_arvore_recursivo(raiz->dir, k, cmp_chaves);
}

nodo_rb * __busca_arvore_iterativo(arvore_rb *t, const void *k)
{
    register int cmp;
    register nodo_rb *raiz = t->raiz;

    while (raiz != ARVORE_NULL)
    {
        cmp = t->cmp_chaves(raiz->chave, k);

        if (cmp == 0)
            break;
        else if (cmp > 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }

    if (raiz == ARVORE_NULL)
        return NULL;
    else
        return raiz;
}

nodo_rb * arvore_buscar(arvore_rb *t, const void *k)
{
    // return __busca_arvore_recursivo(t->raiz, k, t->cmp_chaves);
    return __busca_arvore_iterativo(t, k);
}

nodo_rb * __arvore_minimo(nodo_rb *raiz)
{
    while (raiz->esq != ARVORE_NULL) raiz = raiz->esq;
    return raiz;
}

nodo_rb * arvore_minimo(arvore_rb *t)
{
    return __arvore_minimo(t->raiz);
}

nodo_rb * __arvore_maximo(nodo_rb *raiz)
{
    while (raiz->dir != ARVORE_NULL) raiz = raiz->dir;
    return raiz;
}

nodo_rb * arvore_maximo(arvore_rb *t)
{
    return __arvore_maximo(t->raiz);
}

nodo_rb * arvore_predecessor(nodo_rb *nd)
{
    nodo_rb *pai;

    // Se o nó tem filho esquerdo, então o predecessor só pode ser o máximo da subárvore esquerda.
    if (nd->esq != ARVORE_NULL)
    {
        nd = __arvore_maximo(nd->esq);
    }
    else
    {
        // Caso contrário, procura o primeiro ancestral do nó que seja filho direito de outro nó.
        pai = nd->pai;
        while (pai != ARVORE_NULL && pai->esq == nd)
        {
            nd = pai;
            pai = pai->pai; // Essa foi de lascar hein...
        }
        nd = pai;
    }

    return nd;
}

nodo_rb * arvore_sucessor(nodo_rb *nd)
{
    nodo_rb *pai;

    // Se o nó tem filho direito, então o sucessor só pode ser o mínimo da subárvore direita.
    if (nd->dir != ARVORE_NULL)
    {
        nd = __arvore_minimo(nd->dir);
    }
    else
    {
        // Caso contrário, procura o primeiro ancestral do nó que seja filho esquerdo de outro nó.
        pai = nd->pai;
        while (pai != ARVORE_NULL && pai->dir == nd)
        {
            nd = pai;
            pai = pai->pai; // Como diz o ditado: "Tao Pai Pai, Tao Filho Filho..."
        }
        nd = pai;
    }

    return nd;
}

void __percorrer_preordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg)
{
    if (raiz != ARVORE_NULL)
    {
        func(raiz, arg);
        __percorrer_preordem_recursivo(raiz->esq, func, arg);
        __percorrer_preordem_recursivo(raiz->dir, func, arg);
    }
}

void percorrer_preordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg)
{
    __percorrer_preordem_recursivo(t->raiz, func, arg);
}

void __percorrer_inordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg)
{
    if (raiz != ARVORE_NULL)
    {
        __percorrer_inordem_recursivo(raiz->esq, func, arg);
        func(raiz, arg);
        __percorrer_inordem_recursivo(raiz->dir, func, arg);
    }
}

void percorrer_inordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg)
{
    __percorrer_inordem_recursivo(t->raiz, func, arg);
}

void __percorrer_posordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg)
{
    if (raiz != ARVORE_NULL)
    {
        __percorrer_posordem_recursivo(raiz->esq, func, arg);
        __percorrer_posordem_recursivo(raiz->dir, func, arg);
        func(raiz, arg);
    }
}

void percorrer_posordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg)
{
    __percorrer_posordem_recursivo(t->raiz, func, arg);
}
