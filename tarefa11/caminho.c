#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lista_ligada.h"

static void ler_grafo_entrada(lista_ligada_t *grafo)
{
    celula_t *ponto_atual;
    double pos_entrada[2];
    char eh_lugia;

    // Lê posição inicial
    scanf("%lf %lf", &pos_entrada[0], &pos_entrada[1]);
    ponto_atual = lista_anexar_inicio(grafo, pos_entrada);

    while (EOF != scanf("%lf %lf %c %*s", &pos_entrada[0], &pos_entrada[1], &eh_lugia))
    {
        ponto_atual = lista_anexar_fim(grafo, pos_entrada);

        if (eh_lugia == 'L')
            ponto_atual->status |= 1UL;
    }
}

static double busca_dfs(lista_ligada_t *grafo, celula_t *v, double max_dist, double restricao)
{
    // Se encontrou um novo caminho para o Lugia, retorne a distância máxima entre dois vértices encontrada
    if(v->status & 1UL)
    {
        return max_dist;
    }

    // Marque o vértice atual como acessado
    v->status |= (1UL << 1);

    double dist_atual;

    // Senão, busca recursivamente todos os vizinhos não visitados do vértice atual
    for(celula_t *w = grafo->inicio; w != NULL; w = w->prox)
    {
        if(w != v && !((w->status >> 1) & 1UL)) {
            dist_atual = hypot(v->coords[0] - w->coords[0], v->coords[1] - w->coords[1]);

            if (dist_atual >= restricao) {
                // Se o vértice não satisfaz a restrição, vá pro próximo
                continue;
            }
            else if (dist_atual > max_dist) {
                max_dist = dist_atual;
            }

            if ((dist_atual = busca_dfs(grafo, w, max_dist, restricao)) != -1)
                return dist_atual;
        }
    }
    
    // Não encontrou caminho
    return -1;
}

static int procura_lugia(lista_ligada_t *grafo)
{
    double menor_max_dist;  /* menor das distâncias máximas dentre todos os caminhos */
    double max_dist = 0;    /* distância máxima entre dois vértices consecutivos no caminho encontrado */

    // Primeira estimativa para o caminho de menor distância máxima entre vértices
    menor_max_dist = busca_dfs(grafo, grafo->inicio, 0, INFINITY);
    for(celula_t *v = grafo->inicio; v != NULL; v = v->prox) v->status &= ~(1UL << 1);

    /** Método gambiarra de resolução enquanto a busca binária não funciona. Executa em tempo surpreendentemente
     * razoável, e mais importante, resolve a tarefa. */
    while (max_dist != -1)
    {
        max_dist = busca_dfs(grafo, grafo->inicio, 0, menor_max_dist);
        if (max_dist != -1) menor_max_dist = max_dist;
        for(celula_t *v = grafo->inicio; v != NULL; v = v->prox) v->status &= ~(1UL << 1);
    }

    return ((int) ceil(menor_max_dist));
}

int main(void)
{
    // O grafo é completo, logo uma lista ligada basta para armazenar o grafo.
    lista_ligada_t *grafo = lista_criar();

    // Lê a entrada
    ler_grafo_entrada(grafo);

    // Imprime resultado
    printf("%d\n", procura_lugia(grafo));
    
    lista_destruir(grafo);
    return 0;
}
