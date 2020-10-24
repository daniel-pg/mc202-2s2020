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
    celula_t *inicio;
    size_t len;
} lista_ligada_t;

// Aloca e inicializa uma lista ligada na memória.
lista_ligada_t * inicializa_lista(void);

// Remove todos os elementos da lista
void esvazia_lista(lista_ligada_t *lista);

// Esvazia a lista e logo em seguida libera-a da memória.
void libera_lista(lista_ligada_t *lista);

// Insere elemento na posição especificada.

// Anexa elemento ao final da lista.

// Concatena duas listas

// Remove primeira ocorrência do elemento especificado da lista.

// Retira o elemento na posição especificada.

// Copia a lista de origem para a lista de destino.

#endif //TAREFA05_LISTA_LIGADA_H
