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

/* Máximo de caracteres que uma linha da entrada pode ter */
#define MAX_LINHA 1024
/* Máximo de caracteres que o nome do arquivo pode ter */
#define MAX_NOME 32
/* Máximo de caracteres que um "token" pode ter */
#define MAX_TOKEN 4


#define XSTR(x) #x
#define STR(x) XSTR(x)

typedef struct celula_t
{
    int valor, tmh_formula;
    char (*formula)[MAX_TOKEN]; /* vetor de tokens//strings */
} celula_t;

typedef struct planilha_t
{
    celula_t *planilha; /* matriz de células */
    int w, h;
} planilha_t;

static void planilha_inicializar(planilha_t *p)
{
    p->planilha = malloc(p->w * p->h * sizeof(celula_t));
    if (p->planilha == NULL)
        exit(1);
}

static void planilha_liberar(planilha_t *p)
{
    size_t tmh_tabela = p->w * p->h;
    for (size_t i = 0; i < tmh_tabela; i++) {
        free(p->planilha[i].formula); // É sempre seguro dar free() num ponteiro nulo
    }
    free(p->planilha);
}

static long planilha_coord_to_idx(planilha_t *p, const char *coord)
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

static void ler_formula(celula_t *celula, char formula[MAX_TOKEN])
{
    celula->tmh_formula = 0;
    size_t i;
    char *token;

    // Conta o número de tokens antes de alocar o vetor de tokens
    while (NULL != (token = strchr(formula, ' '))) {
        celula->tmh_formula++;
        token++;
    }

    celula->formula = malloc(celula->tmh_formula * sizeof(*celula->formula));
    if (celula->formula == NULL)
        exit(1);
    
    // Copia tokens de entrada para a célula
    for (i = 0; NULL != (token = strtok(formula, " ")); i++) {
        memcpy(celula->formula[i], token, MAX_TOKEN * sizeof(*token));
    }
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
            if (num == 0 && errno != 0) {
                /* a célula contém uma fórmula */
                p->planilha[idx].valor = 0;
                ler_formula(&p->planilha[idx], token);
                // TODO: Transformar a notação da fórmula de infixa para pós-fixa
            }
            else {
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
            // TODO: Falta implementar essa operação
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
