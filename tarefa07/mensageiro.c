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
    // A variável "uu" não é usada
    free((struct cartao *) nd->chave);
    free(nd);
}

void imprime_nodo(nodo_rb *nd, void* uu)
{
    // A variável "uu" não é usada
    printf("%s", ((struct cartao*)nd->chave)->texto);
}

void processa_trio(arvore_rb *t, int soma)
{
    /* Basicamente resolve o problema da soma do subconjunto para o caso especial em que n=3 */
    nodo_rb *n0, *n1, *n2;
    nodo_rb *aux;

    // Preferir alocação estática para variáveis temporárias
    nodo_rb nd_soma;
    struct cartao meu_cartao;
    nd_soma.chave = &meu_cartao;

    int *resto = &((struct cartao*) nd_soma.chave)->numero;

    n0 = arvore_minimo(t);
    while (n0 != ARVORE_NULL)
    {
        n1 = arvore_sucessor(n0);
        while (n1 != ARVORE_NULL)
        {
            *resto = soma - ((struct cartao*) n0->chave)->numero - ((struct cartao*) n1->chave)->numero;
            n2 = arvore_buscar(t, nd_soma.chave);

            if (n2 != NULL)
            {
                imprime_nodo(n0, NULL);
                imprime_nodo(n1, NULL);
                imprime_nodo(n2, NULL);
                libera_nodo_cartao(arvore_deletar(t, n0->chave), NULL);
                libera_nodo_cartao(arvore_deletar(t, n1->chave), NULL);
                libera_nodo_cartao(arvore_deletar(t, n2->chave), NULL);
                goto fim;
            }

            n1 = arvore_sucessor(n1);
        }

        imprime_nodo(n0, NULL);
        aux = n0;
        n0 = arvore_sucessor(n0);
        libera_nodo_cartao(arvore_deletar(t, aux->chave), NULL);
    }

    fim: ;
}

int ler_mensagem(arvore_rb *t)
{
    nodo_rb *novo_nodo;
    struct cartao *novo_cartao;
    int m, n;
    int i;

    // Lê os inteiros m, n
    if (scanf("%d %d ", &m, &n) == EOF) return EOF;

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
    int soma;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &soma);
        processa_trio(t, soma);
    }

    // Imprime o resto em ordem
//    percorrer_inordem(t, imprime_nodo, NULL);
    printf("\n");

    return 0;
}

int main(void)
{
    arvore_rb *t = arvore_criar(cmp_cartoes);

    // Lê e decodifica cada mensagem enquanto não acabar a entrada, e depois libera os nós da árvore.
    while (1)
    {
        if (ler_mensagem(t) == EOF)
            break;

        percorrer_posordem(t, libera_nodo_cartao, NULL);
        arvore_inicializar(t, cmp_cartoes);
    }

    free(t);
    return 0;
}
