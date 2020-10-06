//
// Created by danielpg on 06/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "seaofwords.h"

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
    char *cacapalavras = malloc(n * m * sizeof(char));
    if (cacapalavras == NULL)
    {
        printf("Erro de alocacao de memoria!");
        exit(1);
    }

    le_cacapalavras(cacapalavras, n, m);
    escreve_cacapalavras(cacapalavras, n, m);


    free(cacapalavras);
    return 0;
}