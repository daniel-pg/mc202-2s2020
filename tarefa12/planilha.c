#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 32
#define MAX_TOKEN 4

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

int main(void)
{
    char nome_arquivo[MAX_NOME];
    planilha_t p;

    scanf("%s %d %d", nome_arquivo, &p.w, &p.h);
    planilha_inicializar(&p);

    free(p.planilha);
    return 0;
}
