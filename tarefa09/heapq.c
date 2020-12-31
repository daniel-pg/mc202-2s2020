/**
 * Daniel Paulo Garcia © 2020
 *
 * heapq.c
 *
 * Descrição: Implementa as funções do módulo heapq.h
 */

#include <stdlib.h>

#include "heapq.h"

#define HP_PAI(i) ((i - 1)/2)
#define HP_ESQ(i) (2*i + 1)
#define HP_DIR(i) (2*i + 2)

static void troca_chaves(void **a, void **b)
{
    void *t = *a;
    *a = *b;
    *b = t;
}

static size_t sobe_heap(heapq_t *heapq, size_t idx)
{
    while (idx > 0 && heapq->cmp_chaves(heapq->chaves[HP_PAI(idx)], heapq->chaves[idx]) < 0)
    {
        troca_chaves(&heapq->chaves[HP_PAI(idx)], &heapq->chaves[idx]);
        idx = HP_PAI(idx);
    }

    return idx;
}

static size_t desce_heap(heapq_t *heapq, size_t idx)
{
    size_t maior_filho;
    size_t l, r;

    while (HP_ESQ(idx) < heapq->len) {
        l = HP_ESQ(idx);
        r = HP_DIR(idx);

        if(r < heapq->len && heapq->cmp_chaves(heapq->chaves[l], heapq->chaves[r]) < 0)
            maior_filho = r;
        else
            maior_filho = l;

        if (heapq->cmp_chaves(heapq->chaves[idx], heapq->chaves[maior_filho]) < 0) {
            troca_chaves(&heapq->chaves[idx], &heapq->chaves[maior_filho]);
            idx = maior_filho;
        } else {
            break;
        }
        
    }

    return idx;
}

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

void heapq_inicializar(heapq_t *heapq, void *chaves[], size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*))
{
    heapq->chaves = chaves;
    heapq->tmh_heapq = tmh_heapq;
    heapq->len = 0;
    heapq->cmp_chaves = cmp_chaves;
}

void heapq_destroi(heapq_t *heapq)
{
    // Heap inválida, não faça nada.
    if (!heapq)
        return;

    free(heapq->chaves);
    free(heapq);
}

long heapq_inserir(heapq_t *heapq, void *chave)
{
    void **temp;

    // Operação inválida
    if (!heapq || !heapq->chaves)
        return -1;

    // Aumentar o tamanho da heap caso ultrapasse o limite
    if (heapq->len == heapq->tmh_heapq) {
        temp = realloc(heapq->chaves, heapq->tmh_heapq * 2);

        // Se a realocação de memória falhar, cancele a operação de inserção.
        if (temp == NULL) {
            return -1;
        } else {
            heapq->chaves = temp;
            heapq->tmh_heapq *= 2;
        }
    }

    heapq->chaves[heapq->len] = chave;
    heapq->len++;

    return sobe_heap(heapq, heapq->len - 1);
}

void * heapq_extrair(heapq_t *heapq, size_t idx)
{
    if (!heapq || heapq->len == 0 || !heapq->chaves)
        return NULL;

    void *chave_extraida = heapq->chaves[idx];
    troca_chaves(&heapq->chaves[idx], &heapq->chaves[heapq->len - 1]);
    heapq->len--;
    desce_heap(heapq, idx);

    return chave_extraida;
}

long heapq_remover(heapq_t *heapq, const void *chave)
{
    long idx = heapq_buscar(heapq, chave);
    if (idx < 0) return -1;

    troca_chaves(&heapq->chaves[idx], &heapq->chaves[heapq->len - 1]);
    heapq->len--;
    desce_heap(heapq, idx);

    return idx;
}

long heapq_buscar(heapq_t *heapq, const void *chave)
{
    // TODO: Por enquanto só faz uma busca linear mesmo... melhorar depois.
    for (size_t i = 0; i < heapq->len; i++)
    {
        if (heapq->chaves[i] == chave) return i;
    }

    return -1;
}

void * heapq_extrai_max(heapq_t *heapq)
{
    return heapq_extrair(heapq, 0);
}

void heapq_heapify(heapq_t *heapq)
{
    for (long i = (long) heapq->len/2; i >= 0; i--)
    {
        desce_heap(heapq, i);
    }
}

void heapq_heapsort(heapq_t *heapq, void *arr[])
{
    for (long i = (long) heapq->len - 1; i >= 0; i--)
    {
        arr[i] = heapq_extrai_max(heapq);
    }
}

void heapq_percorrer_largura(heapq_t *heapq, void (*func)(void*, void*), void *arg)
{
    for (size_t i = 0; i < heapq->len; i++)
    {
        func(heapq->chaves[i], arg);
    }
}
