#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double hypot_n_dimensoes(double*, double*, int, int);

void le_pontos(double *matriz_pontos, int dim_pontos, int n_pontos)
{
    for (size_t i = 0; i < n_pontos; i++)
    {
        for (size_t j = 0; j < dim_pontos; j++)
        {
            scanf(" %lf", &matriz_pontos[i * dim_pontos + j]);
        }
        
    }
    
}

double * calcula_centroide(double *matriz_pontos, int dim_pontos, int n_pontos)
{
    double *centroide = calloc(dim_pontos, sizeof(double));
    
    for (size_t i = 0; i < n_pontos; i++)
    {
        for (size_t j = 0; j < dim_pontos; j++)
        {
            centroide[j] += matriz_pontos[i * dim_pontos + j] / n_pontos;
        }
    }

    return centroide;
    
}

void libera_centroide(double *centroide)
{
    free(centroide);
}

double calc_soma_distancias(double *matriz_pontos, double *centroide, int dim_pontos, int n_pontos)
{
    double soma = 0;

    for (size_t i = 0; i < n_pontos; i++)
    {
        soma += hypot_n_dimensoes(matriz_pontos + i * dim_pontos, centroide, 0, dim_pontos - 1);
    }

    return soma;
}

double hypot_n_dimensoes(double *ponto, double *centroide, int l, int r)
{
    double resultado;
    int m = (l + r) / 2;
    if (l > r)
    {
        return 0.0;
    }
    else if (l == r)
    {
        return fabs(ponto[l] - centroide[l]);
    }
    else if (r - l == 1)
    {
        return hypot(ponto[l] - centroide[l], ponto[r] - centroide[r]);
    }
    else
    {
        return hypot(hypot_n_dimensoes(ponto, centroide, l, m), hypot_n_dimensoes(ponto, centroide, m + 1, r));
    }
    
    
    
    
}

void imprime_centroide(double *centroide, int dim_pontos, int n_pontos)
{
    printf("Centroide: ");

    for (size_t i = 0; i < dim_pontos; i++)
    {
        printf("%lf ", centroide[i]);
    }

    printf("\n");
}

int main(void)
{
    int dim_pontos, n_pontos;
    double *centroide, soma;
    scanf(" %d %d", &dim_pontos, &n_pontos);

    // Aloca uma matriz "linearizada"
    double *matriz_pontos = malloc(sizeof(double) * dim_pontos * n_pontos);
    if (!matriz_pontos) exit(1);
    
    le_pontos(matriz_pontos, dim_pontos, n_pontos);
    centroide = calcula_centroide(matriz_pontos, dim_pontos, n_pontos);
    soma = calc_soma_distancias(matriz_pontos, centroide, dim_pontos, n_pontos);
    imprime_centroide(centroide, dim_pontos, n_pontos);
    printf("Soma das distancias ate o centroide: %lf\n", soma);

    libera_centroide(centroide);
    free(matriz_pontos);
    return 0;
}
