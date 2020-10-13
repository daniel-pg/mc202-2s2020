/**
 * Daniel Paulo Garcia © 2020
 * 
 * complexo.c
 * 
 * Implementa as funções do módulo "complexo.h".
 *
 */

#include <stdio.h>
#include <math.h>
#include "complexo.h"

#define LIMIAR_IGUALDADE 1e-8

void inicializa_complexo(Complexo *z, double real, double imag)
{
    z->real = real;
    z->imag = imag;
}

void imprime_complexo(Complexo z)
{
    printf("%lf + %lfi\n", z.real, z.imag);
}

double modulo_complexo(Complexo z)
{
    /* Muito mais seguro e otimizado do que usar uma implementação ingênua do hypot() */
    return hypot(z.real, z.imag);
}

Complexo soma_complexo(Complexo z1, Complexo z2)
{
    Complexo resultado;
    resultado.real = z1.real + z2.real;
    resultado.imag = z1.imag + z2.imag;
    return resultado;
}

Complexo multiplica_complexo(Complexo z1, Complexo z2)
{
    /** Notação:
     * z1 = a + b*i
     * z2 = c + d*i
    */

    Complexo resultado;
    resultado.real = z1.real * z2.real - z1.imag * z2.imag; // ac - bd
    resultado.imag = z1.real * z2.imag + z1.imag * z2.real; // ad + bc
    return resultado;
}

Complexo subtrai_complexo(Complexo z1, Complexo z2)
{
    Complexo resultado;
    resultado.real = z1.real - z2.real;
    resultado.imag = z1.imag - z2.imag;
    return resultado;
}

Complexo divide_complexo(Complexo z1, Complexo z2)
{
    // z1/z2 = z1 * 1/z2
    Complexo resultado;

    if (z2.real == 0 && z2.imag == 0)
    {
        printf("Erro de Divisão por Zero!");
        resultado.real = INFINITY;
        resultado.imag = INFINITY;
        return resultado;
    }

    double mod_z2 = modulo_complexo(z2);
    double mod_z2_quadrado = mod_z2 * mod_z2;

    Complexo inv_z2;
    inv_z2.real = z2.real / mod_z2_quadrado;
    inv_z2.imag = -z2.imag / mod_z2_quadrado;

    resultado = multiplica_complexo(z1, inv_z2);
    return resultado;
}

Complexo potencia_complexo(Complexo z, int a)
{
    Complexo resultado;

    if (a == 0)
    {
        resultado.real = 1;
        resultado.imag = 0;
        return resultado;
    }
    else
    {
        resultado = z;
    }

    for (int i = 1; i < a; i++)
    {
        resultado = multiplica_complexo(resultado, z);
    }

    return resultado;
}

int compara_complexo(Complexo z1, Complexo z2)
{
    if (modulo_complexo(subtrai_complexo(z1, z2)) < LIMIAR_IGUALDADE)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Complexo conjugado_complexo(Complexo z)
{
    Complexo resultado;
    resultado.real = z.real;
    resultado.imag = -z.imag;
    return resultado;
}