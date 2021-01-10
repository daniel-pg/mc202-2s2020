/**
 * Daniel Paulo Garcia © 2021
 *
 * planilha.c
 *
 * Descrição: Lê um arquivo CSV contendo uma planilha com números e fórmulas, e realiza um conjunto de operações
 * especificados pelo usuário.
 */


#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "planilha.h"
#include "pilha.h"

/* Máximo de caracteres que uma linha da entrada pode ter */
#define MAX_LINHA 1024
/* Máximo de caracteres que o nome do arquivo pode ter */
#define MAX_NOME 32


#define XSTR(x) #x
#define STR(x) XSTR(x)

void planilha_inicializar(planilha_t *p)
{
    p->planilha = malloc(p->w * p->h * sizeof(celula_t));
    if (p->planilha == NULL)
        exit(1);
}

void planilha_liberar(planilha_t *p)
{
    size_t tmh_tabela = p->w * p->h;
    for (size_t i = 0; i < tmh_tabela; i++) {
        free(p->planilha[i].formula); // É sempre seguro dar free() num ponteiro nulo
    }
    free(p->planilha);
}

long planilha_coord_to_idx(planilha_t *p, const char *coord)
{
    long idx;
    int linha, ret;
    char col;

    ret = sscanf(coord, " %c%d", &col, &linha);
    if (ret != 2 || !isupper(col)) {
        /* leitura da coordenada a partir do token falhou */
        fprintf(stderr, "Coordenada invalida em: \"%s\"\n", coord);
        idx =  -1;
    }
    else {
        /* coordenada válida */
        idx = (linha - 1) * p->w + (col - 'A');
    }
    
    return idx;
}

static void planilha_ler_celula(planilha_t *p, const char *coord, size_t idx)
{
    assert(idx < ((size_t) p->w * (size_t) p->h));  // Checa se o índice da matriz é válido

    celula_t *cel_atual = &p->planilha[idx];

    if (cel_atual->tmh_formula == -1) {
        /* a célula contém apenas um número */
        printf("%s: %d\n", coord, cel_atual->valor);
    }
    else if (cel_atual->formula != NULL) {
        /* a célula contém uma fórmula */
        // TODO: Falta implementar
    }
    else {
        /* célula inválida */
        fprintf(stderr, "Coordenada invalida no índice: %lu\n", idx);
    }
}

static void planilha_escrever_celula(planilha_t *p, const char *coord, size_t idx)
{
    // TODO: Falta implementar essa operação

    printf("%s: %d", coord, p->planilha[idx].valor);
    scanf("%d", &p->planilha[idx].valor);

    // TODO: Recalcular valor da célula se for o caso.
    printf(" -> %d\n", p->planilha[idx].valor);
}

static void ler_formula(celula_t *celula, char *formula)
{
    celula->tmh_formula = 0;
    size_t i;
    char *token;

    // Pula o símbolo '=', que é inútil
    if (formula[0] == '=') formula += 2;

    // Conta o número de tokens antes de alocar o vetor de tokens
    token = strchr(formula, ' ');
    while (token != NULL) {
        celula->tmh_formula++;
        token = strchr(token+1, ' ');
    }

    celula->formula = malloc(celula->tmh_formula * sizeof(*celula->formula));
    if (celula->formula == NULL)
        exit(1);
    
    // Copia tokens de entrada para a célula
    token = strtok(formula, " ");
    for (i = 0; token != NULL; i++) {
        strcpy(celula->formula[i], token);
        token = strtok(NULL, " ");
    }
}

