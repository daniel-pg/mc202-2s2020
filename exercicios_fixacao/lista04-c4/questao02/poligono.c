//
// Created by danielpg on 14/10/2020.
//

#include <stdbool.h>
#include <stdlib.h>
#include "poligono.h"

Poligono * cria_poligono(int n_vertices)
{
    Poligono *p = malloc(sizeof(Poligono));
    p->pontos = malloc(sizeof(struct ponto) * n_vertices);
    p->n_vertices = n_vertices;
    return p;
}

void libera_poligono(Poligono *p)
{
    free(p->pontos);
    free(p);
}

bool eh_poligono_simples(Poligono *p)
{
    return false;
}

double calcula_area_poligono(Poligono *p)
{
    register double area = 0;
    register int i;

    for (i = 0; i < (p->n_vertices - 1); i++)
    {
        area += p->pontos[i].x * p->pontos[i + 1].y - p->pontos[i].y * p->pontos[i + 1].x;
    }
    area += p->pontos[i].x * p->pontos[0].y - p->pontos[i].y * p->pontos[0].x;

    area /= 2.0;
    return area;
}

void transladar_poligono(Poligono *p, double dx, double dy)
{
    for (int i = 0; i < p->n_vertices; i++)
    {
        p->pontos[i].x += dx;
        p->pontos[i].y += dy;
    }
}
