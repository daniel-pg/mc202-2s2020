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

struct horario
{
    int hora, minutos;
};

void incrementa_horario(struct horario *horario)
{
    horario->minutos += 10;
    if (horario->minutos >= 60) {
        horario->minutos = 0;
        horario->hora++;
    }
    if (horario->hora >= 24) {
        horario->hora = 0;
    }
}

lista_ligada_t * le_entrada(void)
{
    lista_ligada_t *fila_pacientes = inicializa_lista(PACIENTE);
    struct paciente *paciente_atual;
    char buff_nome[MAX_NOME];
    int *id_atual;
    int c;

    while (true)
    {
        if (scanf("%*[\"]%49[^\"]%*[\"]", buff_nome) == EOF) break;

        if ( (paciente_atual = malloc(sizeof(*paciente_atual))) == NULL) exit(1);
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
                if ( (id_atual = malloc(sizeof(*id_atual))) == NULL) exit(1);
                *id_atual = c - '0';
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
    // Horário do início do atendimento.
    struct horario horario = {8, 0};

    // Cria filas de atendimento para cada especialidade e indica quantos profissionais estão disponíveis em cada fila.
    lista_ligada_t* filas_atendimento[NUM_ESPECIALISTAS];
    size_t tmh_filas_atendimento[NUM_ESPECIALISTAS] = {10, 2, 5, 3, 4, 7, 2, 1, 4};
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) filas_atendimento[i] = inicializa_lista(PACIENTE);

    // A fila de pacientes nunca é alterada uma vez criada, o que mudam são só as filas de atendimento e as listas dos
    // IDs dos atendimentos requisitados por cada paciente.
    lista_ligada_t *fila_pacientes = le_entrada();

    celula_t *celulaPacienteatual, *celulaIdAtual;
    struct paciente *pacienteAtual;
    int *idAtual;

    while (fila_pacientes->len > 0)
    {
        celulaPacienteatual = fila_pacientes->inicio;

        while (celulaPacienteatual != NULL)
        {
            pacienteAtual = (struct paciente*) celulaPacienteatual->valor;
            celulaIdAtual = pacienteAtual->lista_id->inicio;

            if (celulaIdAtual == NULL)
            {
                printf("%d:%d %s", horario.hora, horario.minutos, pacienteAtual->nome);
                libera_elemento_costura_lista(fila_pacientes, celulaPacienteatual, true);
            }

            idAtual = (int*) celulaIdAtual->valor;

            // Adiciona paciente ao fim ou início da fila de atendimento requisitado, de acordo com a sua prioridade, e
            // remove pendência de atendimento. Se o paciente já estiver ocupado, não faça nada.
            if (!pacienteAtual->ocupado && filas_atendimento[*idAtual - 1]->len < tmh_filas_atendimento[*idAtual - 1])
            {
                if (pacienteAtual->prioridade == PREFERENCIAL) {
                    insere_elemento(filas_atendimento[*idAtual - 1], pacienteAtual, 0);
                } else {
                    anexa_elemento(filas_atendimento[*idAtual - 1], pacienteAtual);
                }

                pacienteAtual->ocupado = true;
                retira_elemento(pacienteAtual->lista_id, 0, true);
            }

            celulaPacienteatual = celulaPacienteatual->prox;
        }

        for (int i = 0; i < NUM_ESPECIALISTAS; i++)
        {
            if (filas_atendimento[i]->len > 0)
            {
                pacienteAtual = (struct paciente*) filas_atendimento[i]->inicio->valor;
                pacienteAtual->ocupado = false;
                retira_elemento(filas_atendimento[i], 0, false);
            }
        }

        incrementa_horario(&horario);
    }

    // Libera memória e termina o programa.
    libera_lista(fila_pacientes, true);
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) libera_lista(filas_atendimento[i], false);
    return 0;
}
