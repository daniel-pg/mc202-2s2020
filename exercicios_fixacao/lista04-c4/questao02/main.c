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

    if (eh_poligono_simples(meu_poligono))
        printf("Y");
    else
        printf("N");

    printf("%.2lf", area);

    libera_poligono(meu_poligono);
    return 0;
}
