#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void imprime_tabuleiro(int stk[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c%d\t", 'A' + i, stk[i] + 1);
    }
    printf("\n");
}

static bool eh_pos_valida(int stk[], int i, int j)
{
    /* retorna verdadeiro somente se a dama pode ser colocada na linha i e coluna j */
    for (int k = 0; k < j; k++)
    {
        // Estão na mesma horizontal ou na mesma diagonal
        if (stk[k] == i || (abs(stk[k] - i) == abs(k - j))) {
           return false;
        }
    }

   return true;
}

void ndamas(int n)
{
    int *stk;   // Pilha de posições fixadas das damas
    int slen;   // Tamanho da pilha
    int i;

    // Inicializa pilha
    stk = malloc(sizeof(*stk) * n);
    stk[0] = 0;
    slen = 1;

    /* enquanto nao fixou todas as damas */
    while (slen < n)
    {
        /*  procura uma posicao viável para a dama entre stk[slen]+1 e n */
        for (i = 0; i < n; i++)
        {
            if (eh_pos_valida(stk, i, slen)) {
                /* se encontrou posicao viável, fixa posicao e inicializa proxima dama */
                stk[slen] = i;
                slen++;
            } else {
                /* se nao encontrou, desafixa posicao */
                slen--;
            }
        }
    }

    printf("Solucao encontrada: ");
    imprime_tabuleiro(stk, n);
    free(stk);
}

int main(void)
{
    int n;
    printf("Insira o tamaho o tabuleiro: ");
    scanf("%d", &n);
    ndamas(n);
    return 0;
}
