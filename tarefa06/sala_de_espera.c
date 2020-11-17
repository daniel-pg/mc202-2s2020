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

#define STR(x) XSTR(x)
#define XSTR(x) #x

struct horario
{
    unsigned hora, minutos;
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

void imprime_horario(struct horario horario, const char* nome)
{
    printf("%02d:%02d %s\n", horario.hora, horario.minutos, nome);
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
        if (scanf("%*[\"]%" STR(MAX_NOME) "[^\"]%*[\"]", buff_nome) == EOF) break; // TODO: Deveria ser MAX_NOME - 1

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

        while (scanf("%d", &c) == 1)
        {
            if ( (id_atual = malloc(sizeof(*id_atual))) == NULL) exit(1);
            *id_atual = c;
            anexa_elemento(paciente_atual->lista_id, id_atual);
        }

    }

    retorna:
    return fila_pacientes;
}

void processa_filas(lista_ligada_t *fila_pacientes, lista_ligada_t* filas_atendimento[], const size_t tmh_filas_atendimento[])
{
    // Horário do início do atendimento.
    struct horario horario = {8, 0};

    celula_t *celulaPacienteAtual, *celulaIdAtual;
    struct paciente *pacienteAtual;
    int *idAtual;

    while (fila_pacientes->len > 0)
    {
        celulaPacienteAtual = fila_pacientes->inicio;

        // Percorre fila de pacientes e redireciona-os para as devidas filas de atendimento.
        while (celulaPacienteAtual != NULL)
        {
            pacienteAtual = (struct paciente*) celulaPacienteAtual->valor;
            celulaIdAtual = pacienteAtual->lista_id->inicio;

            if (celulaIdAtual == NULL)
            {
                imprime_horario(horario, pacienteAtual->nome);
                celula_t *aux = celulaPacienteAtual;
                celulaPacienteAtual = celulaPacienteAtual->prox;
                libera_elemento_costura_lista(fila_pacientes, aux, true);
                continue;
            } else {
                idAtual = (int*) celulaIdAtual->valor;
            }

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

            celulaPacienteAtual = celulaPacienteAtual->prox;
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
}

/* Função usada apenas para debug (verificar os valores lidos pelo programa) */
void imprime_lista_prioridade(lista_ligada_t *lista)
{
    celula_t *atual = lista->inicio;

    while (atual != NULL)
    {
        printf("%d ", *((int*)(atual->valor)) );

        atual = atual->prox;
    }

    printf("\n");
}

/* Função usada apenas para debug (verificar os valores lidos pelo programa) */
void imprime_fila_pacientes(lista_ligada_t *fila)
{
    celula_t *atual = fila->inicio;
    struct paciente *paciente_atual;

    while (atual != NULL)
    {
        paciente_atual = (struct paciente*) atual->valor;
        printf("\"%s\"", paciente_atual->nome);

        if (paciente_atual->prioridade == PREFERENCIAL) {
            printf(" preferencial ");
        } else {
            printf(" normal ");
        }

        imprime_lista_prioridade(paciente_atual->lista_id);

        atual = atual->prox;
    }
}

int main(void)
{
    // Cria filas de atendimento para cada especialidade e indica quantos profissionais estão disponíveis em cada fila.
    lista_ligada_t* filas_atendimento[NUM_ESPECIALISTAS];
    size_t tmh_filas_atendimento[NUM_ESPECIALISTAS] = {10, 2, 5, 3, 4, 7, 2, 1, 4};
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) filas_atendimento[i] = inicializa_lista(PACIENTE);

    // Lê fila de pacientes da entrada e depois processa-a.
    lista_ligada_t *fila_pacientes = le_entrada();
    imprime_fila_pacientes(fila_pacientes);
    // processa_filas(fila_pacientes, filas_atendimento, tmh_filas_atendimento);

    // Libera memória e termina o programa.
    libera_lista(fila_pacientes, true);
    for (size_t i = 0; i < NUM_ESPECIALISTAS; i++) libera_lista(filas_atendimento[i], false);
    return 0;
}
