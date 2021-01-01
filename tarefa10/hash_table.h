/**
 * Daniel Paulo Garcia © 2020
 *
 * hash_table.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "Hash Table".
 */

#ifndef TAREFA09_HASH_TABLE_H
#define TAREFA09_HASH_TABLE_H

#include <stddef.h>

#include "lista_ligada.h"

#define TAMANHO_TABELA 1823

typedef struct hash_table_t
{
    lista_ligada_t tabela[TAMANHO_TABELA];
} hash_table_t;


/**
 * @brief Cria e aloca memória para uma nova hash table.
 * 
 * @return hash_table_t* Ponteiro para a nova hash table.
 */
hash_table_t * hashtable_criar();


/**
 * @brief Libera a memória e destrói a hash table.
 * 
 * @param ht Ponteiro para a hash table a ser destruída.
 */
void hashtable_destruir(hash_table_t *ht);


/**
 * @brief Insere uma chave na tabela.
 * 
 * @param ht Ponteiro para a hash table onde se quer inserir a chave.
 * @param chave Chave a ser inserida na hash table.
 */
void hashtable_inserir(hash_table_t *ht, char *chave);


/**
 * @brief Deleta uma chave da tabela.
 * 
 * @param ht Ponteiro para a hash table de onde se quer deletar a chave.
 * @param chave Chave a ser deletada da hash table.
 */
void hashtable_deletar(hash_table_t *ht, char *chave);


/**
 * @brief Busca uma chave na tabela.
 * 
 * @param ht Ponteiro para a hash table onde se quer buscar a chave.
 * @param chave Chave a ser buscada.
 * @return celula_t* Ponteiro para o elemento encontrado na tabela em caso de sucesso, ou NULL em caso contrário.
 */
celula_t * hashtable_buscar(hash_table_t *ht, char *chave);


#endif //TAREFA09_HASH_TABLE_H
