/**
 * Daniel Paulo Garcia © 2020
 *
 * lista_ligada.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo lista ligada simples.
 */

#ifndef TAREFA05_LISTA_LIGADA_H
#define TAREFA05_LISTA_LIGADA_H

#include <stdint.h>

typedef uint64_t item_t;

typedef struct celula
{
    struct celula *prox;
    item_t valor;
} celula_t;

typedef struct lista_ligada
{
    celula_t *sentinela;
    int len;
} lista_ligada_t;

#endif //TAREFA05_LISTA_LIGADA_H
