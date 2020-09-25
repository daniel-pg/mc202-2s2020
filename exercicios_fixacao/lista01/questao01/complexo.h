/**
 * Daniel Paulo Garcia © 2020
 * 
 * complexo.h
 * 
 * Interface do módulo "complexo.h".
 *
 */

#ifndef COMPLEXO_H
#define COMPLEXO_H

typedef struct complexo
{
    double real;
    double imag;
} Complexo;

void inicializa_complexo(Complexo *z, double real, double imag);
void imprime_complexo(Complexo z);
double modulo_complexo(Complexo z);
Complexo soma_complexo(Complexo z1, Complexo z2);
Complexo multiplica_complexo(Complexo z1, Complexo z2);
Complexo subtrai_complexo(Complexo z1, Complexo z2);
Complexo divide_complexo(Complexo z1, Complexo z2);
Complexo potencia_complexo(Complexo z, int a);
int compara_complexo(Complexo z1, Complexo z2);
Complexo conjugado_complexo(Complexo z);

#endif /* COMPLEXO_H */
