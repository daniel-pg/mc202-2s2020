/**
 * Daniel Paulo Garcia © 2020
 *
 * arvore_rb.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo "Árvore Rubro-Negra".
 */

#ifndef TAREFA07_ARVORE_RB_H
#define TAREFA07_ARVORE_RB_H

// Não, não estamos falando de um corno rubro-negro, estamos falando da cor do nó da árvore rubro-negra...
enum cor_no {RUBRO, NEGRO};
typedef char* item_t;

typedef struct celula
{
    enum cor_no cor;
    struct celula *esq, *dir, *pai;
} celula_t;

struct arvore_rb
{
    celula_t *raiz;
};

#endif //TAREFA07_ARVORE_RB_H
