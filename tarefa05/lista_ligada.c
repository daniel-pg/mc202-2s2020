/**
 * Daniel Paulo Garcia © 2020
 *
 * lista_ligada.c
 *
 * Descrição: Implementa funções do módulo lista_ligada.h
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista_ligada.h"

lista_ligada_t * inicializa_lista(void)
{
    lista_ligada_t *lista;
    if ( (lista = malloc(sizeof(lista_ligada_t))) == NULL ) exit(1);

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->len = 0;

    return lista;
}

void esvazia_lista(lista_ligada_t *lista)
{
    celula_t *anterior;

    for (size_t i = 0; i < lista->len; i++)
    {
        anterior = lista->inicio;
        lista->inicio = anterior->prox;
        free(anterior);
    }

    lista->fim = NULL;
    lista->len = 0;
}

void libera_lista(lista_ligada_t *lista)
{
    esvazia_lista(lista);
    free(lista);
}

void anexa_elemento(lista_ligada_t *lista, const item_t item)
{
    celula_t *novo_elemento;
    if ( (novo_elemento = malloc(sizeof(*novo_elemento))) == NULL ) exit(1);

    novo_elemento->valor = item;
    novo_elemento->ant = lista->fim;
    novo_elemento->prox = NULL;

    lista->fim = novo_elemento;
}

void imprime_lista(lista_ligada_t *lista, const char *sep)
{
    for (celula_t *atual = lista->inicio; atual != NULL ; atual = atual->prox)
    {
        printf("%" PRIu64, atual->valor);
        printf("%s", sep);
    }
}

void ler_lista(lista_ligada_t *lista, size_t n)
{
    item_t el;

    for (size_t i = 0; i < n; i++)
    {
        scanf(" %" PRIu64, &el);
        anexa_elemento(lista, el);
    }
}
