/**
 * Daniel Paulo Garcia © 2020
 * 
 * megasena.c
 * 
 * Descrição: Dados um número "m" de jogadores com suas respectivas apostas, o
 * valor "n" do prêmio da Mega-Sena e os números sorteados, calcula o valor que
 * cada apostador deve receber e imprime na tela.
 *
 */

#include <stdio.h>
#include <stdint.h>

#define MAX_APOSTAS 1000
#define TAMANHO_VOLANTE 60
#define NUMEROS_SORTEADOS 6


/**
 * Lê um número m de matrizes binárias, correspondentes aos volantes de cada aposta, da entrada padrão.
 * 
 * @param lista_apostas Vetor de tamanho fixo, onde cada elemento corresponde a uma aposta individual a ser lida.
 * @param m Número de apostas. Deve ser menor ou igual a constante MAX_APOSTAS.
 * 
 */
void ler_apostas(uint64_t lista_apostas[], unsigned m)
{
    uint64_t entrada;

    for (size_t i = 0; i < m; i++)
    {
        lista_apostas[i] = 0;

        for (size_t j = 0; j < TAMANHO_VOLANTE; j++)
        {
            scanf(" %lu", &entrada);
            // * Etapa desnecessária, pois assume-se que a entrada sempre é válida (0 ou 1):
            // entrada &= 0x01;
            lista_apostas[i] |= (entrada << j); // Grava o bit de entrada na posição j do número.
        }
    }
}

/**
 * Lê uma lista de números sorteados da entrada padrão e os armazena no vetor dado.
 * 
 * @param lista_sorteados Vetor onde os valores lidos serão guardados.
 */
void ler_sorteados(unsigned lista_sorteados[])
{
    for (size_t i = 0; i < NUMEROS_SORTEADOS; i++)
    {
        scanf(" %u", &lista_sorteados[i]);
    }
}

/**
 *  Conta o número de acertos de cada aposta.
 * 
 * @param lista_acertos Vetor onde o número de acertos de cada aposta será guardado.
 * @param lista_apostas Vetor de números binários, cujos bits correspondem aos valores marcados no volante de cada aposta.
 * @param lista_sorteados Vetor contendo os números sorteados do jogo.
 * @param m Número de apostas. Deve ser menor ou igual a constante MAX_APOSTAS.
 */
void contar_acertos(unsigned lista_acertos[], uint64_t lista_apostas[], unsigned lista_sorteados[], unsigned m)
{
    unsigned acertos;

    for (size_t i = 0; i < m; i++)
    {
        acertos = 0;

        for (size_t j = 0; j < NUMEROS_SORTEADOS; j++)
        {
            if (((lista_apostas[i] >> (lista_sorteados[j] - 1)) & 0x01) == 0x01)
            {
                acertos++;
            }
        }

        lista_acertos[i] = acertos;
    }
}

/**
 * Conta quantas apostas acertaram uma determinada quantidade dos números sorteados.
 * 
 * @param lista_acertos Vetor contendo o número de acertos de cada aposta.
 * @param m Número de apostas. Deve ser menor ou igual a constante MAX_APOSTAS.
 * @param acertos Parâmetro que determina qual a quantidade de acertos de cada aposta contabilizada na contagem.
 * @return Retorna o número de premiados com a quantidade de acertos especificada. 
 */
unsigned contar_premiados(unsigned lista_acertos[], unsigned m, unsigned acertos)
{
    unsigned premiados = 0;

    for (size_t i = 0; i < m; i++)
    {
        if (lista_acertos[i] == acertos)
        {
            premiados++;
        }
    }

    return premiados;
}

/**
 * Lista os valores dos prêmios de cada aposta.
 * 
 * @param lista_acertos Vetor contendo o número de acertos de cada aposta.
 * @param contagem_premiados Vetor contendo o número de premiados na quadra, na quina e na sena, respectivamente.
 * @param m Número de apostas. Deve ser menor ou igual a constante MAX_APOSTAS.
 * @param n Valor do prêmio.
 */
void listar_premios(unsigned lista_acertos[], unsigned contagem_premiados[], unsigned m, double n)
{
    double valores_premios[3] = {0.0, 0.0, 0.0};

    // Caso não hajam premiados na quadra, quina ou sena, previne uma divisão por zero.
    if (contagem_premiados[0] > 0)
        valores_premios[0] = (0.19 * n) / contagem_premiados[0]; // Premiados na quadra

    if (contagem_premiados[1] > 0)
        valores_premios[1] = (0.19 * n) / contagem_premiados[1]; // Premiados na quina

    if (contagem_premiados[2] > 0)
        valores_premios[2] = (0.62 * n) / contagem_premiados[2]; // Premiados na sena

    for (size_t i = 0; i < m; i++)
    {
        switch (lista_acertos[i])
        {
        case 4:
            printf("%.2lf\n", valores_premios[0]);
            break;
        case 5:
            printf("%.2lf\n", valores_premios[1]);
            break;
        case 6:
            printf("%.2lf\n", valores_premios[2]);
            break;

        default:
            printf("%.2lf\n", 0.0);
            break;
        }
    }
}

int main(void)
{
    unsigned m;
    double n;
    uint64_t lista_apostas[MAX_APOSTAS];
    unsigned lista_acertos[MAX_APOSTAS];
    unsigned lista_sorteados[NUMEROS_SORTEADOS];

    scanf(" %u %lf", &m, &n);
    ler_apostas(lista_apostas, m);
    ler_sorteados(lista_sorteados);
    contar_acertos(lista_acertos, lista_apostas, lista_sorteados, m);

    unsigned contagem_premiados[3];
    for (size_t i = 0; i < 3; i++)
    {
        contagem_premiados[i] = contar_premiados(lista_acertos, m, i + 4);
    }

    listar_premios(lista_acertos, contagem_premiados, m, n);
    return 0;
}
