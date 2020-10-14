//
// Created by danielpg on 13/10/2020.
//

#ifndef LISTA04_C4_POLIGONO_H
#define LISTA04_C4_POLIGONO_H

#include <stdbool.h>

typedef struct poligono{
    double *x, *y;
    int n;
} Poligono;

bool eh_poligono_simples(Poligono *p);
double calcula_area_poligono(Poligono *p);
void transladar_poligono(Poligono *p, double dx, double dy);


#endif //LISTA04_C4_POLIGONO_H
