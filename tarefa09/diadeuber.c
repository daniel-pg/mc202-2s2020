/**
 * Daniel Paulo Garcia © 2020
 *
 * diadeuber.c
 *
 * Descrição: Recebe um histórico de eventos diários do Uber, e imprime um relatório das ações realizadas em cada
 * corrida, bem como as estatísticas de quilômetros rodados, rendimento bruto e líquido e gastos ao fim do dia.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heapq.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define MAX_CLIENTES 256
#define MAX_NOME 15

struct cliente
{
    char nome[MAX_NOME];
    double avaliacao;
    int pos_origem[2];
    int pos_destino[2];
    bool eh_passageiro;
};

int cmp_clientes(const void *c1, const void *c2)
{
    // Se o cliente já é passageiro, então obviamente ele tem prioridade independentemente da sua avaliação.
    if (((struct cliente*) c1)->eh_passageiro)
        return 1;
    else if (((struct cliente*) c2)->eh_passageiro)
        return -1;

    double a1 = ((struct cliente*) c1)->avaliacao;
    double a2 = ((struct cliente*) c2)->avaliacao;

    // É seguro comparar dois 'double' por igualdade nesse caso, pois os valores nunca são alterados algebricamente
    if (a1 == a2)
        return 0;
    else if ( (a1 - a2) > 0)
        return 1;
    else
        return -1;
}

static int distancia_de_manhattan(int pos1[], int pos2[])
{
    return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]);
}

static void aceita_solicitacao(heapq_t *fila_corridas)
{
    struct cliente *novo_cliente;
    novo_cliente = malloc(sizeof(*novo_cliente));

    scanf(" %" STR(MAX_NOME) "s" "%lf %d %d %d %d",
          novo_cliente->nome,
          &novo_cliente->avaliacao,
          &novo_cliente->pos_origem[0], &novo_cliente->pos_origem[1],
          &novo_cliente->pos_destino[0], &novo_cliente->pos_destino[1]);

    if (fila_corridas->len == 0)
        novo_cliente->eh_passageiro = true;
    else
        novo_cliente->eh_passageiro = false;

    heapq_inserir(fila_corridas, novo_cliente);
    printf("Cliente %s foi adicionado(a)\n", novo_cliente->nome);
}

static void finaliza_corrida(heapq_t *fila_corridas, int *km_total, double *rend_bruto, int pos_motorista[])
{
    struct cliente *cliente_atendido;
    int dist_percorrida;

    const double pagamento_por_km = 1.4;

    cliente_atendido = heapq_extrai_max(fila_corridas);

    if (fila_corridas->len > 0)
        ((struct cliente *) fila_corridas->chaves[0])->eh_passageiro = true;


    *km_total += distancia_de_manhattan(pos_motorista, cliente_atendido->pos_origem);
    pos_motorista[0] = cliente_atendido->pos_origem[0];
    pos_motorista[1] = cliente_atendido->pos_origem[1];

    dist_percorrida = distancia_de_manhattan(pos_motorista, cliente_atendido->pos_destino);
    pos_motorista[0] = cliente_atendido->pos_destino[0];
    pos_motorista[1] = cliente_atendido->pos_destino[1];
    *km_total += dist_percorrida;
    *rend_bruto += pagamento_por_km * dist_percorrida;

    printf("A corrida de %s foi finalizada\n", cliente_atendido->nome);
    free(cliente_atendido);
}

static void cancela_corrida(heapq_t *fila_corridas)
{
    char nome_cliente_cancelado[MAX_NOME];
    struct cliente *cliente_cancelado = NULL;

    scanf(" %" STR(MAX_NOME) "s", nome_cliente_cancelado);

    // Procura pelo cliente que quer cancelar a corrida através de uma busca linear
    for (size_t i = 0; i < fila_corridas->len; i++)
    {
        if ( strcmp(nome_cliente_cancelado, ((struct cliente*) fila_corridas->chaves[i])->nome) == 0) {
            cliente_cancelado = heapq_extrair(fila_corridas, i);
            break;
        }
    }

    printf("%s cancelou a corrida\n", nome_cliente_cancelado);
    free(cliente_cancelado);
}

static void imprime_relatorio_final(int km_total, double rend_bruto)
{
    // Constantes dadas no problema
    const double custo_aluguel_diario = 57.0;
    const double custo_por_km_rodado = 0.4104;
    const double taxa_uber = 0.25;

    // Valores calculados
    const double despesas = km_total * custo_por_km_rodado + custo_aluguel_diario;
    const double rend_liquid = (1.0 - taxa_uber) * rend_bruto - despesas;

    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", km_total);
    printf("Rendimento bruto: %.2lf\n", rend_bruto);
    printf("Despesas: %.2lf\n", despesas);
    printf("Rendimento liquido: %.2lf\n", rend_liquid);
}

static void le_processa_entrada(heapq_t *fila_corridas)
{
    int pos_motorista[2] = {0, 0};
    double rend_bruto = 0;
    int km_total = 0;
    char operacao;

    const double taxa_cancelamento = 7.0;

    do {
        scanf(" %c", &operacao);

        switch (operacao)
        {
            case 'A':
                /* O motorista aceitou a solicitação de um cliente, deixando-o em espera. */
                aceita_solicitacao(fila_corridas);
                break;

            case 'F':
                /* O motorista finalizou a corrida atual. */
                finaliza_corrida(fila_corridas, &km_total, &rend_bruto, pos_motorista);
                break;

            case 'C':
                /* O cliente indicado cancelou sua solicitação. */
                cancela_corrida(fila_corridas);
                rend_bruto += taxa_cancelamento;
                break;

            case 'T':
                /* O motorista indicou o término da sua jornada e deseja ver o rendimento obtido. */
                imprime_relatorio_final(km_total, rend_bruto);
                break;

            default:
                break;
        }

    } while (operacao != 'T');
}

int main(void)
{
    heapq_t *fila_corridas = heapq_criar(MAX_CLIENTES, cmp_clientes);

    le_processa_entrada(fila_corridas);

    heapq_destroi(fila_corridas);
    return 0;
}
