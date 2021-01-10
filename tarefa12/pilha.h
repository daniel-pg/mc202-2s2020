/**
 * Daniel Paulo Garcia © 2021
 *
 * pilha.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "pilha".
 */

#ifndef TAREFA12_PILHA_H
#define TAREFA12_PILHA_H

#include <stddef.h>

#include "planilha.h"

typedef struct pilha_t
{
    char (*stk)[MAX_TOKEN]; /* vetor de tokens */
    size_t tmh;             /* tamanho máximo da pilha */
    size_t slen;            /* número de elementos na pilha */
} pilha_t;


/**
 * @brief Aloca e inicializa uma nova pilha.
 * 
 * @param tmh Tamanho da pilha.
 * @return pilha_t* Ponteiro para a nova pilha, ou NULL caso a operação falhe.
 */
pilha_t * pilha_criar(size_t tmh);


/**
 * @brief Inicializa uma pilha previamente alocada pelo usuário.
 * 
 * @param p Ponteiro para a pilha a ser inicializada.
 * @param tmh Tamanho da pilha.
 * @return Retorna 'p' em caso de sucesso, ou NULL caso contrário.
 */
pilha_t * pilha_inicializar(pilha_t *p, size_t tmh);


/**
 * @brief Destrói uma pilha alocada pela função pilha_criar().
 * 
 * @param p Ponteiro para a pilha a ser destruída.
 */
void pilha_destruir(pilha_t *p);


/**
 * @brief Insere um elemento no topo da pilha.
 * 
 * @param p Ponteiro para a pilha onde se quer inserir.
 * @param tk Elemento a ser inserido.
 */
void pilha_push(pilha_t *p, const char *tk);


/**
 * @brief Remove um elemento do topo da pilha.
 * 
 * @param p Ponteiro para a pilha de onde se quer remover.
 * @return char* Ponteiro para o elemento removido.
 */
char * pilha_pop(pilha_t *p);


#endif //TAREFA12_PILHA_H
