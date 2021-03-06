/**
 * Daniel Paulo Garcia © 2021
 *
 * planilha.c
 *
 * Descrição: Lê um arquivo CSV contendo uma planilha com números e fórmulas, e realiza um conjunto de operações
 * especificados pelo usuário.
 */

// Precisamos dessas coisinhas aqui porque essa linguagem C maravilinda precisa só pra usar o strtok_s()
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

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


static int resolver_posfixo(planilha_t *p, int idx, int *erro_ciclo)
{
    celula_t *vizinho, *cel_atual = &p->planilha[idx];
    int idx_token, result;
    int *stk_num, slen = 0;
    char c;

    // Marca como descoberto
    cel_atual->status |= (1UL << 0);

    // Não há como ter mais operadores do que operandos
    stk_num = malloc(sizeof(*stk_num) * (cel_atual->tmh_formula / 2 + 1));

    for (int i = 0; i < cel_atual->tmh_formula; i++)
    {
        c = cel_atual->formula[i][0];
        if (c == '+' || c == '-') {
            /* o token contém um operador */
            if (c == '+')
                stk_num[slen - 2] += stk_num[slen - 1];
            else if (c == '-')
                stk_num[slen - 2] -= stk_num[slen - 1];

            slen--;
        }
        else {
            /* o token contém uma referência a outra célula */
            idx_token = planilha_coord_to_idx(p, cel_atual->formula[i]);
            vizinho = &p->planilha[idx_token];

            if ((vizinho->status & 1UL) || (vizinho->status >> 2 & 1UL)) {
                /* se o vizinho já foi descoberto ou já tinha ciclo, ele contém um ciclo */
                cel_atual->status |= (1UL << 2); // ...e a própria célula atual também contém um ciclo
                *erro_ciclo = 1;
                result = 0;
                break;
            }
            else if (vizinho->formula == NULL || (vizinho->status >> 1) & 1UL) {
                /* se o vizinho for um número, ou então uma fórmula já finalizada, mas sem ciclo */
                stk_num[slen] = vizinho->valor;
            }
            else {
                /* o vizinho contém uma fórmula ainda não resolvida */
                stk_num[slen] = resolver_posfixo(p, idx_token, erro_ciclo);
            }
            slen++;
        }
    }
    
    cel_atual->status &= ~(1UL << 0); // Desmarca a célula como descoberta
    cel_atual->status |= (1UL << 1); // Finaliza célula

    if (!(*erro_ciclo)) result = stk_num[0]; // Se tudo correu bem, o valor que sobrou na pilha é o resultado
    cel_atual->valor = result;
    free(stk_num);
    return result;
}

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

void planilha_ler_celula(planilha_t *p, const char *coord, size_t idx)
{
    assert(idx < ((size_t) p->w * (size_t) p->h));  // Checa se o índice da matriz é válido

    celula_t *cel_atual = &p->planilha[idx];
    int result, erro_ciclo = 0;

    if (cel_atual->tmh_formula == -1) {
        /* a célula contém apenas um número */
        printf("%s: %d\n", coord, cel_atual->valor);
    }
    else if (cel_atual->formula != NULL) {
        /* a célula contém uma fórmula */
        result = resolver_posfixo(p, idx, &erro_ciclo);

        // Limpa status das células percorridas na busca em profundidade na hora de resolver a fórmula.
        // TODO: Percorrer apenas as células com fórmulas, ao invés da planilha toda
        for (int i = 0; i < p->w * p->h; i++) p->planilha[i].status &= ~(1UL << 1);
        
        cel_atual->valor = result;
        if (!erro_ciclo) {
            printf("%s: %d\n", coord, result);
        } else {
            printf("%s: #ERRO#\n", coord);
        }
    }
    else {
        /* célula inválida */
        fprintf(stderr, "Coordenada invalida no índice: %lu\n", idx);
    }
}

void planilha_escrever_celula(planilha_t *p, const char *coord, size_t idx)
{
    // É garantido que a célula alterada contém um valor constante
    printf("%s: %d", coord, p->planilha[idx].valor);
    scanf("%d", &p->planilha[idx].valor);
    printf(" -> %d\n", p->planilha[idx].valor);
}

void planilha_ler_formula(celula_t *celula, char *formula)
{
    celula->tmh_formula = 0;
    size_t i;
    char *token, *saveptr;

    // Pula o símbolo '=' e o espaço, que são inúteis
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
    token = strtok_r(formula, " ", &saveptr);
    for (i = 0; token != NULL; i++) {
        strcpy(celula->formula[i], token);
        token = strtok_r(NULL, " ", &saveptr);
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

    // Desempilha todos os operadores restantes
    while (stk_op.slen > 0)
    {
        pilha_push(&stk_result, pilha_pop(&stk_op));
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
    char *token, *endptr, *saveptr;
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
        linha[strcspn(linha, "\n")] = '\0'; // Remove quebra de linha pestilenta
        token = strtok_r(linha, ",", &saveptr); // Inicializa strtok()

        // Divide a linha em células da tabela
        for (j = 0; token != NULL; j++)
        {
            idx = i * p->w + j; // Índice da célula atual

            num = (int) strtol(token, &endptr, 10);
            if (token == endptr) {
                /* a célula contém uma fórmula */
                p->planilha[idx].valor = 0;
                planilha_ler_formula(&p->planilha[idx], token);
                infixo_para_posfixo(&p->planilha[idx]);
            }
            else if (num != 0 || errno == 0) {
                /* a célula contém um número */
                p->planilha[idx].valor = num;
                p->planilha[idx].formula = NULL;
                p->planilha[idx].tmh_formula = -1;
            }
            p->planilha[idx].status = 0x0;
            token = strtok_r(NULL, ",", &saveptr);  // Avança para o pŕoximo token
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
