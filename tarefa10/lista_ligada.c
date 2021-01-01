/**
 * Daniel Paulo Garcia © 2021
 *
 * lista_ligada.c
 *
 * Descrição: Implementa funções do módulo lista_ligada.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_ligada.h"

lista_ligada_t * lista_criar(void)
{
    lista_ligada_t *lista = malloc(sizeof(lista_ligada_t));

    if (lista == NULL)
        return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->len = 0;

    return lista;
}

void lista_esvaziar(lista_ligada_t *lista)
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

void lista_liberar(lista_ligada_t *lista)
{
    lista_esvaziar(lista);
    free(lista);
}

void lista_inserir(lista_ligada_t *lista, const char *valor, size_t pos)
{
    if (pos > lista->len) {
        // Operação inválida: inserção em posição fora do limite da lista. Ver documentação em "lista_ligada.h".
        return;
    }

    // Inserir nessa posição é a mesma coisa que simplesmente anexá-lo.
    if (pos == lista->len) {
        lista_anexar(lista, valor);
        return;
    }

    celula_t *atual, *novo_elemento;

    novo_elemento = malloc(sizeof(*novo_elemento));
    if (novo_elemento == NULL )
        exit(1);

    strncpy(novo_elemento->valor, valor, MAX_PALAVRA - 1);

    // Inserir no início da lista
    if (pos == 0)
    {
        if (lista->fim == NULL)
            lista->fim = novo_elemento;
        else
            lista->inicio->ant = novo_elemento;

        novo_elemento->prox = lista->inicio;
        novo_elemento->ant = NULL;
        lista->inicio = novo_elemento;
        lista->len++;
        return;
    }

    register size_t i;

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

    } else {
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

void lista_anexar(lista_ligada_t *lista, const char *valor)
{
    celula_t *novo_elemento = malloc(sizeof(*novo_elemento));

    if (novo_elemento == NULL)
        exit(1);

    strncpy(novo_elemento->valor, valor, MAX_PALAVRA - 1);

    if (lista->inicio == NULL)
        lista->inicio = novo_elemento;
    else
        lista->fim->prox = novo_elemento;

    novo_elemento->ant = lista->fim;
    novo_elemento->prox = NULL;
    lista->fim = novo_elemento;
    lista->len++;
}

void lista_concatenar(lista_ligada_t *nova_lista, lista_ligada_t *l1, lista_ligada_t *l2)
{
    lista_copiar(nova_lista, l1);
    lista_copiar(nova_lista, l2);
}

// Libera/remove o elemento da lista e "costura" as pontas soltas da lista de volta.
static void libera_elemento_costura_lista(lista_ligada_t *lista, celula_t *elemento)
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

void lista_remover(lista_ligada_t *lista, const char *valor)
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            libera_elemento_costura_lista(lista, atual);
            break;
        }

        atual = atual->prox;
    }
}

void lista_deletar(lista_ligada_t *lista, size_t pos)
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

void lista_copiar(lista_ligada_t *dest, lista_ligada_t *orig)
{
    celula_t *atual = orig->inicio;
    celula_t *novo_elemento;

    while (atual != NULL)
    {
        novo_elemento = malloc(sizeof(*novo_elemento));
        
        if (novo_elemento == NULL)
            exit(1);

        strncpy(novo_elemento->valor, atual->valor, MAX_PALAVRA - 1);

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
