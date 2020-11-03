/**
 * Daniel Paulo Garcia © 2020
 *
 * int_grande.h
 *
 * Descrição: Permite manipular números inteiros positivos de precisão arbitrária.
 */

#ifndef TAREFA05_INT_GRANDE_H
#define TAREFA05_INT_GRANDE_H

#include "lista_ligada.h"

// Escreve o número em formato decimal na saída padrão.
void imprime_ngrande(lista_ligada_t *num);

// Lê um número em formato decimal da entrada padrão.
void le_ngrande(lista_ligada_t *num);

// Retorna 1 se n1 for maior, -1 se n1 for menor, ou 0 se n1 e n2 forem iguais.
int compara_ngrande(lista_ligada_t *n1, lista_ligada_t *n2);

// Soma dois números e guarda o resultado na variável de destino.
void soma_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2);

// Multiplica dois números e guarda o resultado na variável de destino.
void multiplica_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2);

// Subtrai dois números e guarda o resultado em módulo na variável de destino.
void subtrai_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2);

// Divide dois números e guarda o resultado na variável de destino.
void divide_ngrande(lista_ligada_t *resultado, lista_ligada_t *n1, lista_ligada_t *n2);

#endif //TAREFA05_INT_GRANDE_H
