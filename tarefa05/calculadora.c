/**
 * Daniel Paulo Garcia © 2020
 *
 * calculadora.c
 *
 * Descrição: Calcula as operações matemáticas especificadas na entrada. Suporta números de precisão arbitrária.
 */

#include <stdio.h>

void seleciona_operacao(char op) // DD
{
    // TODO: receber os números n1 e n2 como parâmetros e implementar operações
    switch (op)
    {
        case '+':
            /* operação de soma */
            break;

        case '-':
            /* operação de subtração (em módulo) */
            break;

        case '*':
            /* operação de multiplicação */
            break;

        case '/':
            /* operação de divisão */
            break;

        default:
            break;
    }
}

int main(int argc, char const *argv[])
{
    unsigned int n;
    char op;

    scanf(" %u", &n);

    for (size_t i = 0; i < n; i++)
    {
        scanf(" %c", &op);
        // TODO: Ler números n1 e n2 e selecionar operação aqui.
    }

    return 0;
}