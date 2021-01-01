/**
 * Daniel Paulo Garcia © 2021
 *
 * lista_ligada.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "lista duplamente ligada". A estrutura de dados é
 * intrusiva, isto é, os valores são armazenados diretamente em cada nó da lista.
 */

#ifndef TAREFA09_LISTA_LIGADA_H
#define TAREFA09_LISTA_LIGADA_H

#include <stddef.h>

#define MAX_PALAVRA 26

typedef struct celula_t
{
    struct celula_t *prox;
    struct celula_t *ant;
    char valor[MAX_PALAVRA];
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
 * @return lista_ligada_t* 
 */
lista_ligada_t * lista_criar(void);

/**
 * @brief Remove todos os elementos da lista
 * 
 * @param lista 
 */
void lista_esvaziar(lista_ligada_t *lista);

/**
 * @brief Esvazia a lista e logo em seguida libera-a da memória.
 * 
 * @param lista 
 */
void lista_liberar(lista_ligada_t *lista);

/**
 * @brief Insere elemento na posição anterior à especificada.
 * 
 * @param lista 
 * @param valor 
 * @param pos 
 */
void lista_inserir(lista_ligada_t *lista, const char *valor, size_t pos);

/**
 * @brief Anexa elemento ao final da lista.
 * 
 * @param lista 
 * @param valor 
 */
void lista_anexar(lista_ligada_t *lista, const char *valor);

/**
 * @brief Concatena duas listas.
 * 
 * @param nova_lista 
 * @param l1 
 * @param l2 
 */
void lista_concatenar(lista_ligada_t *nova_lista, lista_ligada_t *l1, lista_ligada_t *l2);

/**
 * @brief Copia a lista de origem para a lista de destino.
 * 
 * @param dest 
 * @param orig 
 */
void lista_copiar(lista_ligada_t *dest, lista_ligada_t *orig);

/**
 * @brief Remove primeira ocorrência do elemento especificado da lista e devolve seu indice.
 * 
 * @param lista 
 * @param valor 
 */
void lista_remover(lista_ligada_t *lista, const char *valor);

/**
 * @brief Retira o elemento na posição especificada.
 * 
 * @param lista 
 * @param pos 
 */
void lista_deletar(lista_ligada_t *lista, size_t pos);


#endif //TAREFA09_LISTA_LIGADA_H
