/**
 * Daniel Paulo Garcia © 2020
 *
 * lista_ligada.c
 *
 * Descrição: Implementa funções do módulo lista_ligada.h
 */

#include <stdlib.h>

#include "lista_ligada.h"

lista_ligada_t * inicializa_lista(void)
{
    lista_ligada_t *lista;
    if ( (lista = malloc(sizeof(lista_ligada_t))) == NULL ) exit(1);
    if ((lista->inicio = malloc(sizeof(celula_t))) == NULL ) exit(1);

    lista->inicio->prox = NULL;
    lista->inicio->valor = 0;
    lista->len = 0;

    return lista;
}

void esvazia_lista(lista_ligada_t *lista)
{
    celula_t *anterior;

    for (size_t i = 0; i < lista->len; i++)
    {
        anterior = lista->inicio->prox;
        lista->inicio->prox = anterior->prox;
        free(anterior);
    }

    lista->inicio->valor = 0;
    lista->len = 0;
}

void libera_lista(lista_ligada_t *lista)
{
    esvazia_lista(lista);
    free(lista->inicio);
    free(lista);
}
