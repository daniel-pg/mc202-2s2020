//
// Created by danielpg on 23/10/2020.
//

#include "tintas.h"

tinta mistura_tintas(tinta t1, tinta t2)
{
    tinta mistura;

    for (int i = 0; i < N_CORES_PRIMARIAS; i++) {
        mistura.cores[i] = 0.5 * (t1.cores[i] + t2.cores[i]);
    }
    
    return mistura;
}
