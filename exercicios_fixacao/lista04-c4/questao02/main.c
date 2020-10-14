//
// Created by danielpg on 14/10/2020.
//

#include <stdio.h>
#include "poligono.h"

Poligono * le_poligono()
{
    Poligono *p;
    int n;

    scanf(" %d", &n);
    p = cria_poligono(n);

    for (int i = 0; i < n; i++)
    {
        scanf(" %lf", &p->pontos[i].x);
        scanf(" %lf", &p->pontos[i].y);
    }

    return p;
}

int main(void)
{
    double area;
    Poligono *meu_poligono = le_poligono();
    area = calcula_area_poligono(meu_poligono);
    printf("%.2lf", area);
    return 0;
}
