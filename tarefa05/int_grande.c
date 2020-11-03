/**
 * Daniel Paulo Garcia © 2020
 *
 * int_grande.c
 *
 * Descrição: Implementa funções do módulo int_grande.h
 */

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_grande.h"

// Infelizmente a linguagem C é ruim o suficiente pra nos forçar a esse tipo de truque para tarefas tão simples.
#define STR(x) #x
#define XSTR(x) STR(x)

// Maximo de algarismos decimais que cabem em um int de 64 bits, menos um algarismo para caber o resto da soma.
#define MAX_DIG_DECIMAL 2
#define MAX_VAL_DECIMAL (item_t) pow(10, MAX_DIG_DECIMAL)

#define MAX_NUM_LENGTH 64

void imprime_ngrande(lista_ligada_t *num)
{
    celula_t *atual = num->fim;

    while (atual != NULL)
    {
        // O último caractere deve ser impresso sem zeros à esquerda, e o restante deve ser alinhado à largura de um
        // membro da lista usando zeros.
        if (atual->prox == NULL)
            printf("%" PRIu64, atual->valor);
        else
            printf("%0" XSTR(MAX_DIG_DECIMAL) PRIu64, atual->valor);

        atual = atual->ant;
    }

    printf("\n");
}

// Algoritmo de conversão de base numérica baseado no algoritmo da biblioteca GMPLib. Adaptado para ler números decimais.
// Fonte: https://gmplib.org/manual/Radix-to-Binary
void conv_str_para_bin(lista_ligada_t *num, const char *str, size_t tmh_str)
{
    size_t k = 0;
    item_t atual = 0;
    item_t multiplicador = 1;

    for (size_t i = tmh_str; i-- > 0; )
    {
        atual += (item_t) (str[i] - '0') * multiplicador;
        multiplicador *= 10;

        if ((k + 1) % MAX_DIG_DECIMAL == 0 || i == 0)
        {
            anexa_elemento(num, atual);
            atual = 0;
            multiplicador = 1;
        }

        k++;
    }
}

void le_ngrande(lista_ligada_t *num)
{
    esvazia_lista(num);

    char entrada[MAX_NUM_LENGTH];
    scanf(" %s", entrada);
    size_t tmh_str = strlen(entrada);
    conv_str_para_bin(num, entrada, tmh_str);
}

int compara_ngrande(lista_ligada_t *n1, lista_ligada_t *n2)
{
    celula_t *atual_n1, *atual_n2;

    if (n1->len > n2->len) {
        return 1;
    } else if (n1->len < n2->len) {
        return -1;
    } else {
        // Se chegou até aqui, n1 e n2 tem mesmo comprimento, então precisamos checar membro a membro qual o maior.
        atual_n1 = n1->fim;
        atual_n2 = n2->fim;

        while (atual_n1 && atual_n2)
        {
            if (atual_n1->valor > atual_n2->valor) {
                return 1;
            } else if (atual_n1->valor < atual_n2->valor) {
                return -1;
            }

            // Avança os ponteiros pro membro menos significativo do número.
            atual_n1 = atual_n1->ant;
            atual_n2 = atual_n2->ant;
        }

        // Se n1 e n2 tem mesmo comprimento e todos os seus membros são iguais, então n1 e n2 são iguais.
        return 0;
    }
}

void soma_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    // Queremos ignorar o valor anterior da lista antes de realizar quaisquer cálculos.
    esvazia_lista(resultado);

    // Garante que a soma sempre seja feita a partir do menor número sobre o maior. Facilita a implementação do algoritmo.
    // Caso um número seja maior que outro mas ocupe o mesmo espaço na memória, o resultado será o mesmo.
    if (n1->len > n2->len) {
        copia_lista(resultado, n1);
    }
    else {
        copia_lista(resultado, n2);
        n2 = n1; // Não é necessário guardar uma referência para n2 uma vez feita a sua cópia.
    }

    anexa_elemento(resultado, 0); // Cria um espaço a mais para caso a soma ultrapasse o tamanho da lista.

    // TODO: Algoritmo de soma aqui
    item_t resto_soma = 0;
    celula_t *atual_result, *atual_n2;
    atual_result = resultado->inicio;
    atual_n2 = n2->inicio;

    for (size_t i = 0; i < resultado->len; i++)
    {
        // Caso estejamos somando os dígitos de n1 e n2 em paralelo...
        if (i < n2->len) {
            // É garantido que a soma nunca irá estourar o limite de um item_t devido ao limite MAX_DIG_DECIMAL.
            atual_result->valor += atual_n2->valor + resto_soma;
            atual_n2 = atual_n2->prox;
        }
        else {
            // ...senão, devemos apenas propagar o resto da soma.
            atual_result->valor += resto_soma;
        }

        if (atual_result->valor >= MAX_VAL_DECIMAL) {
            atual_result->valor -= MAX_VAL_DECIMAL;
            resto_soma = 1;
        }
        else {
            resto_soma = 0;
        }

        atual_result = atual_result->prox;
    }

    // Remove os "zeros à esquerda", ninguém gosta deles.
    if (resultado->fim->valor == 0)
    {
        retira_elemento(resultado, resultado->len);
    }

}

void multiplica_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    esvazia_lista(resultado);

    // TODO: Algoritmo de multiplicação aqui
}

void subtrai_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    esvazia_lista(resultado);

    // Garante que a subtração sempre seja feita em módulo.
    if (compara_ngrande(n1, n2) > 0) {
        copia_lista(resultado, n1);
    } else {
        copia_lista(resultado, n2);
        n2 = n1;
    }

    // TODO: Algoritmo de subtração aqui
    item_t emprestimo = 0;
    celula_t *atual_result, *atual_n2;
    atual_result = resultado->inicio;
    atual_n2 = n2->inicio;

    for (size_t i = 0; i < resultado->len; i++)
    {
        // Caso estejamos subtraindo os dígitos de n1 e n2 em paralelo...
        if (i < n2->len) {
            if (atual_result->valor < atual_n2->valor + emprestimo) {
                atual_result->valor += MAX_VAL_DECIMAL;
                atual_result->valor -= atual_n2->valor + emprestimo;
                emprestimo = 1;
            } else {
                atual_result->valor -= atual_n2->valor + emprestimo;
                emprestimo = 0;
            }

            atual_n2 = atual_n2->prox;
        } else {
            // Caso contrário, apenas propagar os empréstimos.
            if (atual_result->valor < emprestimo) {
                atual_result->valor += MAX_VAL_DECIMAL;
                atual_result->valor -= emprestimo;
                emprestimo = 1;
            } else {
                atual_result->valor -= emprestimo;
                emprestimo = 0;
            }
        }

        atual_result = atual_result->prox;
    }

    // Remove os zeros à esquerda.
    if (resultado->len > 1 && resultado->fim->valor == 0)
    {
        retira_elemento(resultado, resultado->len);
    }
}

void divide_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2)
{
    esvazia_lista(resultado);

    // TODO: Algoritmo de divisão aqui
}
