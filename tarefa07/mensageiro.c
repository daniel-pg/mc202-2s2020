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
#include <string.h>

#include "arvore_rb.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define MAX_TEXTO_MSG 5

struct cartao
{
    char *texto;
    int numero;
};

int cmp_cartoes(const void *msg1, const void *msg2)
{
    return ((struct cartao*) msg1)->numero - ((struct cartao*) msg2)->numero;
}

nodo_rb * cria_nodo_cartao(const char *texto, int numero, size_t tmh_string)
{
    nodo_rb *novo_nodo;

    // Aloca espaço para o nó e para a chave
    if ( (novo_nodo = malloc(sizeof(*novo_nodo))) == NULL)
        return NULL;

    if ( (novo_nodo->chave = malloc(sizeof(struct cartao))) == NULL) {
        free(novo_nodo);
        return NULL;
    }

    ((struct cartao*)novo_nodo->chave)->texto = malloc(sizeof(char) * tmh_string);
    if (((struct cartao*)novo_nodo->chave)->texto == NULL) {
        free((struct cartao*) novo_nodo->chave);
        free(novo_nodo);
        return NULL;
    }

    // Inicializa chave
    strncpy( ((struct cartao*)novo_nodo->chave)->texto, texto, tmh_string - 1);
    ((struct cartao*)novo_nodo->chave)->texto[tmh_string - 1] = '\0';
    ((struct cartao*)novo_nodo->chave)->numero = numero;

    return novo_nodo;
}

void libera_nodo_cartao(nodo_rb *nd, void *uu)
{
    (void) uu;

//    if (nd != NULL) {
//        if ( (struct cartao *)nd->chave != NULL) {
            free(((struct cartao *) nd->chave)->texto);
//        }
        free( (struct cartao *) nd->chave);
//    }
    free(nd);
}

void imprime_nodo(nodo_rb *nd, void* uu)
{
    (void) uu;

    printf("%s", ((struct cartao*)nd->chave)->texto);
}

void processa_trio(arvore_rb *t, int soma)
{
    /* Basicamente resolve o problema da soma do subconjunto para o caso especial em que n=3 */
    struct cartao chave_procurada;
    nodo_rb *n0, *n1, *n2;
    nodo_rb *novo_nodo;
    size_t tmh_string = 0;

    chave_procurada.texto = NULL;
    n0 = arvore_minimo(t);
    while (n0 != ARVORE_NULL)
    {
        n1 = arvore_sucessor(n0);
        while (n1 != ARVORE_NULL)
        {
            chave_procurada.numero = soma - ((struct cartao*) n0->chave)->numero - ((struct cartao*) n1->chave)->numero;
            n2 = arvore_buscar(t, &chave_procurada);

            if (n2 != NULL)
            {
                // Computar tamanho da string antes de alocar espaço suficiente na memória
                tmh_string += strlen(((struct cartao*) n0->chave)->texto);
                tmh_string += strlen(((struct cartao*) n1->chave)->texto);
                tmh_string += strlen(((struct cartao*) n2->chave)->texto);

                // Cria um novo nó correspondente ao trio encontrado. Note que esse tmh_string+1 serve pra guardar o caractere nulo.
                novo_nodo = cria_nodo_cartao(((struct cartao*) n0->chave)->texto, soma, tmh_string + 1);

                // Concatena as próximas duas strings ao texto
                strcat(((struct cartao*) novo_nodo->chave)->texto, ((struct cartao*) n1->chave)->texto);
                strcat(((struct cartao*) novo_nodo->chave)->texto, ((struct cartao*) n2->chave)->texto);

                // Remove os nós antigos
                libera_nodo_cartao(arvore_deletar_nodo(t, n2), NULL);
                libera_nodo_cartao(arvore_deletar_nodo(t, n1), NULL);
                libera_nodo_cartao(arvore_deletar_nodo(t, n0), NULL);

                arvore_inserir(t, novo_nodo);
                return;
            }

            n1 = arvore_sucessor(n1);
        }

        n0 = arvore_sucessor(n0);
    }
}

int ler_mensagem(arvore_rb *t)
{
    nodo_rb *novo_nodo;
    char buffer_entrada[MAX_TEXTO_MSG];
    int numero_cartao;
    int soma_autoridade;
    int m, n;
    int i;

    // Lê os inteiros m, n
    if (scanf("%d %d ", &m, &n) == EOF) return EOF;

    // Lê os cartões
    for (i = 0; i < m; i++)
    {
        //TODO: Ainda não descobri como subtrair números com macros. Deveria ser MAX_TEXTO_MSG - 1
        scanf("%d %*[\"]%" STR(MAX_TEXTO_MSG) "[^\"]%*[\"]", &numero_cartao, buffer_entrada);
        // Não vale a pena chamar um strlen() aqui, mais fácil colocar o tamanho máximo da string de entrada.
        novo_nodo = cria_nodo_cartao(buffer_entrada, numero_cartao, MAX_TEXTO_MSG);
        arvore_inserir(t, novo_nodo);
    }

    // Para cada "autoridade", concatena os trios correspondentes.
    for (i = 0; i < n; i++)
    {
        scanf("%d", &soma_autoridade);
        processa_trio(t, soma_autoridade);
    }

    // Imprime a árvore final em ordem
    percorrer_inordem(t, imprime_nodo, NULL);
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
