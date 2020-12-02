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
    uint64_t numero;
    size_t num_copias;
};

int cmp_elementos(const void *n1, const void *n2)
{
    uint64_t cmp = ((struct elemento*) n1)->numero - ((struct elemento*) n2)->numero;
    if (cmp == 0)
        return 0;
    else if (cmp > 0)
        return 1;
    else
        return -1;
}

void libera_nodo(nodo_rb *nd, void *uu)
{
    (void) uu;
    free(nd);
}

void seleciona_operacao(arvore_rb *t, int op, uint64_t arg)
{
    switch (op)
    {
    case 1:
        /* adiciona o inteiro 'arg' na lista atual */
        break;

    case 2:
        /* encontra quantas vezes o inteiro 'arg' aparece na lista */
        break;

    case 3:
        /* encontra a menor quantidade de números que devem ser retirados da lista atual para que ela se torne legal */
        break;

    default:
        break;
    }
}

void le_processa_entrada(arvore_rb *t)
{
    // Lê inteiros n, k
    // Lê 'n' números da lista e adiciona-os à árvore
    // Lê as 'k' linhas seguintes, e para cada uma seleciona a operação correspondente
}

int main(void)
{
    arvore_rb *t = arvore_criar(cmp_elementos);

    le_processa_entrada(t);

    percorrer_posordem(t, libera_nodo, NULL);
    free(t);
    return 0;
}
