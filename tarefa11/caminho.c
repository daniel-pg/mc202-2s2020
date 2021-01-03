#include <stdbool.h>
#include <stdio.h>

#include "lista_ligada.h"

static void ler_grafo_entrada(lista_ligada_t *grafo)
{
    celula_t *ponto_atual;
    double pos_entrada[2];
    char eh_lugia;

    while (EOF != scanf("%lf %lf %c %*s", &pos_entrada[0], &pos_entrada[1], &eh_lugia))
    {
        ponto_atual = lista_anexar_fim(grafo, pos_entrada);

        if (eh_lugia == 'L')
            ponto_atual->status |= 1UL;
    }
}

// TODO: É aqui que a mágica acontece
static int procura_lugia(lista_ligada_t *grafo, double pos_atual[])
{
    return 0;
}

int main(void)
{
    // O grafo é completo, logo uma lista ligada basta para armazenar o grafo.
    lista_ligada_t *grafo = lista_criar();
    double pos_atual[2];
    int k;

    // Lê a entrada
    scanf("%lf %lf", &pos_atual[0], &pos_atual[1]);
    ler_grafo_entrada(grafo);

    // Imprime resultado
    k = procura_lugia(grafo, pos_atual);
    printf("%d", k);
    
    lista_destruir(grafo);
    return 0;
}
