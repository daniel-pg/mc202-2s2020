/*
 * Daniel Paulo Garcia © 2020
 * 
 * boanoite.c
 * 
 * Parte da primeira tarefa da disciplina de MC202!
 *
 */

#include <stdio.h>

#define MAX_NOME 30

int main(void)
{
    char nome[MAX_NOME];
    unsigned n;

    scanf("%u", &n);
    for (size_t i = 0; i < n; i++)
    {
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }
}
