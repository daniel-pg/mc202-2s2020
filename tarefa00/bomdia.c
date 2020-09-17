#include <stdio.h>

#define MAX_NOME 30

int main(void)
{
    char nome[MAX_NOME];
    scanf("%s", nome);
    printf("Bom dia, %s.\n", nome);
    return 0;
}
