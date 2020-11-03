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

    // Quando o fluxo de execução chegar aqui, necessariamente: lista->inicio == NULL;
    lista->fim = NULL;
    lista->len = 0;
}

void libera_lista(lista_ligada_t *lista)
{
    esvazia_lista(lista);
    free(lista);
}

void libera_elemento_costura_lista(lista_ligada_t *lista, celula_t *elemento)
{
    if (elemento->ant == NULL && elemento->prox == NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
    }
    else if (elemento->ant == NULL) {
        lista->inicio = elemento->prox;
        elemento->prox->ant = NULL;
    }
    else if (elemento->prox == NULL) {
        lista->fim = elemento->ant;
        elemento->ant->prox = NULL;
    }
    else {
        elemento->ant->prox = elemento->prox;
        elemento->prox->ant = elemento->ant;
    }

    free(elemento);
    lista->len--;
}

void insere_elemento(lista_ligada_t *lista, const item_t item, size_t pos)
{
    if (lista == NULL)
    {
        return; // Operação inválida: inserção numa lista vazia. Ver documentação em "lista_ligada.h".
    }

    register size_t i;
    celula_t *atual;
    celula_t *novo_elemento;

    if ( (novo_elemento = malloc(sizeof(*novo_elemento))) == NULL ) exit(1);
    novo_elemento->valor = item;

    // Percorre a lista da esquerda para a direita ou ao contrário dependendo de qual caminho for mais curto.
    if (pos < lista->len / 2)
    {
        atual = lista->inicio;
        for (i = 0; i < pos - 1; i++)
        {
            atual = atual->prox;
        }
        novo_elemento->ant = atual;
        novo_elemento->prox = atual->prox;
        atual->prox->ant = novo_elemento;
        atual->prox = novo_elemento;

    } else
    {
        atual = lista->fim;
        for (i = lista->len - 1; i > pos; i--)
        {
            atual = atual->ant;
        }
        novo_elemento->prox = atual;
        novo_elemento->ant = atual->ant;
        atual->ant->prox = novo_elemento;
        atual->ant = novo_elemento;
    }

    lista->len++;
}

void anexa_elemento(lista_ligada_t *lista, const item_t item)
{
    celula_t *novo_elemento;
    if ( (novo_elemento = malloc(sizeof(*novo_elemento))) == NULL ) exit(1);
    novo_elemento->valor = item;

    if (lista->inicio == NULL)
        lista->inicio = novo_elemento;
    else
        lista->fim->prox = novo_elemento;

    novo_elemento->ant = lista->fim;
    novo_elemento->prox = NULL;
    lista->fim = novo_elemento;
    lista->len++;
}

void concatena_listas(lista_ligada_t *nova_lista, lista_ligada_t *l1, lista_ligada_t *l2)
{
    copia_lista(nova_lista, l1);
    copia_lista(nova_lista, l2);
}

void remove_elemento(lista_ligada_t *lista, const item_t item)
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->valor == item)
        {
            libera_elemento_costura_lista(lista, atual);
            break;
        }

        atual = atual->prox;
    }
}

void retira_elemento(lista_ligada_t *lista, size_t pos)
{
    celula_t *atual;
    size_t i;

    if (pos < lista->len / 2)
    {
        atual = lista->inicio;
        for (i = 0; i < pos; i++) atual = atual->prox; // Avança o ponteiro atual até o elemento que será removido.
    }
    else
    {
        atual = lista->fim;
        for (i = lista->len; i > pos; i--) atual = atual->ant; // Avança o ponteiro atual até o elemento que será removido.
    }

    libera_elemento_costura_lista(lista, atual);
}

void copia_lista(lista_ligada_t *dest, lista_ligada_t *orig)
{
    celula_t *atual = orig->inicio;
    celula_t *novo_elemento;

    while (atual != NULL)
    {
        if ( (novo_elemento = malloc(sizeof(*novo_elemento))) == NULL ) exit(1);
        novo_elemento->valor = atual->valor;

        if (dest->inicio == NULL)
            dest->inicio = novo_elemento;
        else
            dest->fim->prox = novo_elemento;

        novo_elemento->ant = dest->fim;
        dest->fim = novo_elemento;

        atual = atual->prox;
    }

    dest->fim->prox = NULL;
    dest->len = orig->len;
}

void imprime_lista(lista_ligada_t *lista, const char *sep)
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        printf("%" PRIu64, atual->valor);
        printf("%s", sep);

        atual = atual->prox;
    }

    printf("\n");
}

void imprime_lista_inverso(lista_ligada_t *lista, const char *sep)
{
    celula_t *atual = lista->fim;

    while (atual != NULL)
    {
        printf("%" PRIu64, atual->valor);
        printf("%s", sep);

        atual = atual->ant;
    }

    printf("\n");
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
