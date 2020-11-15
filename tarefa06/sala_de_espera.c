/**
 * Daniel Paulo Garcia © 2020
 *
 * sala_de_espera.c
 *
 * Descrição: Dada uma lista de pacientes em ordem de chegada no hospital, com a descrição de nome, prioridade de
 * atendimento e atendimentos requisitados, devolve uma lista com os horários de saída de cada paciente.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_ligada.h"

#define NUM_ESPECIALISTAS 9

lista_ligada_t * le_entrada(void)
{
    lista_ligada_t *fila_pacientes = inicializa_lista(PACIENTE);
    struct paciente *paciente_atual;
    char buff_nome[MAX_NOME];
    int *id_atual;
    int c;

    while (true)
    {
        if (scanf("%[^\n]s", buff_nome) == EOF) break;

        if ( (paciente_atual = malloc(sizeof(*paciente_atual))) == NULL) exit(-1);
        anexa_elemento(fila_pacientes, paciente_atual);

        strcpy(paciente_atual->nome, buff_nome);

        scanf(" %s", buff_nome);
        if (strcmp(buff_nome, "preferencial") == 0) {
            paciente_atual->prioridade = PREFERENCIAL;
        } else {
            paciente_atual->prioridade = NORMAL;
        }

        paciente_atual->ocupado = false;
        paciente_atual->lista_id = inicializa_lista(ID);

        while ((c = getchar()) != '\n')
        {
            if (isdigit(c))
            {
                if ( (id_atual = malloc(sizeof(*id_atual))) == NULL) exit(-1);
                *id_atual = c;
                anexa_elemento(paciente_atual->lista_id, id_atual);
            }
            else if (c == EOF)
            {
                goto retorna;
            }
        }

    }

    retorna:
    return fila_pacientes;
}

int main(void)
{
    // Cria filas de atendimento para cada especialidade e indica quantos profissionais estão disponíveis em cada fila.
    lista_ligada_t* filas_atendimento[NUM_ESPECIALISTAS];
    size_t tmh_filas_atendimento[NUM_ESPECIALISTAS] = {10, 2, 5, 3, 4, 7, 2, 1, 4};
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) filas_atendimento[i] = inicializa_lista(PACIENTE);

    lista_ligada_t *fila_pacientes = le_entrada();

    libera_lista(fila_pacientes, true);
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) libera_lista(filas_atendimento[i], false);
    return 0;
}
