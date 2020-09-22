/**
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
            if (((lista_apostas[i] >> (lista_sorteados[j] - 1)) & 0x01) == 0x01)
            {
                acertos++;
            }
        }

        lista_acertos[i] = acertos;
    }
}

unsigned contar_premiados(unsigned lista_acertos[], unsigned m, unsigned acertos)
{
    unsigned premiados = 0;

    for (size_t i = 0; i < m; i++)
    {
        if (lista_acertos[i] == acertos)
        {
            premiados++;
        }
    }

    return premiados;
}

void listar_premios(unsigned lista_acertos[], unsigned contagem_premiados[], unsigned m, double n)
{
    double valores_premios[3] = {0.0, 0.0, 0.0};

    // Caso não hajam premiados na quadra, quina ou sena, previne uma divisão por zero.
    if (contagem_premiados[0] > 0) valores_premios[0] = (0.19 * n) / contagem_premiados[0];
    if (contagem_premiados[1] > 0) valores_premios[1] = (0.19 * n) / contagem_premiados[1];
    if (contagem_premiados[2] > 0) valores_premios[2] = (0.62 * n) / contagem_premiados[2];

    for (size_t i = 0; i < m; i++)
    {
        switch (lista_acertos[i])
        {
        case 4:
            printf("%.2lf\n", valores_premios[0]);
            break;
        case 5:
            printf("%.2lf\n", valores_premios[1]);
            break;
        case 6:
            printf("%.2lf\n", valores_premios[2]);
            break;

        default:
            printf("%.2lf\n", 0.0);
            break;
        }
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

    unsigned contagem_premiados[3];
    for (size_t i = 0; i < 3; i++)
    {
        contagem_premiados[i] = contar_premiados(lista_acertos, m, i + 4);
    }

    listar_premios(lista_acertos, contagem_premiados, m, n);
    return 0;
}
