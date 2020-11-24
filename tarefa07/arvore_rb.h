/**
 * Daniel Paulo Garcia © 2020
 *
 * arvore_rb.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "Árvore Rubro-Negra".
 */

#ifndef TAREFA07_ARVORE_RB_H
#define TAREFA07_ARVORE_RB_H

// Não, não estamos falando de um corno rubro-negro, estamos falando da cor do nó da árvore rubro-negra...
enum cor_no {RUBRO, NEGRO};

typedef struct nodo_rb
{
    struct nodo_rb *esq, *dir, *pai;
    const void *chave;
    enum cor_no cor;
} nodo_rb;

typedef struct arvore_rb
{
    // Atributos
    nodo_rb *raiz;
    size_t tmh_arvore; /* Número de nós da árvore */

    // Métodos
    int (*cmp_chaves) (const void*, const void*); /* Função para comparar duas chaves; deve ser providenciada pelo usuário */
} arvore_rb;

#define ARVORE_NULL &arvore_nodo_nulo
extern nodo_rb arvore_nodo_nulo;

/**
 * Cria uma nova árvore vazia com a função de comparação de chaves fornecida, e aloca memória para ela.
 *
 * @param cmp_chaves Função que compara duas chaves, de maneira similar ao strcmp().
 * @return Ponteiro para a árvore criada.
 */
arvore_rb * arvore_criar(int (*cmp_chaves) (const void*, const void*));

/**
 * Inicializa uma árvore previamente alocada pelo usuário.
 *
 * @param t Ponteiro para árvore não inicializada.
 * @param cmp_chaves Função que compara duas chaves, de maneira similar ao strcmp().
 */
void arvore_inicializar(arvore_rb *t, int (*cmp_chaves) (const void*, const void*));

/**
 * Insere um novo nó na árvore.
 *
 * @param t Árvore onde se quer inserir o nó.
 * @param nd Nó a ser inserido.
 * @return Ponteiro nd em caso de sucesso, NULL caso a chave do novo nó coincida com a de algum outro nó da árvore.
 */
nodo_rb * arvore_inserir(arvore_rb *t, nodo_rb *nd);

/**
 * Remove da árvore o nó cuja chave é igual à chave fornecida. É de responsabilidade do usuário liberar a memória do nó
 * removido.
 *
 * @param t Árvore de onde se deseja retirar o nó.
 * @param k Chave do nó que será retirado.
 * @return Ponteiro para o nó removido, ou NULL caso o nó não seja encontrado.
 */
nodo_rb * arvore_deletar(arvore_rb *t, const void *k);

/**
 * Busca um nó da árvore cuja chave seja igual à chave fornecida.
 *
 * @param t Árvore onde se quer buscar.
 * @param k Chave do nó a ser buscado.
 * @return Ponteiro para o nó encontrado, ou NULL se não foi encontrado.
 */
nodo_rb * arvore_buscar(arvore_rb *t, const void *k);

/**
 * Encontra o nó mínimo, ou seja, aquele mais à esquerda de todos na árvore.
 *
 * @param t Árvore onde se quer buscar.
 * @return Ponteiro para o nó mínimo, ou NULL se a árvore estiver vazia.
 */
nodo_rb * arvore_minimo(arvore_rb *t);

/**
 * Encontra o nó máximo, ou seja, aquele mais à direita de todos na árvore.
 *
 * @param t Árvore onde se quer buscar.
 * @return Ponteiro para o nó máximo, ou NULL se a árvore estiver vazia.
 */
nodo_rb * arvore_maximo(arvore_rb *t);

/**
 * Encontra o predecessor do nó fornecido.
 *
 * @param nd Nó cujo predecessor será buscado.
 * @return Ponteiro para o predecessor, ou NULL se não houver predecessor.
 */
nodo_rb * arvore_predecessor(nodo_rb *nd);

/**
 * Encontra o sucessor do nó fornecido.
 *
 * @param nd Nó cujo sucessor será buscado.
 * @return Ponteiro para o sucessor, ou NULL se não houver sucessor.
 */
nodo_rb * arvore_sucessor(nodo_rb *nd);

/**
 * Faz o percurso em pré-ordem na árvore, e executa a função fornecida em cada elemento acessado.
 *
 * @param t Árvore binária.
 * @param func Função executada para cada nó percorrido.
 * @param arg Parâmetro opcional da função func (fornecido pelo usuário).
 */
void percorrer_preordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);

/**
 * Faz o percurso em inordem na árvore, e executa a função fornecida em cada elemento acessado.
 *
 * @param t Árvore binária.
 * @param func Função executada para cada nó percorrido.
 * @param arg Parâmetro opcional da função func (fornecido pelo usuário).
 */
void percorrer_inordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);

/**
 * Faz o percurso em pós-ordem na árvore, e executa a função fornecida em cada elemento acessado. O percuso em pós-ordem
 * é especialmente útil para liberar todos os recursos alocados pela árvore, já que todos os nós filhos são acessados
 * antes dos pais.
 *
 * @param t Árvore binária.
 * @param func Função executada para cada nó percorrido.
 * @param arg Parâmetro opcional da função func (fornecido pelo usuário).
 */
void percorrer_posordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);


#endif //TAREFA07_ARVORE_RB_H
