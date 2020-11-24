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
    return;
}

nodo_rb * arvore_inserir(arvore_rb *t, nodo_rb *nd)
{
    nodo_rb *x, *y;
    int cmp;

    // Iniciamos pela raíz da árvore
    y = ARVORE_NULL;    // Nó pai
    x = t->raiz;        // Nó auxiliar

    // Executa o programa do ratinho pra fazer o teste de DNA e encontrar o novo pai do nó a ser inserido.
    while (x != ARVORE_NULL)
    {
        cmp = t->cmp_chaves(nd->chave, x->chave);

        // Se encontrarmos uma chave duplicada, retorna NULL e cancela a inserção.
        if (cmp == 0)
            return NULL;

        y = x;
        if (cmp < 0)
            x = x->esq;
        else
            x = x->dir;
    }

    nd->pai = y;

    // Insere nó na árvore
    if (y == ARVORE_NULL)
        t->raiz = nd;
    else if (t->cmp_chaves(nd->chave, y->chave) < 0)
        y->esq = nd;
    else
        y->dir = nd;

    // Inicializa nó
    nd->esq = ARVORE_NULL;
    nd->dir = ARVORE_NULL;
    nd->cor = RUBRO;

    // Restaura propriedades da árvore rubro-negra
    arvore_consertar_insercao(t, nd);
    return nd;
}

nodo_rb * arvore_deletar(arvore_rb *t, const void *k)
{
    return NULL;
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

inline nodo_rb * __busca_arvore_iterativo(arvore_rb *t, const void *k)
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

nodo_rb * arvore_minimo(arvore_rb *t)
{
    nodo_rb *raiz = t->raiz;
    while (raiz->esq != ARVORE_NULL) raiz = raiz->esq;
    return raiz;
}

nodo_rb * arvore_maximo(arvore_rb *t)
{
    nodo_rb *raiz = t->raiz;
    while (raiz->dir != ARVORE_NULL) raiz = raiz->dir;
    return raiz;
}

nodo_rb * arvore_predecessor(nodo_rb *nd)
{
    nodo_rb *pai;

    // Se o nó tem filho esquerdo, então o predecessor só pode ser o máximo da subárvore esquerda.
    if (nd->esq != ARVORE_NULL)
    {
        nd = nd->esq;
        while (nd->dir != ARVORE_NULL) nd = nd->dir;
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
        nd = nd->dir;
        while (nd->esq != ARVORE_NULL) nd = nd->esq;
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
