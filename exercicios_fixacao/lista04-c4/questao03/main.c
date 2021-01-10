//
// Created by danielpg on 23/10/2020.
//

#include <stdio.h>

#include "tintas.h"

int main(void)
{
    tinta t1, t2, result;
    char c = 'Y';

    while (c == 'Y')
    {
        printf("Digite a primeira cor: ");
        scanf("%lf %lf %lf", &t1.cores[AZUL], &t1.cores[AMARELO], &t1.cores[VERMELHO]);
        printf("Digite a segunda cor: ");
        scanf("%lf %lf %lf", &t2.cores[AZUL], &t2.cores[AMARELO], &t2.cores[VERMELHO]);

        result = mistura_tintas(t1, t2);
        printf("Resultado da mistura: %lf %lf %lf\n", result.cores[AZUL], result.cores[AMARELO], result.cores[VERMELHO]);

        printf("Deseja continuar? [Y/n]\n");
        scanf(" %c", &c);
    }
    
    return 0;
}
