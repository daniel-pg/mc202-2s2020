/**
 * Daniel Paulo Garcia © 2021
 *
 * lista_ligada.c
 *
 * Descrição: Implementa funções do módulo lista_ligada.h
 */

#include <stdlib.h>
#include <string.h>

#include "lista_ligada.h"

lista_ligada_t * lista_criar(void)
{
    lista_ligada_t *lista = malloc(sizeof(lista_ligada_t));

    if (lista == NULL)
        return NULL;

    lista->inicio = NULL;
    return lista;
}

void lista_esvaziar(lista_ligada_t *lista)
{
    celula_t *anterior;

    while (lista->inicio != NULL)
    {
        anterior = lista->inicio;
        lista->inicio = anterior->prox;
        free(anterior);
    }

    // Quando o fluxo de execução chegar aqui, necessariamente: lista->inicio == NULL;
}

void lista_destruir(lista_ligada_t *lista)
{
    lista_esvaziar(lista);
    free(lista);
}

celula_t * lista_anexar_inicio(lista_ligada_t *lista, const char *chave, bool dado)
{
    celula_t *novo_elemento = malloc(sizeof(*novo_elemento));

    if (novo_elemento == NULL)
        return NULL;

    strcpy(novo_elemento->chave, chave);
    novo_elemento->dado = dado;

    novo_elemento->prox = lista->inicio;
    lista->inicio = novo_elemento;
    return novo_elemento;
}

// Libera/remove o elemento da lista e "costura" as pontas soltas da lista de volta.
static void libera_elemento_costura_lista(lista_ligada_t *lista, celula_t *elemento, celula_t *anterior)
{
    if (anterior == NULL && elemento->prox == NULL) {
        lista->inicio = NULL;
    }
    else if (anterior == NULL) {
        lista->inicio = elemento->prox;
    }
    else if (elemento->prox == NULL) {
        anterior->prox = NULL;
    }
    else {
        anterior->prox = elemento->prox;
    }

    free(elemento);
}

size_t lista_remover(lista_ligada_t *lista, const char *chave)
{
    celula_t *atual = lista->inicio;
    celula_t *anterior = NULL;
    size_t pos = 0;

    while (atual != NULL)
    {
        if (strcmp(atual->chave, chave) == 0)
        {
            libera_elemento_costura_lista(lista, atual, anterior);
            break;
        }

        anterior = atual;
        atual = atual->prox;
        pos++;
    }

    return pos;
}
