//
// Created by danielpg on 23/10/2020.
//

#ifndef QUESTAO03_TINTAS_H
#define QUESTAO03_TINTAS_H

#define N_CORES_PRIMARIAS 3

enum cores_primarias {AZUL, AMARELO, VERMELHO};

typedef struct tinta
{
    double cores[N_CORES_PRIMARIAS];    // Azul, amarelo, vermelho
} tinta;

tinta mistura_tintas(tinta t1, tinta t2);

#endif //QUESTAO03_TINTAS_H
