/**
 * Daniel Paulo Garcia © 2020
 * 
 * main.c
 * 
 * Programa para testar o módulo "complexo.h".
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include "complexo.h"

int main(void)
{
    Complexo z1, z2, z = {0.0, 0.0};
    double a, b;
    unsigned operacao;
    int primeira_vez = true;

    while (true)
    {
        if (!primeira_vez)
        {
            printf("Resultado:\n");
            imprime_complexo(z);
            printf("\n\nNova operação:\n");
        }

        printf("Selecione uma dentre as seguintes operações:\n");
        printf("0. Sair.\n");
        printf("1. Somar.\n");
        printf("2. Subtrair.\n");
        printf("3. Multiplicar.\n");
        printf("4. Dividir.\n");
        printf(">> ");

        scanf(" %u", &operacao);
        if (!operacao)
        {
            break;
        }
        
        printf("\n");

        printf("Primeiro operando:\n");
        scanf(" %lf %lf", &a, &b);
        inicializa_complexo(&z1, a, b);

        printf("Segundo operando:\n");
        scanf(" %lf %lf", &a, &b);
        inicializa_complexo(&z2, a, b);

        switch (operacao)
        {
        case 1:
            z = soma_complexo(z1, z2);
            break;

        case 2:
            z = subtrai_complexo(z1, z2);
            break;

        case 3:
            z = multiplica_complexo(z1, z2);
            break;

        case 4:
            z = divide_complexo(z1, z2);
            break;

        default:
            break;
        }

        primeira_vez = false;

    }

    return 0;
}
