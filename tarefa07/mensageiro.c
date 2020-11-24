/**
 * Daniel Paulo Garcia © 2020
 *
 * mensageiro.c
 *
 * Descrição: Recebe um conjunto de tokens numerados unicamente, cada um contendo um trecho de texto, além de uma
 * sequência de inteiros usados para determinar a ordem de impressão dos tokens. O programa devolve a mensagem decodificada.
 */

#include <stdio.h>
#include <stdlib.h>

#include "arvore_rb.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define MAX_TEXTO_MSG 5

struct cartao
{
    char texto[MAX_TEXTO_MSG];
    int numero;
};

int cmp_cartoes(const void *msg1, const void *msg2)
{
    return ((struct cartao*) msg1)->numero - ((struct cartao*) msg2)->numero;
}

nodo_rb * cria_nodo_cartao()
{
    nodo_rb *novo_nodo;

    // Aloca espaço para o nó e para a chave
    if ( (novo_nodo = malloc(sizeof(*novo_nodo))) == NULL) abort();
    if ( (novo_nodo->chave = malloc(sizeof(struct cartao))) == NULL) abort();

    novo_nodo->esq = ARVORE_NULL;
    novo_nodo->dir = ARVORE_NULL;
    novo_nodo->pai = ARVORE_NULL;
    novo_nodo->cor = NEGRO;

    return novo_nodo;
}

void libera_nodo_cartao(nodo_rb *nd, void *uu)
{
    free((struct cartao *) nd->chave);
    free(nd);
}

int ler_mensagem(arvore_rb *t)
{
    nodo_rb *novo_nodo;
    struct cartao *novo_cartao;
    int m, n;
    int i;

    // Lê os inteiros m, n
    if (scanf(" %d %d", &m, &n) == EOF) return EOF;

    // Lê os cartões
    for (i = 0; i < m; i++)
    {
        novo_nodo = cria_nodo_cartao();
        novo_cartao = (struct cartao*) novo_nodo->chave;

        //TODO: Ainda não descobri como subtrair números com macros. Deveria ser MAX_TEXTO_MSG - 1
        scanf("%d %*[\"]%" STR(MAX_TEXTO_MSG) "[^\"]%*[\"]", &novo_cartao->numero, novo_cartao->texto);

        arvore_inserir(t, novo_nodo);
    }

    // Para cada "autoridade", imprime o trio.
    for (i = 0; i < n; i++)
    {
        // TODO: Algoritmo de achar trio aqui
    }

    return 0;
}

int main(void)
{
    arvore_rb *t = arvore_criar(cmp_cartoes);

    // Lê e decodifica cada mensagem enquanto não acabar a entrada, e libera a árvore após isso.
    while (ler_mensagem(t) != EOF)
    {
        percorrer_posordem(t, libera_nodo_cartao, NULL);
    }

    return 0;
}
