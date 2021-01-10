/**
 * Daniel Paulo Garcia © 2021
 *
 * pilha.c
 *
 * Descrição: Implementa as funções do módulo pilha.h
 */

#include <stdlib.h>
#include <string.h>

#include "pilha.h"

pilha_t * pilha_criar(size_t tmh)
{
    pilha_t *p = malloc(sizeof(*p));
    if (p == NULL)
        return NULL;
    
    if (p != pilha_inicializar(p, tmh)) {
        free(p);
        return NULL;
    } else {
        return p;
    }
}

pilha_t * pilha_inicializar(pilha_t *p, size_t tmh)
{
    p->stk = malloc(tmh * sizeof(*p->stk));
    if (p->stk == NULL)
        return NULL;
    
    p->tmh = tmh;
    p->slen = 0;
    return p;
}

void pilha_destruir(pilha_t *p)
{
    free(p->stk);
    free(p);
}

void pilha_push(pilha_t *p, const char *tk)
{
    memcpy(p->stk[p->slen], tk, MAX_TOKEN * sizeof(*tk));
    p->slen++;
}

char * pilha_pop(pilha_t *p)
{
    p->slen--;
    return p->stk[p->slen];
}
