/**
 * Daniel Paulo Garcia © 2020
 *
 * lista_ligada.h
 *
 * Descrição: Interface genérica para uma estrutura de dados do tipo lista ligada dupla.
 */

#ifndef TAREFA06_LISTA_LIGADA_H
#define TAREFA06_LISTA_LIGADA_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_NOME 50

typedef void* item_t;

enum tipo_lista {PACIENTE, ID};
enum prioridade {NORMAL, PREFERENCIAL};

typedef struct celula
{
    struct celula *prox;
    struct celula *ant;
    item_t valor;
} celula_t;

typedef struct lista_ligada
{
    celula_t *inicio;
    celula_t *fim;
    enum tipo_lista tipoLista;
    size_t len;
} lista_ligada_t;

struct paciente
{
    char nome[MAX_NOME];
    enum prioridade prioridade;
    lista_ligada_t *lista_id;
    bool ocupado;
};

// Aloca e inicializa uma lista ligada na memória.
lista_ligada_t * inicializa_lista(enum tipo_lista tipoLista);

// Remove todos os elementos da lista
void esvazia_lista(lista_ligada_t *lista, bool libera_valor);

// Libera todos os registros da célula antes de liberar a célula propriamente dita.
void libera_celula(celula_t *celula, enum tipo_lista tipoLista, bool libera_valor);

// Esvazia a lista e logo em seguida libera-a da memória.
void libera_lista(lista_ligada_t *lista, bool libera_valor);

// Libera/remove o elemento da lista e "costura" as pontas soltas da lista de volta.
void libera_elemento_costura_lista(lista_ligada_t *lista, celula_t *elemento);

// Insere elemento na posição anterior à especificada.
void insere_elemento(lista_ligada_t *lista, item_t item, size_t pos);

// Anexa elemento ao final da lista.
void anexa_elemento(lista_ligada_t *lista, item_t item);

// Concatena duas listas.
void concatena_listas(lista_ligada_t *nova_lista, lista_ligada_t *l1, lista_ligada_t *l2);

// Remove primeira ocorrência do elemento especificado da lista e devolve seu indice.
void remove_elemento(lista_ligada_t *lista, item_t item);

// Retira o elemento na posição especificada.
void retira_elemento(lista_ligada_t *lista, size_t pos);

// Copia a lista de origem para a lista de destino.
void copia_lista(lista_ligada_t *dest, lista_ligada_t *orig);

// Imprime todos os elementos da lista na saída padrão usando um separador especificado.
void imprime_lista(lista_ligada_t *lista, const char *sep);

// Mesma coisa da função imprime_lista(), exceto que os elementos da lista são impressos em ordem inversa.
void imprime_lista_inverso(lista_ligada_t *lista, const char *sep);

#endif //TAREFA06_LISTA_LIGADA_H
