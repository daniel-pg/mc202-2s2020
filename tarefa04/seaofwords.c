//
// Created by danielpg on 06/10/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seaofwords.h"

#define MAX_PALAVRA 21

void le_cacapalavras(struct cacapalavras *c, int n, int m)
{
    c->matriz = malloc(sizeof(*c->matriz) * n * m);
    c->n = n;
    c->m = m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf(" %c", &c->matriz[i*m + j] );
        }
    }
}

void le_pistas(struct pistas *p, int q)
{
    p->palavras = malloc(sizeof(char[MAX_PALAVRA]) * q);
    p->q = q;

    for (int i = 0; i < q; i++)
    {
        scanf(" %s", &p->palavras[i * MAX_PALAVRA]);
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_cacapalavras(const struct cacapalavras *c)
{
    for (int i = 0; i < c->n; i++)
    {
        for (int j = 0; j < c->m; j++)
        {
            printf("%c", c->matriz[i * c->m + j] );
        }

        printf("\n");
    }
}

/* Função utilizada apenas para depurar o programa e checar se a entrada foi lida corretamente */
void escreve_pistas(const struct pistas *p)
{
    for (int i = 0; i < p->q; i++)
    {
        printf("%s\n", &p->palavras[i * MAX_PALAVRA]);
    }
}

void procura_palavras(struct cacapalavras *c, const struct pistas *p, bool *resultados)
{
    int i, j, k;

    // Se a tabela está vazia, todos os resultados da pesquisa serão falsos.
    if (!c->n || !c->m)
    {
        memset(resultados, 0, sizeof(*resultados) * p->q);
        return;
    }

    // Para cada palavra...
    for (k = 0; k < p->q; k++)
    {
        // Para cada linha da matriz...
        for (i = 0; i < c->n; i++)
        {
            // Para cada coluna da matriz...
            for (j = 0; j < c->m; j++)
            {
                if (encontra_palavra_na_posicao(c, &p->palavras[k * MAX_PALAVRA], i, j))
                {
                    resultados[k] = true;
                    goto proxima_palavra;
                }
            }
        }

        resultados[k] = false;
        proxima_palavra: ;
    }

}

bool encontra_palavra_na_posicao(struct cacapalavras *c, const char *palavra, int i, int j)
{
    if (c->matriz[i * c->m + j] != *palavra) return false;

    const char *prox_letra_palavra = palavra + 1; // Pré-computa o endereço da próxima letra na palavra.
    if (*prox_letra_palavra == '\0') return true;

    bool encontrou = false;
    char acessado = c->matriz[i * c->m + j];
    c->matriz[i * c->m + j] = '\0'; // Apaga o caractere, i.e. não deve ser procurado novamente

    if (i > 0)
    {
        encontrou |= encontra_palavra_na_posicao(c, prox_letra_palavra, i-1, j);
        if (encontrou) goto retorna_valor;
    }
    if (j > 0)
    {
        encontrou |= encontra_palavra_na_posicao(c, prox_letra_palavra, i, j-1);
        if (encontrou) goto retorna_valor;
    }
    if (i < c->n - 1)
    {
        encontrou |= encontra_palavra_na_posicao(c, prox_letra_palavra, i+1, j);
        if (encontrou) goto retorna_valor;
    }
    if (j < c->m - 1)
    {
        encontrou |= encontra_palavra_na_posicao(c, prox_letra_palavra, i, j+1);
        if (encontrou) goto retorna_valor;
    }

    retorna_valor:
    c->matriz[i * c->m + j] = acessado; // Restaura valor anterior do caça-palavras
    return encontrou;
}

void imprime_resultados(const bool *resultados, int q)
{
    for (int i = 0; i < q; i++)
    {
        if (resultados[i])
            printf("sim\n");
        else
            printf("nao\n");
    }
}

int main(void)
{
    int n, m, q;
    scanf(" %d %d %d", &n, &m, &q);

    bool *resultados = malloc(sizeof(*resultados) * q);
    if (resultados == NULL) exit(1);

    // Aloca struct na pilha
    struct cacapalavras cs;
    struct pistas ps;

    le_cacapalavras(&cs, n, m);
    le_pistas(&ps, q);

    // DEBUG: Escreve entrada devolta na tela
    // escreve_cacapalavras(&cs);
    // escreve_pistas(&ps);

    procura_palavras(&cs, &ps, resultados);
    imprime_resultados(resultados, q);

    // Libera memoria
    free(resultados);
    free(ps.palavras);
    free(cs.matriz);
    return 0;
}
