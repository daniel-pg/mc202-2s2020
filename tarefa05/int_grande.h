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
void imprime_ngrande(lista_ligada_t *n);

// Lê um número em formato decimal da entrada padrão.
void le_ngrande(lista_ligada_t *n);

// Soma dois números e guarda o resultado na variável de destino.
lista_ligada_t * soma_ngrande(lista_ligada_t *n1, lista_ligada_t *n2);

// Multiplica dois números e guarda o resultado na variável de destino.
lista_ligada_t * multiplica_ngrande(lista_ligada_t *n1, lista_ligada_t *n2);

// Subtrai dois números e guarda o resultado em módulo na variável de destino.
lista_ligada_t * subtrai_ngrande(lista_ligada_t *n1, lista_ligada_t *n2);

// Divide dois números e guarda o resultado na variável de destino.
lista_ligada_t * divide_ngrande(lista_ligada_t *n1, lista_ligada_t *n2);

#endif //TAREFA05_INT_GRANDE_H
