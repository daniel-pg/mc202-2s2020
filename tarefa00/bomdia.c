/*
 * Daniel Paulo Garcia © 2020
 * 
 * bomdia.c
 * 
 * Parte da primeira tarefa da disciplina de MC202!
 *
 */

#include <stdio.h>

#define MAX_NOME 30

int main(void)
{
    char nome[MAX_NOME];
    scanf("%s", nome);
    printf("Bom dia, %s.\n", nome);
    return 0;
}
