/**
 * Daniel Paulo Garcia © 2020
 *
 * fakenews.c
 *
 * Descrição: ...
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fakenews.h"

#define MAX_PALAVRA 25

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

void processaListaTermos(Termo *lista_termos, int n, int m)
{
    int idx_max, idx_min;
    double media;

    for (int i = 0; i < n; i++)
    {
        idx_max = calculaIndiceMaximo(lista_termos[i].historico, m);
        idx_min = calculaIndiceMinimo(lista_termos[i].historico, m);
        media = calculaMedia(lista_termos[i].historico, m);
        lista_termos[i].maximo = &lista_termos[i].historico[idx_max];
        lista_termos[i].minimo = &lista_termos[i].historico[idx_min];
        lista_termos[i].media = media;
        lista_termos[i].desvpad = calculaDesvPad(lista_termos[i].historico, media, m);
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

double calculaMedia(double* historico, int m)
{
    // Assuma que o historico tenha pelo menos um elemento
    double sma = historico[0] / m;

    for (int i = 1; i < m; i++)
    {
        sma += historico[i] / m;
    }

    return sma;
}

double calculaDesvPad(double* historico, double media, int m)
{
    if (m < 2) return 0.0;
    
    double variancia = 0.0;
    double parcela;

    for (int i = 0; i < m; i++)
    {
        parcela = historico[i] - media;
        variancia += (parcela * parcela) / m;
    }

    return sqrt(variancia); // Desvio padrão
}

int calculaIndiceMaximo(double* historico, int m)
{
    int idx_max = 0;

    for (int i = 1; i < m; i++)
    {
        if (historico[i] > historico[idx_max])
        {
            idx_max = i;
        }
    }

    return idx_max;
}

int calculaIndiceMinimo(double* historico, int m)
{
    int idx_min = 0;

    for (int i = 1; i < m; i++)
    {
        if (historico[i] < historico[idx_min])
        {
            idx_min = i;
        }
    }

    return idx_min;
}

int main(void)
{
    Termo *lista_termos;
    int n, m;

    scanf(" %d %d", &n, &m);

    lista_termos = alocaListaTermos(n, m);
    lerListaTermos(lista_termos, n, m);
    // mostraListaTermos(lista_termos, n, m);
    processaListaTermos(lista_termos, n, m);

    liberaListaTermos(lista_termos, n);

    return 0;
}
