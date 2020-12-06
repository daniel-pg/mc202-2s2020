/**
 * Daniel Paulo Garcia © 2020
 *
 * heapq.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "Heap".
 */

#ifndef TAREFA09_HEAPQ_H
#define TAREFA09_HEAPQ_H

#include <stddef.h>

typedef struct heapq
{
    // Atributos
    void **chaves;      /* vetor de ponteiros para os dados */
    size_t tmh_heapq;   /* tamanho do vetor alocado */
    size_t len;         /* quantidade atual de itens na heap */

    // Métodos
    int (*cmp_chaves) (const void*, const void*); /* Função para comparar duas chaves; deve ser providenciada pelo usuário */
} heapq_t;

/**
 * Cria uma nova fila de prioridade vazia com a função de comparação de chaves fornecida, e aloca memória para ela e
 * para o vetor de chaves.
 *
 * @param tmh_heapq Tamanho máximo da fila de prioridade.
 * @param cmp_chaves Função que compara duas chaves, de maneira similar ao strcmp().
 * @return Ponteiro para a fila criada.
 */
heapq_t * heapq_criar(size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*));

/**
 * Inicializa uma fila previamente alocada pelo usuário com o vetor de chaves e a função de comparação fornecidos.
 *
 * @param heapq Ponteiro para a fila de prioridade não inicializada.
 * @param chaves Vetor de ponteiros para os dados da fila.
 * @param tmh_heapq Tamanho máximo da fila de prioridade.
 * @param cmp_chaves Função que compara duas chaves, de maneira similar ao strcmp().
 */
void heapq_inicializar(heapq_t *heapq, void **chaves, size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*));

// Inserir elemento

// Remover elemento

// Buscar elemento

// Extrai máximo

// Constroi heap

// Heapify

// Heapsort

// Percurso pré-ordem

// Percurso inordem

// Percurso pós-ordem

// Percurso em largura

#endif //TAREFA09_HEAPQ_H
