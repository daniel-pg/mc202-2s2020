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
#define N_CATEGORIAS 5

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

char *** alocaMatrizPalavras(int linhas, int colunas)
{
    char ***matriz = malloc(sizeof(char**) * linhas);
    if (matriz == NULL)
    {
        printf("Erro de alocacao de memoria.");
        exit(1);
    }

    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = malloc(sizeof(char*) * colunas);
        if (matriz[i] == NULL)
        {
            printf("Erro de alocacao de memoria.");
            exit(1);
        }
    }

    return matriz;
}

void liberaMatrizPalavras(char ***matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
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

void mostraResultados(Termo *lista_termos, int n, int m)
{
    /* Categorias:
     * 1. Bot
     * 2. Evento surpreendente
     * 3. Evento normal
     * 4. Evento local
     * 5. Evento irrelevante
     * */
    double *maximo, *minimo, *media, *desvpad;
    char *palavra;
    int i, seletor;

    int *contagens = calloc(N_CATEGORIAS, sizeof(int)); // Importante inicializar com zeros!

    // Sim, essa é solução mais horrível do mundo, mas lembre-se de que uso do malloc pra tudo nessa tarefa é obrigatório.
    char **nome_categorias = malloc(sizeof(char*) * N_CATEGORIAS);
    char ***matriz_categorias = alocaMatrizPalavras(N_CATEGORIAS, n);

    if (!contagens || !nome_categorias)
    {
        printf("Erro de alocacao de memoria.");
        exit(1);
    }

    /* Acho que a essa altura do campeonato já deve ter ficado bem óbvio que C não é uma linguagem nada elegante.
     * Ah! Se desse de escrever só:
     * nome_categorias = {"Bot", "Surpreendente", "Normal", "Local", "Irrelevante"};
     * */
    for (i = 0; i < N_CATEGORIAS; i++)
    {
        nome_categorias[i] = malloc(sizeof(char) * 14); // 14 é o tamanho da maior string, preguiça de criar um define só pra isso.
        if (!nome_categorias[i])
        {
            printf("Erro de alocacao de memoria.");
            exit(1);
        }
    }

    sprintf(nome_categorias[0], "Bot");
    sprintf(nome_categorias[1], "Surpreendente");
    sprintf(nome_categorias[2], "Normal");
    sprintf(nome_categorias[3], "Local");
    sprintf(nome_categorias[4], "Irrelevante");

    for (i = 0; i < n; i++)
    {
        // Atalhos para não ter que ficar escrevendo o nome da variável por extenso toda hora.
        palavra = lista_termos[i].palavra;
        maximo = lista_termos[i].maximo;
        minimo = lista_termos[i].minimo;
        media = &lista_termos[i].media;
        desvpad = &lista_termos[i].desvpad;

        printf("%s %.2lf %.2lf %.2lf %.2lf\n", palavra, *maximo, *minimo, *media, *desvpad);

        // TODO: Corrigir essa bagaça!
        seletor = classificaTermo(maximo, minimo, media, desvpad);
        matriz_categorias[seletor][contagens[seletor]] = palavra;
        contagens[seletor]++;
    }

    printf("\nRESULTADO:\n");

    for (i = 0; i < N_CATEGORIAS; i++)
    {
        printf("%s (%d): ", nome_categorias[i], contagens[i]);

        for (int j = 0; j < contagens[i]; j++)
        {
            printf("%s ", matriz_categorias[i][j]);
        }
        printf("\n");
    }

    /* E lá vamos nós desalocar uma cacetada de memória! */
    free(contagens);

    for (i = 0; i < N_CATEGORIAS; i++)
    {
        free(nome_categorias[i]);
    }

    free(nome_categorias);
    liberaMatrizPalavras(matriz_categorias, N_CATEGORIAS);

}

int classificaTermo(double *maximo, double *minimo, double *media, double *desvpad)
{
    if (*media >= 60.0)
    {
        if (*desvpad > 15.0)
        {
            /* bot */
            return 0;
        } else
        {
            /* surpreendente */
            return 1;
        }
    }
    else
    {
        if (*maximo >= 80.0 && *minimo > 20.0)
        {
            /* normal */
            return 2;
        } else if (*maximo >= 80.0 && *minimo <= 20.0)
        {
            /* local */
            return 3;
        } else
        {
            /* irrelevante */
            return 4;
        }
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
    mostraResultados(lista_termos, n, m);

    liberaListaTermos(lista_termos, n);

    return 0;
}
