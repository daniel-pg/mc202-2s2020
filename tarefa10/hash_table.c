/**
 * Daniel Paulo Garcia © 2020
 *
 * hash_table.c
 *
 * Descrição: Implementa as funções do módulo hash_table.h
 */

#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

hash_table_t * hashtable_criar()
{
    hash_table_t *nova_tabela = malloc(sizeof(hash_table_t));
    if (nova_tabela == NULL)
        return NULL;

    // Inicializa todas as posições da tabela com listas vazias.
    for (size_t i = 0; i < TMH_TABELA; i++) {
        nova_tabela->tabela[i].inicio = NULL;
        nova_tabela->tabela[i].fim = NULL;
        nova_tabela->tabela[i].len = 0;
    }

    return nova_tabela;
}

void hashtable_destruir(hash_table_t *ht)
{
    free(ht);
}

static size_t hashtable_hash(char *chave)
{
    size_t i, n = 0;

    for (i = 0; i < strlen(chave); i++) {
        n = ((n << 8 * sizeof(char)) + chave[i]) % TMH_TABELA;
    }
    
    return n;
}

void hashtable_inserir(hash_table_t *ht, char *chave)
{
    size_t idx = hashtable_hash(chave);
    celula_t *elemento_antigo = __buscar_chave(&ht->tabela[idx], chave);

    if (elemento_antigo == NULL) {
        lista_anexar_fim(&ht->tabela[idx], chave);
    }
}

void hashtable_deletar(hash_table_t *ht, char *chave)
{
    size_t idx = hashtable_hash(chave);
    lista_remover(&ht->tabela[idx], chave);
}

static celula_t * __buscar_chave(lista_ligada_t *l, char *chave)
{
    celula_t *atual = l->inicio;

    while (atual != NULL && strcmp(atual->valor, chave) != 0) {
        atual = atual->prox;
    }
    
    return atual;
}

celula_t * hashtable_buscar(hash_table_t *ht, char *chave)
{
    size_t idx = hashtable_hash(chave);
    return __buscar_chave(&ht->tabela[idx], chave);
}
