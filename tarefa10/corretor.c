/**
 * Daniel Paulo Garcia © 2020
 *
 * corretor.c
 *
 * Descrição: Dado um dicionário de palavras, verifica quantas palavras de um texto qualquer estão grafadas
 * corretamente e quantas possuem um ou então mais de um erro de grafia. Um erro de grafia é caracterizado
 * pela remoção, inserção ou troca de um único caractere.
 */

#include <stdio.h>
#include <string.h> 

#include "hash_table.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)

static void inserir_variacoes(hash_table_t *ht, const char *chave)
{
    char tmp[MAX_PALAVRA];
    size_t i, len;
    char c;

    strcpy(tmp, chave);
    len = strlen(chave);

    // Insere chaves com letras trocadas.
    for (i = 0; i < len; i++)
    {
        c = chave[i];
        tmp[i] = '*';
        hashtable_inserir(ht, tmp, false);
        tmp[i] = c;
    }

    // Insere chaves com letras faltantes.
    for (i = len; i > 0; i--)
    {
        tmp[i - 1] = chave[i];
        hashtable_inserir(ht, tmp, false);
    }
    

    // Insere chaves com letras adicionais.
    tmp[0] = '*';
    strcpy(&tmp[1], chave);
    for (i = 0; i <= len; i++)
    {
        hashtable_inserir(ht, tmp, false);
        tmp[i] = tmp[i+1];
        tmp[i+1] = '*';
    }
}


static celula_t * busca_variacoes(hash_table_t *ht, char *chave)
{
    celula_t *encontrado = NULL;
    size_t i;
    char c;

    // Busca chaves com letras trocadas ou adicionais.
    for (i = 0; chave[i] != '\0'; i++)
    {
        c = chave[i];
        chave[i] = '*';

        encontrado = hashtable_buscar(ht, chave);
        if (encontrado != NULL) return encontrado;

        chave[i] = c;
    }

    return encontrado;
}

int main(void)
{
    hash_table_t *dicionario = hashtable_criar();
    celula_t *chave_encontrada;
    char entrada[MAX_PALAVRA];
    int n, q, i;

    scanf("%d %d", &n, &q);

    for (i = 0; i < n; i++)
    {
        scanf("%" STR(MAX_PALAVRA) "s", entrada);
        hashtable_inserir(dicionario, entrada, true);
        inserir_variacoes(dicionario, entrada);
    }

    for (i = 0; i < q; i++)
    {
        scanf("%" STR(MAX_PALAVRA) "s", entrada);

        chave_encontrada = hashtable_buscar(dicionario, entrada);

        if (chave_encontrada != NULL && chave_encontrada->dado) {
            printf("verde\n");
        } else if (chave_encontrada != NULL && !chave_encontrada->dado) {
            // Esse caso só ocorre quando uma palavra com letras faltando é buscada.
            printf("amarelo\n");
        } else {
            chave_encontrada = busca_variacoes(dicionario, entrada);
            
            if (chave_encontrada != NULL) {
                printf("amarelo\n");
            } else {
                printf("vermelho\n");
            }
        }
    }

    hashtable_destruir(dicionario);
    return 0;
}
