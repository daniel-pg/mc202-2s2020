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
    uint64_t entrada;

    for (size_t i = 0; i < m; i++)
    {
        lista_apostas[i] = 0;

        for (size_t j = 0; j < TAMANHO_VOLANTE; j++)
        {
            scanf(" %lu", &entrada);
            lista_apostas[i] |= (entrada << j);
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

void contar_acertos(unsigned lista_acertos[], uint64_t lista_apostas[], unsigned lista_sorteados[], unsigned m)
{
    unsigned acertos;

    for (size_t i = 0; i < m; i++)
    {
        acertos = 0;

        for (size_t j = 0; j < NUMEROS_SORTEADOS; j++)
        {
            if (( (lista_apostas[i] >> (lista_sorteados[j] - 1)) & 0x01) == 0x01)
            {
                acertos++;
            }
        }

        lista_acertos[i] = acertos;

    }
}

int main(void)
{
    unsigned m;
    double n;
    uint64_t lista_apostas[MAX_APOSTAS];
    unsigned lista_acertos[MAX_APOSTAS];
    unsigned lista_sorteados[NUMEROS_SORTEADOS];

    scanf(" %u %lf", &m, &n);
    ler_apostas(lista_apostas, m);
    ler_sorteados(lista_sorteados);
    contar_acertos(lista_acertos, lista_apostas, lista_sorteados, m);

    for (size_t i = 0; i < m; i++)
    {
        // printf("%lu", lista_apostas[i]);
        printf("%u", lista_acertos[i]);
    }

    printf("\n");
    

    return 0;
}
