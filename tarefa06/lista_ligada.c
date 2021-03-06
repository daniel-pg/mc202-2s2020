/**
 * Daniel Paulo Garcia © 2020
 *
 * lista_ligada.c
 *
 * Descrição: Implementa funções do módulo lista_ligada.h
 */

#include <stdio.h>
#include <stdlib.h>

#include "lista_ligada.h"

lista_ligada_t * inicializa_lista(enum tipo_lista tipoLista)
{
    lista_ligada_t *lista;
    if ( (lista = malloc(sizeof(lista_ligada_t))) == NULL ) exit(1);

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->len = 0;
    lista->tipoLista = tipoLista;

    return lista;
}

void esvazia_lista(lista_ligada_t *lista, bool libera_valor)
{
    celula_t *anterior;

    for (size_t i = 0; i < lista->len; i++)
    {
        anterior = lista->inicio;
        lista->inicio = anterior->prox;
        libera_celula(anterior, lista->tipoLista, libera_valor);
    }

    // Quando o fluxo de execução chegar aqui, necessariamente: lista->inicio == NULL;
    lista->fim = NULL;
    lista->len = 0;
}

void libera_celula(celula_t *celula, enum tipo_lista tipoLista, bool libera_valor)
{
    if (libera_valor && tipoLista == PACIENTE)
    {
        struct paciente *paciente_atual = (struct paciente*) celula->valor;
        libera_lista(paciente_atual->lista_id, true);
    }
    if (libera_valor) free(celula->valor);

    free(celula);
}

void libera_lista(lista_ligada_t *lista, bool libera_valor)
{
    esvazia_lista(lista, libera_valor);
    free(lista);
}

void libera_elemento_costura_lista(lista_ligada_t *lista, celula_t *elemento, bool libera_valor)
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

    libera_celula(elemento, lista->tipoLista, libera_valor);
    lista->len--;
}

void insere_elemento(lista_ligada_t *lista, item_t item, size_t pos)
{
    if (pos > lista->len)
    {
        return; // Operação inválida: inserção em posição fora do limite da lista. Ver documentação em "lista_ligada.h".
    }

    // Inserir nessa posição é a mesma coisa que simplesmente anexá-lo.
    if (pos == lista->len) {
        anexa_elemento(lista, item);
        return;
    }

    celula_t *atual, *novo_elemento;

    if ( (novo_elemento = malloc(sizeof(*novo_elemento))) == NULL ) exit(1);
    novo_elemento->valor = item;

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

void anexa_elemento(lista_ligada_t *lista, item_t item)
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

void remove_elemento(lista_ligada_t *lista, item_t item, bool libera_valor)
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->valor == item)
        {
            libera_elemento_costura_lista(lista, atual, libera_valor);
            break;
        }

        atual = atual->prox;
    }
}

void retira_elemento(lista_ligada_t *lista, size_t pos, bool libera_valor)
{
    celula_t *atual;
    size_t i;

    if (pos <= lista->len / 2)
    {
        atual = lista->inicio;
        for (i = 0; i < pos; i++) atual = atual->prox; // Avança o ponteiro atual até o elemento que será removido.
    }
    else
    {
        atual = lista->fim;
        for (i = lista->len; i > pos; i--) atual = atual->ant; // Avança o ponteiro atual até o elemento que será removido.
    }

    libera_elemento_costura_lista(lista, atual, libera_valor);
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
        printf("%p", atual->valor);
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
        printf("%p", atual->valor);
        printf("%s", sep);

        atual = atual->ant;
    }

    printf("\n");
}
