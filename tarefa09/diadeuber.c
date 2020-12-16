/**
 * Daniel Paulo Garcia © 2020
 *
 * diadeuber.c
 *
 * Descrição: Recebe um histórico de eventos diários do Uber, e imprime um relatório das ações realizadas em cada
 * corrida, bem como as estatísticas de quilômetros rodados, rendimento bruto e líquido e gastos ao fim do dia.
 */

#include <stdio.h>

#include "heapq.h"

#define MAX_CLIENTES 256
#define MAX_NOME 15

struct cliente
{
    char nome[MAX_NOME];
    double avaliacao;
    int pos_origem[2];
    int pos_destino[2];
};

int cmp_clientes(const void *c1, const void *c2)
{
    double a1 = ((struct cliente*) c1)->avaliacao;
    double a2 = ((struct cliente*) c2)->avaliacao;

    // É seguro comparar dois 'double' por igualdade nesse caso, pois os valores nunca são alterados algebricamente
    if (a1 == a2)
        return 0;
    else if ( (a1 - a2) > 0)
        return 1;
    else
        return -1;
}

int main(void)
{
    heapq_t *fila_corridas = heapq_criar(MAX_CLIENTES, cmp_clientes);

    heapq_destroi(fila_corridas);
    return 0;
}
