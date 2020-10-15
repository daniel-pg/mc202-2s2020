//
// Created by danielpg on 06/10/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seaofwords.h"

#define MAX_PALAVRA 21

void le_cacapalavras(char *cacapalavras, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf(" %c", &cacapalavras[i*m + j] );
        }
    }
}

void le_pistas(char *pistas, int q)
{
    for (int i = 0; i < q; i++)
    {
        scanf(" %s", &pistas[i * MAX_PALAVRA]);
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_cacapalavras(const char *cacapalavras, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", cacapalavras[i*m + j] );
        }

        printf("\n");
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_pistas(char *pistas, int q)
{
    for (int i = 0; i < q; i++)
    {
        printf("%s\n", &pistas[i * MAX_PALAVRA]);
    }
}

void procura_palavras(char *cacapalavras, const char *palavras, bool *resultados, int n, int m, int q)
{
    char palavra_atual[MAX_PALAVRA] = {0};

    // Para cada palavra
    for (int k = 0; k < q; k++)
    {
        // Caso básico: A tabela está vazia
        if (!n || !m)
        {
            resultados[k] = false;
            continue;
        }

        strncpy(palavra_atual, &palavras[k * MAX_PALAVRA], MAX_PALAVRA);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (backtrack(cacapalavras, palavra_atual, 0, i, j, &n, &m))
                {
                    resultados[k] = true;
                    goto proxima_palavra;
                }
            }
        }
        resultados[k] = 0;

        proxima_palavra: ;

    }

}

bool backtrack(char *cacapalavras, const char palavra[], int index, int i, int j, const int *n, const int *m)
{
    if (cacapalavras[i * (*m) + j] != palavra[index]) return false;
    if (index == strlen(palavra) - 1) return true;

    bool encontrou = false;
    char c = cacapalavras[i * (*m) + j];
    cacapalavras[i * (*m) + j] = '\0'; // Apaga o caractere, i.e. não deve ser procurado novamente

    if (i > 0)
    {
        encontrou |= backtrack(cacapalavras, palavra, index+1, i-1, j, n, m);
        if (encontrou) goto retorna_valor;
    }
    if (j > 0)
    {
        encontrou |= backtrack(cacapalavras, palavra, index+1, i, j-1, n, m);
        if (encontrou) goto retorna_valor;
    }
    if (i < *n - 1)
    {
        encontrou |= backtrack(cacapalavras, palavra, index+1, i+1, j, n, m);
        if (encontrou) goto retorna_valor;
    }
    if (j < *m - 1)
    {
        encontrou |= backtrack(cacapalavras, palavra, index+1, i, j+1, n, m);
        if (encontrou) goto retorna_valor;
    }

    retorna_valor:
    cacapalavras[i * (*m) + j] = c; // Restaura valor anterior do caça-palavras
    return encontrou;
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
     * Terei que escrever:      *(matriz + sizeof(char) * (i * m + j))
     * Alternativamente:        matriz[i*m + j]
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