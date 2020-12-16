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

typedef struct heapq_t
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
 * @return Ponteiro para a fila criada, ou NULL se a função falhar.
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
void heapq_inicializar(heapq_t *heapq, void *chaves[], size_t tmh_heapq, int (*cmp_chaves) (const void*, const void*));

/**
 * Libera a memória alocada pela função heapq_criar() associada à heap. Não libera os elementos individuais da heap, que
 * devem ser liberados manualmente pelo usuário.
 *
 * @param heapq Ponteiro para a heap a ser destruída.
 */
void heapq_destroi(heapq_t *heapq);

/**
 * Insere um elemento na heap, dada a sua chave de acesso.
 *
 * @param heapq Ponteiro para a heap onde se quer inserir o elemento.
 * @param chave Endereço do valor a ser inserido.
 * @return Índice de inserção do valor no vetor, ou -1 se a operação falhar.
 */
long heapq_inserir(heapq_t *heapq, void *chave);

/**
 * Extrai elemento da heap na posição especificada, efetivamente removendo-o da heap.
 *
 * @param heapq Ponteiro para a heap de onde se quer extrair o elemento.
 * @param idx Índice de remoção do valor no vetor.
 * @return Chave (ponteiro) do valor extraído, ou NULL se a operação falhar.
 */
void * heapq_extrair(heapq_t *heapq, size_t idx);

/**
 * Remove elemento da heap cuja chave é igual à especificada.
 *
 * @param heapq Ponteiro para a heap de onde se quer remover o elemento.
 * @param chave Endereço do valor a ser removido.
 * @return Índice de remoção do valor no vetor, ou -1 se a operação falhar.
 */
long heapq_remover(heapq_t *heapq, const void *chave);

/**
 * Faz uma busca na heap pelo valor cuja chave é igual a fornecida. A busca é semelhante à busca linear/sequencial,
 * e tem complexidade O(n) no pior caso, exceto que na vida real muitas vezes o valor procurado pode não estar em uma
 * das subárvores de heap, o que diminui o tempo de busca.
 *
 * @param heapq Ponteiro para a heap onde se quer buscar o elemento.
 * @param chave Endereço do valor a ser buscado.
 * @return Índice do valor encontrado no vetor, ou -1 se a operação falhar.
 */
long heapq_buscar(heapq_t *heapq, const void *chave);

/**
 * Atalho para extrair a chave na posição de índice 0 da heap.
 *
 * @param heapq Ponteiro para a heap.
 * @return Chave de máximo da heap, ou NULL se a operação falhar.
 */
void * heapq_extrai_max(heapq_t *heapq);

/**
 * Algoritmo in-place para transformar um vetor de chaves qualquer em uma heap. Interessantemente, algumas pessoas
 * gostam de chamar essa operação de "buildheap", enquanto que a operação fixdown/fixup seria o "heapify". Sem nexo.
 *
 * @param heapq Ponteiro para a estrutura de heap que contém o vetor a ser transformado.
 */
void heapq_heapify(heapq_t *heapq);

/**
 * Constroi um vetor ordenado a partir dos elementos da heap.
 *
 * @param heapq Ponteiro para a heap.
 * @param arr Vetor com tamanho suficiente para armazenar todos os elementos da heap.
 */
void heapq_heapsort(heapq_t *heapq, void *arr[]);

/**
 * Faz o percurso em pré-ordem na heap, e executa a função fornecida em cada elemento acessado.
 *
 * @param heapq Ponteiro para a heap.
 * @param func Função executada para cada elemento percorrido.
 * @param arg Parâmetro opcional da função func (fornecida pelo usuário).
 */
void heapq_percorrer_preordem(heapq_t *heapq, void (*func)(void*, void*), void *arg);

/**
 * Faz o percurso em inordem na heap, e executa a função fornecida em cada elemento acessado.
 *
 * @param heapq Ponteiro para a heap.
 * @param func Função executada para cada elemento percorrido.
 * @param arg Parâmetro opcional da função func (fornecida pelo usuário).
 */
void heapq_percorrer_inordem(heapq_t *heapq, void (*func)(void*, void*), void *arg);

/**
 * Faz o percurso em pós-ordem na heap, e executa a função fornecida em cada elemento acessado.
 *
 * @param heapq Ponteiro para a heap.
 * @param func Função executada para cada elemento percorrido.
 * @param arg Parâmetro opcional da função func (fornecida pelo usuário).
 */
void heapq_percorrer_posordem(heapq_t *heapq, void (*func)(void*, void*), void *arg);

/**
 * Faz o percurso em largura na heap, e executa a função fornecida em cada elemento acessado.
 *
 * @param heapq Ponteiro para a heap.
 * @param func Função executada para cada elemento percorrido.
 * @param arg Parâmetro opcional da função func (fornecida pelo usuário).
 */
void heapq_percorrer_largura(heapq_t *heapq, void (*func)(void*, void*), void *arg);

#endif //TAREFA09_HEAPQ_H
