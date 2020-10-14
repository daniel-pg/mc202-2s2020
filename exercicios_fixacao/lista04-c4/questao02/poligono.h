//
// Created by danielpg on 13/10/2020.
//

#ifndef LISTA04_C4_POLIGONO_H
#define LISTA04_C4_POLIGONO_H

#include <stdbool.h>

struct ponto
{
    double x, y;
};

typedef struct poligono{
    struct ponto *pontos;
    int n_vertices;
} Poligono;

Poligono * cria_poligono(int n_vertices);
void libera_poligono(Poligono *p);
bool eh_poligono_simples(Poligono *p);
double calcula_area_poligono(Poligono *p);
void transladar_poligono(Poligono *p, double dx, double dy);


#endif //LISTA04_C4_POLIGONO_H
