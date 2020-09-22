/*
 * Daniel Paulo Garcia © 2020
 * 
 * megasena.c
 * 
 * Descrição: Dados um número "m" de jogadores com suas respectivas apostas, o
 * valor "n" do prêmio da Mega-Sena e os números sorteados, calcula o valor que
 * cada apostador deve receber e imprime na tela.
 *
 */

#include <stdio.h>
#include <stdint.h>

#define MAX_APOSTAS 1000
#define TAMANHO_VOLANTE 60
#define NUMEROS_SORTEADOS 6

void ler_apostas(uint64_t lista_apostas[], unsigned m)
{
    int entrada;

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < TAMANHO_VOLANTE; j++)
        {
            scanf(" %d", &entrada);
            lista_apostas[i] |= (entrada << i);
        }
    }
}

void ler_sorteados(unsigned lista_sorteados[])
{
    for (size_t i = 0; i < NUMEROS_SORTEADOS; i++)
    {
        scanf(" %u", &lista_sorteados[i]);
    }
}

int main(void)
{
    unsigned m;
    double n;
    uint64_t lista_apostas[MAX_APOSTAS];
    unsigned lista_sorteados[NUMEROS_SORTEADOS];

    scanf(" %u %lf", &m, &n);
    ler_apostas(lista_apostas, m);
    ler_sorteados(lista_sorteados);

    return 0;
}
