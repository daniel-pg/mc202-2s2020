/**
 * Daniel Paulo Garcia © 2021
 *
 * planilha.c
 *
 * Descrição: Lê um arquivo CSV contendo uma planilha com números e fórmulas, e realiza um conjunto de operações
 * especificados pelo usuário.
 */


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

static void ler_formula(celula_t *celula, char *formula)
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
    
    for (i = 0; NULL != (token = strtok(formula, " ")); i++) {
        strncpy(celula->formula[i], token, MAX_TOKEN - 1);
    }

    // É seguro apagar essa linha e trocar o limite do strncpy(), mas aí o compilador reclama.
    celula->formula[i][MAX_TOKEN - 1] = '\0';
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

int main(void)
{
    char nome_arquivo[MAX_NOME];
    planilha_t p;

    scanf("%" STR(MAX_NOME) "s %d %d", nome_arquivo, &p.w, &p.h);
    planilha_inicializar(&p);
    ler_arquivo_csv(&p, nome_arquivo);

    planilha_liberar(&p);
    return 0;
}
