/**
 * Daniel Paulo Garcia © 2020
 *
 * int_grande.c
 *
 * Descrição: Implementa funções do módulo int_grande.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_grande.h"

// Maximo de algarismos decimais que cabem em um int de 64 bits.
#define MAX_DIG_DECIMAL 19

#define MAX_NUM_LENGTH 25

void imprime_ngrande(lista_ligada_t *num)
{
    imprime_lista_inverso(num, "");
}

// Algoritmo de conversão de base numérica baseado no algoritmo da biblioteca GMPLib. Adaptado para ler números decimais.
// Fonte: https://gmplib.org/manual/Radix-to-Binary
void conv_str_para_bin(lista_ligada_t *num, const char *str, size_t tmh_str)
{
    item_t atual = 0;
    item_t multiplicador = 1;

    for (size_t i = tmh_str; i-- > 0; )
    {
        atual += (item_t) (str[i] - '0') * multiplicador;
        multiplicador *= 10;

        if ( (i + 1) % MAX_DIG_DECIMAL == 0 || i == 0)
        {
            anexa_elemento(num, atual);
            atual = 0;
            multiplicador = 1;
        }
    }
}

void le_ngrande(lista_ligada_t *num)
{
    char entrada[MAX_NUM_LENGTH];
    scanf(" %s", entrada);
    size_t tmh_str = strlen(entrada);
    conv_str_para_bin(num, entrada, tmh_str);
}

void soma_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    // Garante que a soma sempre seja feita a partir do menor número sobre o maior. Facilita a implementação do algoritmo.
    if (n1->len > n2->len)
        copia_lista(resultado, n1);
    else
        copia_lista(resultado, n2);

    // TODO: Algoritmo de soma aqui
}

void multiplica_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    // TODO: Algoritmo de multiplicação aqui
}

void subtrai_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    // Garante que a subtração sempre seja feita em módulo.
    if (n1->len > n2->len) {
        copia_lista(resultado, n1);
    }
    else if (n1->len < n2->len) {
        copia_lista(resultado, n2);
    }
    else if (n1->fim->valor > n2->fim->valor) {
        copia_lista(resultado, n1);
    }
    else {
        copia_lista(resultado, n2);
    }

    // TODO: Algoritmo de subtração aqui
}

void divide_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    // TODO: Algoritmo de divisão aqui
}
