/**
 * Daniel Paulo Garcia © 2020
 *
 * listas_legais.c
 *
 * Descrição: Dada uma lista de números quaisquer, realiza um conjunto de operações nela, conforme descrito no enunciado
 * da tarefa.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvore_rb.h"

struct elemento {
    int64_t numero;
    size_t num_copias;
};

int cmp_elementos(const void *n1, const void *n2)
{
    int64_t cmp = ((struct elemento*) n1)->numero - ((struct elemento*) n2)->numero;
    if (cmp == 0)
        return 0;
    else if (cmp > 0)
        return 1;
    else
        return -1;
}

nodo_rb * cria_nodo(struct elemento *el)
{
    nodo_rb *novo_nodo;
    if ((novo_nodo = malloc(sizeof(*novo_nodo))) == NULL) return NULL;
    novo_nodo->chave = el;
    return novo_nodo;
}

void libera_nodo(nodo_rb *nd, void *uu)
{
    (void) uu;
    free(nd);
}

/**
 * Cria e insere um novo nó na árvore se a chave de entrada não estiver na árvore. Caso contrário, apenas incrementa o
 * número de ocorrências ("cópias") do elemento cujo número é igual ao do elemento de entrada.
 *
 * @param t Árvore binária de busca balanceada que armazena os elementos da lista.
 * @param entrada Elemento da lista, contendo um número e a sua quantidade de ocorrências na lista.
 * @param lista_elementos Vetor contendo os elementos de todos os nós da árvore.
 * @param pos_vetor Posição de inserção atual no vetor "lista_elementos".
 */
void insere_novo_nodo(arvore_rb *t, struct elemento *entrada, struct elemento *lista_elementos, int *pos_vetor)
{
    nodo_rb *novo_nodo;

    novo_nodo = arvore_buscar(t, entrada);
    if (novo_nodo == NULL)
    {
        novo_nodo = cria_nodo(&lista_elementos[*pos_vetor]);
        lista_elementos[*pos_vetor].numero = entrada->numero;
        lista_elementos[*pos_vetor].num_copias = 1;
        arvore_inserir(t, novo_nodo);
        (*pos_vetor)++;
    } else {
        ((struct elemento*) novo_nodo->chave)->num_copias++;
    }
}

/**
 * Executa uma das operações descritas na tarefa de acordo com a entrada.
 *
 * @param t Árvore binária de busca balanceada que armazena os elementos da lista.
 * @param op Número da operação
 * @param arg Argumento opcional da operação. Se a operação não recebe argumento, deve valer zero.
 * @param lista_elementos Vetor contendo os elementos de todos os nós da árvore.
 * @param pos_vetor Posição de inserção atual no vetor "lista_elementos".
 */
void seleciona_operacao(arvore_rb *t, int op, int64_t arg, struct elemento *lista_elementos, int *pos_vetor)
{
    nodo_rb *atual;
    struct elemento entrada;
    size_t acumulador;

    entrada.numero = arg;

    switch (op)
    {
    case 1:
        /* adiciona o inteiro 'arg' na lista atual */
        insere_novo_nodo(t, &entrada, lista_elementos, pos_vetor);
        break;

    case 2:
        /* encontra quantas vezes o inteiro 'arg' aparece na lista */
        atual = arvore_buscar(t, &entrada);
        if (atual == NULL)
            printf("0\n");
        else
            printf("%" PRId64 "\n", ((struct elemento*) atual->chave)->num_copias);

        break;

    case 3:
        /* encontra a menor quantidade de números que devem ser retirados da lista atual para que ela se torne legal */
        atual = arvore_minimo(t);
        acumulador = 0;

        while (atual != ARVORE_NULL)
        {
            // O cast é garantido de sempre retornar um valor válido pela lógica do programa, pois o número sempre é positivo.
            if (((struct elemento*) atual->chave)->num_copias >= (size_t) ((struct elemento*) atual->chave)->numero)
            {
                acumulador += ((struct elemento*) atual->chave)->num_copias - ((struct elemento*) atual->chave)->numero;
            } else
            {
                acumulador += ((struct elemento*) atual->chave)->num_copias;
            }
            atual = arvore_sucessor(atual);
        }

        printf("%" PRId64 "\n", acumulador);
        break;

    default:
        break;
    }
}

void le_processa_entrada(arvore_rb *t)
{
    struct elemento *lista_elementos;
    struct elemento entrada;
    int pos_vetor;

    int n, k;
    int op;
    int64_t arg;

    int i;

    // Lê inteiros n, k
    scanf("%d %d", &n, &k);

    /* Aloca um vetorzão com o tamanho máximo numa lapada só. Desperdiça no máximo O(k) bytes de memória, com a vantagem
     * de que todos os elementos estarão próximos na memória além de evitar muitas chamadas ao malloc, possivelmente com
     * maior desempenho. */
    lista_elementos = malloc(sizeof(*lista_elementos) * (n + k));
    if (lista_elementos == NULL) exit(1);

    // Lê 'n' números da lista e adiciona-os à árvore
    pos_vetor = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%" PRId64 , &entrada.numero);
        insere_novo_nodo(t, &entrada, lista_elementos, &pos_vetor);
    }

    // Lê as 'k' linhas seguintes, e para cada uma seleciona a operação correspondente
    for (i = 0; i < k; i++)
    {
        scanf("%d", &op);
        if (op == 1 || op == 2)
            scanf("%" PRId64, &arg);
        else
            arg = 0;

        seleciona_operacao(t, op, arg, lista_elementos, &pos_vetor);
    }

    free(lista_elementos);
    percorrer_posordem(t, libera_nodo, NULL);
}

int main(void)
{
    arvore_rb *t = arvore_criar(cmp_elementos);

    le_processa_entrada(t);

    free(t);
    return 0;
}
