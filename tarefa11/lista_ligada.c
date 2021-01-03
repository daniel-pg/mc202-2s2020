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

void lista_destruir(lista_ligada_t *lista)
{
    lista_esvaziar(lista);
    free(lista);
}

celula_t * lista_inserir(lista_ligada_t *lista, double valor[], size_t pos)
{
    // Operação inválida: inserção em posição fora do limite da lista.
    if (pos > lista->len)
        return NULL;

    // Inserir um elemento no início é a mesma coisa que anexá-lo ao início da lista.
    if (pos == 0)
        return lista_anexar_inicio(lista, valor);

    // Inserir um elemento no final é a mesma coisa que anexá-lo ao fim da lista.
    if (pos == lista->len)
        return lista_anexar_fim(lista, valor);


    celula_t *atual, *novo_elemento;
    register size_t i;

    novo_elemento = malloc(sizeof(*novo_elemento));
    if (novo_elemento == NULL)
        return NULL;

    // Inicializa novo elemento
    memcpy(novo_elemento->coords, valor, 2 * sizeof(double));
    novo_elemento->status = 0x0;

    // Percorre a lista da esquerda para a direita ou ao contrário dependendo de qual caminho for mais curto.
    if (pos < lista->len / 2)
    {
        atual = lista->inicio;

        for (i = 0; i < pos - 1; i++) {
            atual = atual->prox;
        }

        novo_elemento->ant = atual;
        novo_elemento->prox = atual->prox;
        atual->prox->ant = novo_elemento;
        atual->prox = novo_elemento;
    } else {
        atual = lista->fim;

        for (i = lista->len - 1; i > pos; i--) {
            atual = atual->ant;
        }

        novo_elemento->prox = atual;
        novo_elemento->ant = atual->ant;
        atual->ant->prox = novo_elemento;
        atual->ant = novo_elemento;
    }

    lista->len++;
    return novo_elemento;
}

celula_t * lista_anexar_inicio(lista_ligada_t *lista, double valor[])
{
    celula_t *novo_elemento = malloc(sizeof(*novo_elemento));

    if (novo_elemento == NULL)
        return NULL;

    // Inicializa novo elemento
    memcpy(novo_elemento->coords, valor, 2 * sizeof(double));
    novo_elemento->status = 0x0;

    if (lista->fim == NULL)
        lista->fim = novo_elemento;
    else
        lista->inicio->ant = novo_elemento;

    novo_elemento->prox = lista->inicio;
    novo_elemento->ant = NULL;
    lista->inicio = novo_elemento;
    lista->len++;
    return novo_elemento;
}

celula_t * lista_anexar_fim(lista_ligada_t *lista, double valor[])
{
    celula_t *novo_elemento = malloc(sizeof(*novo_elemento));

    if (novo_elemento == NULL)
        return NULL;

    // Inicializa novo elemento
    memcpy(novo_elemento->coords, valor, 2 * sizeof(double));
    novo_elemento->status = 0x0;

    if (lista->inicio == NULL)
        lista->inicio = novo_elemento;
    else
        lista->fim->prox = novo_elemento;

    novo_elemento->ant = lista->fim;
    novo_elemento->prox = NULL;
    lista->fim = novo_elemento;
    lista->len++;
    return novo_elemento;
}

// Libera/remove o elemento da lista e "costura" as pontas soltas da lista de volta.
static void remove_elemento(lista_ligada_t *lista, celula_t *elemento)
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

celula_t * lista_remover(lista_ligada_t *lista, double valor[])
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        if (memcmp(atual->coords, valor, 2 * sizeof(double)) == 0)
        {
            remove_elemento(lista, atual);
            break;
        }

        atual = atual->prox;
    }

    return atual;
}

celula_t * lista_deletar(lista_ligada_t *lista, size_t pos)
{
    celula_t *atual;
    size_t i;

    // Avança o ponteiro atual até o elemento que será removido percorrendo o menor caminho.
    if (pos < lista->len / 2) {
        atual = lista->inicio;
        for (i = 0; i < pos; i++) atual = atual->prox;
    } else {
        atual = lista->fim;
        for (i = lista->len; i > pos; i--) atual = atual->ant;
    }

    remove_elemento(lista, atual);
    return atual;
}

void lista_concatenar(lista_ligada_t *dest, lista_ligada_t *orig)
{
    celula_t *atual = orig->inicio;
    celula_t *novo_elemento;

    while (atual != NULL)
    {
        novo_elemento = malloc(sizeof(*novo_elemento));
        
        // Operação falhou em algum ponto.
        if (novo_elemento == NULL) {
            exit(1);
        }

        // Inicializa novo elemento
        memcpy(novo_elemento->coords, atual->coords, 2 * sizeof(double));
        novo_elemento->status = 0x0;

        if (dest->inicio == NULL)
            dest->inicio = novo_elemento;
        else
            dest->fim->prox = novo_elemento;

        novo_elemento->ant = dest->fim;
        dest->fim = novo_elemento;

        atual = atual->prox;
    }

    dest->fim->prox = NULL;
    dest->len += orig->len;
}

void lista_copiar(lista_ligada_t *dest, lista_ligada_t *orig)
{
    if (dest != orig) {
        lista_esvaziar(dest);
        lista_concatenar(dest, orig);
    }
}
