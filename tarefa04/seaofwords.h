//
// Created by danielpg on 06/10/2020.
//

#ifndef TAREFA04_SEAOFWORDS_H
#define TAREFA04_SEAOFWORDS_H

void le_cacapalavras(char *cacapalavras, int n, int m);
void le_pistas(char *pistas, int q);
void escreve_cacapalavras(const char *cacapalavras, int n, int m);
void escreve_pistas(char *pistas, int q);
void procura_palavras(char *cacapalavras, const char *palavras, bool *resultados, int n, int m, int q);
bool backtrack(char *cacapalavras, const char palavra[], int index, int i, int j, const int *n, const int *m);
void imprime_resultados(const bool *resultados, int q);

#endif //TAREFA04_SEAOFWORDS_H
