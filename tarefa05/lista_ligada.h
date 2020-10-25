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
    struct celula *ant;
    item_t valor;
} celula_t;

typedef struct lista_ligada
{
    celula_t *inicio;
    celula_t *fim;
    size_t len;
} lista_ligada_t;

// Aloca e inicializa uma lista ligada na memória.
lista_ligada_t * inicializa_lista(void);

// Remove todos os elementos da lista
void esvazia_lista(lista_ligada_t *lista);

// Esvazia a lista e logo em seguida libera-a da memória.
void libera_lista(lista_ligada_t *lista);

// Insere elemento na posição especificada.
void insere_elemento(lista_ligada_t *lista, const item_t item, size_t pos);

// Anexa elemento ao final da lista.
void anexa_elemento(lista_ligada_t *lista, const item_t item);

// Concatena duas listas
void concatena_listas(lista_ligada_t *l1, lista_ligada_t *l2);

// Remove primeira ocorrência do elemento especificado da lista e devolve seu indice.
size_t remove_elemento(lista_ligada_t *lista, const item_t item);

// Retira o elemento na posição especificada.
void retira_elemento(lista_ligada_t *lista, size_t pos);

// Copia a lista de origem para a lista de destino.
void copia_lista(lista_ligada_t *orig, lista_ligada_t *dest);

// Imprime todos os elementos da lista na saída padrão usando um separador especificado.
void imprime_lista(lista_ligada_t *lista, const char *sep);

// Lê uma lista de tamanho especificado da entrada padrão.
void ler_lista(lista_ligada_t *lista, size_t n);

#endif //TAREFA05_LISTA_LIGADA_H
