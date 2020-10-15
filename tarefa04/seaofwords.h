//
// Created by danielpg on 06/10/2020.
//

#ifndef TAREFA04_SEAOFWORDS_H
#define TAREFA04_SEAOFWORDS_H

struct cacapalavras
{
    char *matriz;
    int n, m;
};

struct pistas
{
    char *palavras;
    int q;
};

void le_cacapalavras(struct cacapalavras *c, int n, int m);
void le_pistas(struct pistas *p, int q);
void escreve_cacapalavras(const struct cacapalavras *c);
void escreve_pistas(const struct pistas *p);
void procura_palavras(struct cacapalavras *c, const struct pistas *p, bool *resultados);
bool encontra_palavra_na_posicao(struct cacapalavras *c, const char *palavra, unsigned int tmh_palavra, int index, int i, int j);
void imprime_resultados(const bool *resultados, int q);

#endif //TAREFA04_SEAOFWORDS_H
