/**
 * Daniel Paulo Garcia © 2020
 *
 * fakenews.c
 *
 * Descrição: ...
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PALAVRA 25

typedef struct termo
{
    char *palavra;
    double *historico;
} Termo;

Termo * alocaListaTermos(int n, int m)
{
    Termo *lista_termos = malloc(sizeof(Termo) * n);

    if (lista_termos == NULL)
    {
        goto erro;
    }

    for (int i = 0; i < n; i++)
    {
        lista_termos[i].palavra = malloc(sizeof(char) * MAX_PALAVRA);
        lista_termos[i].historico = malloc(sizeof(double) * m);

        if (!lista_termos[i].palavra || !lista_termos[i].historico)
        {
            goto erro;
        }

    }

    return lista_termos;

    erro:
        printf("Memoria insuficiente!");
        exit(1);
}

void liberaListaTermos(Termo *lista_termos, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(lista_termos[i].palavra);
        free(lista_termos[i].historico);
    }

    free(lista_termos);
}

void lerListaTermos(Termo *lista_termos, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        scanf(" %25s", lista_termos[i].palavra);
        for (int j = 0; j < m; j++)
        {
            scanf(" %lf", &lista_termos[i].historico[j]);
        }
    }
}

/** Lista todas os termos da entrada. Função usada apenas para debugging do programa */
void mostraListaTermos(Termo *lista_termos, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", lista_termos[i].palavra);
        for (int j = 0; j < m; j++)
        {
            printf("%lf ", lista_termos[i].historico[j]);
        }
        printf("\n");
    }
}

int main(void)
{
    Termo *lista_termos;
    int n, m;

    scanf(" %d %d", &n, &m);

    lista_termos = alocaListaTermos(n, m);
    lerListaTermos(lista_termos, n, m);
    mostraListaTermos(lista_termos, n, m);

    liberaListaTermos(lista_termos, n);

    return 0;
}
