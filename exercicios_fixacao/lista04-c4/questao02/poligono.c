//
// Created by danielpg on 14/10/2020.
//

#include <stdbool.h>
#include "poligono.h"

bool eh_poligono_simples(Poligono *p)
{
}

double calcula_area_poligono(Poligono *p)
{
    register double area = 0;

    for (int i = 0; i < (p->n - 1); i++)
    {
        area += p->x[i] * p->y[i + 1] - p->y[i] * p->x[i + 1];
    }
    area += p->x[i] * p->y[0] - p->y[i] * p->x[0];

    area /= 2.0;
    return area;
}

void transladar_poligono(Poligono *p, double dx, double dy)
{
    for (int i = 0; i < p->n; i++)
    {
        p->x[i] += dx;
        p->y[i] += dy;
    }
}
