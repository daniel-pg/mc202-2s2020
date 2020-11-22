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

nodo_rb * __busca_arvore_recursivo(nodo_rb *raiz, const void *k, int (*cmp_chaves) (const void*, const void*))
{
    if (raiz == NULL || cmp_chaves(raiz->chave, k) == 0) return raiz;

    if (cmp_chaves(raiz->chave, k) > 0)
        return __busca_arvore_recursivo(raiz->esq, k, cmp_chaves);
    else
        return __busca_arvore_recursivo(raiz->dir, k, cmp_chaves);
}

inline nodo_rb * __busca_arvore_iterativo(arvore_rb *t, const void *k)
{
    register nodo_rb *raiz = t->raiz;

    while (raiz != NULL && t->cmp_chaves(raiz->chave, k) != 0)
    {
        if (t->cmp_chaves(raiz->chave, k) > 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }

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
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

nodo_rb * arvore_maximo(arvore_rb *t)
{
    nodo_rb *raiz = t->raiz;
    while (raiz->dir != NULL) raiz = raiz->dir;
    return raiz;
}

nodo_rb * arvore_predecessor(nodo_rb *nd)
{
    nodo_rb *pai;

    // Se o nó tem filho esquerdo, então o predecessor só pode ser o máximo da subárvore esquerda.
    if (nd->esq != NULL)
    {
        nd = nd->esq;
        while (nd->dir != NULL) nd = nd->dir;
        return nd;
    }
    else
    {
        // Caso contrário, procura o primeiro ancestral do nó que seja filho direito de outro nó.
        pai = nd->pai;
        while (pai != NULL && pai->esq == nd)
        {
            nd = pai;
            pai = pai->pai; // Essa foi de lascar hein...
        }
        return pai;
    }
}

nodo_rb * arvore_sucessor(nodo_rb *nd)
{
    nodo_rb *pai;

    // Se o nó tem filho direito, então o sucessor só pode ser o mínimo da subárvore direita.
    if (nd->dir != NULL)
    {
        nd = nd->dir;
        while (nd->esq != NULL) nd = nd->esq;
        return nd;
    }
    else
    {
        // Caso contrário, procura o primeiro ancestral do nó que seja filho esquerdo de outro nó.
        pai = nd->pai;
        while (pai != NULL && pai->dir == nd)
        {
            nd = pai;
            pai = pai->pai; // Como diz o ditado: "Tao Pai Pai, Tao Filho Filho..."
        }
        return pai;
    }
}

void __percorrer_preordem_recursivo(nodo_rb *raiz, void (*func)(nodo_rb*, void*), void *arg)
{
    if (raiz != NULL)
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
    if (raiz != NULL)
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
    if (raiz != NULL)
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
