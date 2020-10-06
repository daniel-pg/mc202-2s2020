/**
 * Daniel Paulo Garcia © 2020
 *
 * fakenews.h
 *
 * Descrição: ...
 *
 */

#ifndef TAREFA03_FAKENEWS_H
#define TAREFA03_FAKENEWS_H

typedef struct termo
{
    char *palavra;
    double *historico;
    double *maximo, *minimo;
    double media, desvpad;
} Termo;

Termo * alocaListaTermos(int n, int m);
void liberaListaTermos(Termo *lista_termos, int n);
char *** alocaMatrizPalavras(int linhas, int colunas);
void liberaMatrizPalavras(char ***matriz, int linhas);
void lerListaTermos(Termo *lista_termos, int n, int m);
void processaListaTermos(Termo *lista_termos, int n, int m);
void mostraListaTermos(Termo *lista_termos, int n, int m);
void mostraResultados(Termo *lista_termos, int n, int m);
int classificaTermo(double *maximo, double *minimo, double *media, double *desvpad);
double calculaMedia(double* historico, int m);
double calculaDesvPad(double* historico, double media, int m);
int calculaIndiceMaximo(double* historico, int m);
int calculaIndiceMinimo(double* historico, int m);


#endif //TAREFA03_FAKENEWS_H
