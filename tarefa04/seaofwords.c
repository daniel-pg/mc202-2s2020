//
// Created by danielpg on 06/10/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seaofwords.h"

#define MAX_PALAVRA 20

void le_cacapalavras(char *cacapalavras, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf(" %c", (cacapalavras + sizeof(char) * (i * n + j)) );
        }
    }
}

void le_pistas(char *pistas, int q)
{
    for (int i = 0; i < q; i++)
    {
        scanf(" %s", &pistas[i]);
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_cacapalavras(const char *cacapalavras, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", *(cacapalavras + sizeof(char) * (i * n + j)) );
        }

        printf("\n");
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_pistas(char *pistas, int q)
{
    for (int i = 0; i < q; i++)
    {
        printf("%s\n", &pistas[i]);
    }
}

void procura_palavras(const char *cacapalavras, const char *palavras, bool *resultados, int n, int m, int q)
{
    char palavra_atual[MAX_PALAVRA];

    // Para cada palavra
    for (int k = 0; k < q; k++)
    {
        // Caso básico: A tabela está vazia
        if (!n || !m){
            resultados[k] = 0;
            continue;
        }

        strncpy(palavra_atual, &palavras[k], MAX_PALAVRA);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (backtrack(cacapalavras, palavra_atual, 0, i, j))
                {
                    resultados[k] = true;
                    goto proxima_palavra;
                }
            }
        }
        resultados[k] = 0;

        proxima_palavra:;

    }

}

bool backtrack(const char *cacapalavras, const char *palavra, int index, int i, int j)
{
    return true;
}

void imprime_resultados(const bool *resultados, int q)
{
    for (int i = 0; i < q; i++)
    {
        if (resultados[i])
        {
            printf("sim\n");
        }
        else
        {
            printf("nao\n");
        }
    }
}

int main(void)
{
    int n, m, q;
    scanf(" %d %d %d", &n, &m, &q); // Assume-se que a entrada sempre é válida, não há necessidade de usar fgets() ou strtol()

    /* Infelizmente o C90 não permite coisas como sizeof(char[n][m]), que é um um uso legítimo e seguro de VLA's.
     * Todas vez que quiser acessar a matriz, ao invés de usar a sintaxe super-conveniente:     matriz[i][j];
     * Terei que escrever:      *(matriz + sizeof(char) * (i * n + j))
     *
     * Solução elegante, se pudesse usar VLA's:
     * char (*matriz)[m] = malloc(sizeof(int[n][m]));
     * */
    char *cacapalavras = malloc(sizeof(char) * n * m);
    char *pistas = malloc(sizeof(char[MAX_PALAVRA]) * q);
    bool *resultados = malloc(sizeof(bool) * q);
    if (!cacapalavras || !pistas || !resultados)
    {
        free(resultados);
        free(pistas);
        free(cacapalavras);
        printf("Erro de alocacao de memoria!");
        exit(1);
    }

    le_cacapalavras(cacapalavras, n, m);
    le_pistas(pistas, q);
    // DEBUG: Escreve entrada devolta na tela
    // escreve_cacapalavras(cacapalavras, n, m);
    // escreve_pistas(pistas, q);

    procura_palavras(cacapalavras, pistas, resultados, n, m, q);
    imprime_resultados(resultados, q);

    // Libera memoria
    free(resultados);
    free(pistas);
    free(cacapalavras);
    return 0;
}