static void infixo_para_posfixo(celula_t *celula)
{
    // Célula ou fórmula inválida
    if (!celula || !celula->formula) {
        fprintf(stderr, "Conversao da notacao de infixo para pos-fixo falhou.");
        return;
    }

    pilha_t stk_op, stk_result;
    int i;
    char c;

    // TODO: Reimplementar essa função sem a pilha de resultado, se for possível
    pilha_inicializar(&stk_op, celula->tmh_formula);
    pilha_inicializar(&stk_result, celula->tmh_formula);

    for (i = 0; i < celula->tmh_formula; i++)
    {
        /* Lê primeiro caractere do token atual para determinar se ele contém um operador */
        c = celula->formula[i][0];

        if (c == '(' || c == '+' || c == '-') {
            /* se o token for um operador, adiciona-o à pilha de operadores */
            pilha_push(&stk_op, celula->formula[i]); // TODO: Implementar precedência de operadores?
        } else if (c == ')') {
            /* desempilha todos os elementos até fechar os parênteses */
            while (stk_op.stk[stk_op.slen - 1][0] != '(')
            {
                // ? Se não fosse garantido que a fórmula é válida, deveríamos também checar que: pilha.tmh > 0
                pilha_push(&stk_result, pilha_pop(&stk_op));
            }
            pilha_pop(&stk_op); // Remove o "abre parênteses"
        } else {
            /* se o token for um operando, adiciona-o ao resultado */
            pilha_push(&stk_result, celula->formula[i]);
        }
    }
    
    // ? Aqui caberia um realloc para economizar um pouco de memória, se valesse a pena.
    memcpy(celula->formula, stk_result.stk, stk_result.slen * sizeof(*stk_result.stk));
    celula->tmh_formula = stk_result.slen;

    free(stk_op.stk);
    free(stk_result.stk);
}

static void ler_arquivo_csv(planilha_t *p, const char *nome_arquivo)
{
    char linha[MAX_LINHA];
    char *token, *endptr;
    size_t i, j, idx;
    int num;

    FILE *arquivo_csv = fopen(nome_arquivo, "r");
    if (arquivo_csv == NULL) {
        perror("Falha ao tentar abrir o arquivo");
        exit(1);
    }
    
    // Lê o arquivo linha por linha
    for (i = 0; NULL != fgets(linha, MAX_LINHA, arquivo_csv); i++)
    {
        token = strtok(linha, ","); // Inicializa strtok()

        // Divide a linha em células da tabela
        for (j = 0; token != NULL; j++)
        {
            idx = i * p->w + j; // Índice da célula atual

            num = (int) strtol(token, &endptr, 10);
            if (token == endptr) {
                /* a célula contém uma fórmula */
                p->planilha[idx].valor = 0;
                ler_formula(&p->planilha[idx], token);
                infixo_para_posfixo(&p->planilha[idx]);
            }
            else if (num != 0 || errno == 0) {
                /* a célula contém um número */
                p->planilha[idx].valor = num;
                p->planilha[idx].formula = NULL;
                p->planilha[idx].tmh_formula = -1;
            }

            token = strtok(NULL, ",");  // Avança para o pŕoximo token
        }
    }
    
    fclose(arquivo_csv);
}

static void realiza_operacoes(planilha_t *p)
{
    size_t idx;
    char token[MAX_TOKEN];
    char op;

    while (EOF != scanf(" %c", &op))
    {
        // ! Deveria ser (MAX_TOKEN - 1)
        scanf(" %" STR(MAX_TOKEN) "s", token);
        idx = planilha_coord_to_idx(p, token);

        if (op == 'G') {
            /* ler uma célula e calcular o valor atual */
            planilha_ler_celula(p, token, idx);
        }
        else if (op == 'S') {
            /* atualizar uma célula e calcular o novo valor. É garantido que a célula a ser alterada contém
            um valor constante, e que o novo valor também será constante */
            planilha_escrever_celula(p, token, idx);
        }
        else {
            fprintf(stderr, "Operacao invalida!\n");
        }
    }
}

int main(void)
{
    char nome_arquivo[MAX_NOME];
    planilha_t p;

    // ! Deveria ser (MAX_NOME - 1), mas a linguagem C não permite de maneira prática.
    scanf("%" STR(MAX_NOME) "s %d %d", nome_arquivo, &p.w, &p.h);
    planilha_inicializar(&p);
    ler_arquivo_csv(&p, nome_arquivo);

    realiza_operacoes(&p);

    planilha_liberar(&p);
    return 0;
}
