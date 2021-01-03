/**
 * Daniel Paulo Garcia © 2021
 *
 * lista_ligada.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "lista ligada simples". A estrutura de dados é
 * intrusiva, isto é, os valores são armazenados diretamente em cada nó da lista.
 */

#ifndef TAREFA09_LISTA_LIGADA_H
#define TAREFA09_LISTA_LIGADA_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_PALAVRA 26

typedef struct celula_t
{
    struct celula_t *prox;

    char chave[MAX_PALAVRA];
    bool dado;
} celula_t;

typedef struct lista_ligada
{
    celula_t *inicio;
} lista_ligada_t;


/**
 * @brief Aloca e inicializa uma lista ligada na memória.
 * 
 * @return lista_ligada_t* Ponteiro para a nova lista, ou NULL caso a alocação falhe.
 */
lista_ligada_t * lista_criar(void);


/**
 * @brief Remove todos os elementos da lista.
 * 
 * @param lista Ponteiro para a lista de onde se quer remover todos os seus elementos.
 */
void lista_esvaziar(lista_ligada_t *lista);


/**
 * @brief Esvazia a lista e logo em seguida libera-a da memória.
 * 
 * @param lista Ponteiro para a lista que se quer destruir.
 */
void lista_destruir(lista_ligada_t *lista);


/**
 * @brief Anexa elemento no início da lista.
 * 
 * @param lista Ponteiro para a lista onde se quer inserir o novo elemento.
 * @param chave Valor de inicialização da chave do novo elemento.
 * @param dado Valor de inicialização do dado do novo elemento.
 */
celula_t * lista_anexar_inicio(lista_ligada_t *lista, const char *chave, bool dado);


/**
 * @brief Remove primeira ocorrência do elemento especificado da lista e devolve o índice de sua posição.
 * 
 * @param lista Ponteiro para a lista de onde se quer remover o elemento.
 * @param chave Valor do elemento que se quer remover.
 */
size_t lista_remover(lista_ligada_t *lista, const char *chave);


#endif //TAREFA09_LISTA_LIGADA_H
