/**
 * Daniel Paulo Garcia © 2020
 *
 * calculadora.c
 *
 * Descrição: Calcula as operações matemáticas especificadas na entrada. Suporta números de precisão arbitrária.
 */

#include <stdio.h>
#include "int_grande.h"

void seleciona_operacao(char op, lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    switch (op)
    {
        case '+':
            /* operação de soma */
            soma_ngrande(resultado, n1, n2);
            break;

        case '-':
            /* operação de subtração (em módulo) */
            subtrai_ngrande(resultado, n1, n2);
            break;

        case '*':
            /* operação de multiplicação */
             multiplica_ngrande(resultado, n1, n2);
            break;

        case '/':
            /* operação de divisão */
            divide_ngrande(resultado, n1, n2);
            break;

        default:
            break;
    }
}

int main(void)
{
    lista_ligada_t *n1, *n2, *resultado;
    n1 = inicializa_lista();
    n2 = inicializa_lista();
    resultado = inicializa_lista();

    size_t n;
    char op;

    // Número de operações que serão realizadas
    scanf(" %lu", &n);

    for (size_t i = 0; i < n; i++)
    {
        // Operador da função que se quer computar
        scanf(" %c", &op);

        le_ngrande(n1);
        le_ngrande(n2);
        seleciona_operacao(op, resultado, n1, n2);
        imprime_ngrande(resultado);
    }

    libera_lista(resultado);
    libera_lista(n2);
    libera_lista(n1);
    return 0;
}
