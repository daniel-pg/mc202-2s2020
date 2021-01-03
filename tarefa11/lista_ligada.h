/**
 * Daniel Paulo Garcia © 2021
 *
 * lista_ligada.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "lista duplamente ligada". A estrutura de dados é
 * intrusiva, isto é, os valores são armazenados diretamente em cada nó da lista.
 */

#ifndef TAREFA10_LISTA_LIGADA_H
#define TAREFA10_LISTA_LIGADA_H

#include <stddef.h>

typedef struct celula_t
{
    struct celula_t *prox;
    struct celula_t *ant;
    char valor[8];
} celula_t;

typedef struct lista_ligada
{
    celula_t *inicio;
    celula_t *fim;
    size_t len;
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
 * @brief Insere elemento na posição anterior à especificada.
 * 
 * @param lista Ponteiro para a lista onde se quer inserir o novo elemento.
 * @param valor Valor de inicialização do novo elemento.
 * @param pos Índice da posição de inserção na lista.
 * 
 * @return celula_t* Ponteiro para o elemento inserido, ou NULL caso a operação falhe.
 */
celula_t * lista_inserir(lista_ligada_t *lista, const char *valor, size_t pos);


/**
 * @brief Anexa elemento ao início da lista.
 * 
 * @param lista Ponteiro para a lista onde se quer inserir o novo elemento.
 * @param valor Valor de inicialização do novo elemento.
 * 
 * @return celula_t* Ponteiro para o elemento inserido, ou NULL caso a operação falhe.
 */
celula_t * lista_anexar_inicio(lista_ligada_t *lista, const char *valor);


/**
 * @brief Anexa elemento ao final da lista.
 * 
 * @param lista Ponteiro para a lista onde se quer inserir o novo elemento.
 * @param valor Valor de inicialização do novo elemento.
 * 
 * @return Ponteiro para o elemento inserido, ou NULL caso a operação falhe.
 */
celula_t * lista_anexar_fim(lista_ligada_t *lista, const char *valor);


/**
 * @brief Remove primeira ocorrência do elemento especificado da lista.
 * 
 * @param lista Ponteiro para a lista de onde se quer remover o elemento.
 * @param valor Valor do elemento que se quer remover.
 * 
 * @return Ponteiro para o elemento removido, ou NULL caso a operação falhe.
 */
celula_t * lista_remover(lista_ligada_t *lista, const char *valor);


/**
 * @brief Remove o elemento na posição especificada.
 * 
 * @param lista Ponteiro para a lista de onde se quer deletar o elemento.
 * @param pos Índice da posição de deleção na lista.
 * 
 * @return Ponteiro para o elemento deletado, ou NULL caso a operação falhe.
 */
celula_t * lista_deletar(lista_ligada_t *lista, size_t pos);


/**
 * @brief Concatena a lista de origem ao final da lista destino.
 * 
 * @param dest Ponteiro para a lista de destino.
 * @param orig Ponteiro para a lista de origem.
 */
void lista_concatenar(lista_ligada_t *dest, lista_ligada_t *orig);


/**
 * @brief Copia a lista de origem para a lista de destino. Caso a lista de destino já contenha elementos, será
 * esvaziada antes, e se ambos parâmtros apontarem para a mesma lista, a função não faz nada.
 * 
 * @param dest Ponteiro para a lista de destino.
 * @param orig Ponteiro para a lista de origem.
 */
void lista_copiar(lista_ligada_t *dest, lista_ligada_t *orig);


#endif //TAREFA10_LISTA_LIGADA_H
