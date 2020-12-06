/**
 * Daniel Paulo Garcia © 2020
 *
 * heapq.c
 *
 * Descrição: Implementa as funções do módulo heapq.h
 */

#include <stdlib.h>

#include "heapq.h"

heapq_t * heapq_criar(size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*))
{
    heapq_t *nova_heapq;
    void **chaves;

    nova_heapq = malloc(sizeof(*nova_heapq));
    if (!nova_heapq)
        return NULL;

    chaves = malloc(sizeof(*chaves) * tmh_heapq);
    if (!chaves) {
        free(nova_heapq);
        return NULL;
    }

    heapq_inicializar(nova_heapq, chaves, tmh_heapq, cmp_chaves);
    return nova_heapq;
}

void heapq_inicializar(heapq_t *heapq, void **chaves, size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*))
{
    heapq->chaves = chaves;
    heapq->tmh_heapq = tmh_heapq;
    heapq->len = 0;
    heapq->cmp_chaves = cmp_chaves;
}
