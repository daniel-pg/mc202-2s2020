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

typedef struct nodo_rb
{
    struct nodo_rb *esq, *dir, *pai;
    const void *chave;
    enum cor_no cor;
} nodo_rb;

typedef struct arvore_rb
{
    // Atributos
    nodo_rb *raiz;
    size_t tmh_arvore; /* Número de nós da árvore */

    // Métodos
    int (*cmp_chaves) (const void*, const void*); /* Função para comparar duas chaves; deve ser providenciada pelo usuário */
} arvore_rb;

// Criar árvore

// Inicializar árvore

// Insere elemento

// Deleta elemento

// Busca um nó da árvore cuja chave seja igual à chave fornecida.
nodo_rb * arvore_buscar(arvore_rb *t, const void *k);

// Mínimo
nodo_rb * arvore_minimo(arvore_rb *t);

// Máximo
nodo_rb * arvore_maximo(arvore_rb *t);

// Predecessor
nodo_rb * arvore_predecessor(nodo_rb *nd);

// Sucessor
nodo_rb * arvore_sucessor(nodo_rb *nd);

// Percurso em pré-ordem
void percorrer_preordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);

// Percurso em inordem
void percorrer_inordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);

// Percurso em pós-ordem
void percorrer_posordem(arvore_rb *t, void (*func)(nodo_rb*, void*), void *arg);

// OBS: Essas funções abaixo provavelmente vão fazer parte apenas da implementação, e não da interface do módulo.
// Reparar árvore
// Rotação à esquerda
// Rotação à direita

#endif //TAREFA07_ARVORE_RB_H
