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
