#include <stdio.h>
#include "professor_carlos.h"

#define MAX_NOME_SOBRENOME 15
#define MAX_SUBSTRING 6
#define MAX_TURMAS 50
#define MAX_ALUNOS 50
#define MAX_OPERACOES 50


void ler_turmas(Turma lista_turmas[], int n)
{
    Aluno entrada_aluno;
    Data entrada_data;
    int dia, mes, ano;
    int m; // Numero de alunos na turma

    for (size_t i = 0; i < n; i++)
    {
        scanf(" %d", &m);
        lista_turmas[i].qtd = m;

        for (size_t j = 0; j < m; j++)
        {
            scanf(" %s %s %d %d %d", &entrada_aluno.nome, &entrada_aluno.sobrenome, &dia, &mes, &ano);
            entrada_data.dia = dia;
            entrada_data.mes = mes;
            entrada_data.ano = ano;
            entrada_aluno.nascimento = entrada_data;
            lista_turmas[i].alunos[j] = entrada_aluno;
        }
    }
}


void faz_operacao(Turma lista_turmas[], int operacao, int n)
{
    int j;
    char padrao[MAX_SUBSTRING];

    switch (operacao)
        {
        case 1:
            scanf(" %d", &j);
            procura_novo_na_turma(lista_turmas, n, j);
            // nome
            break;

        case 2:
            scanf(" %d", &j);
            procura_velho_na_turma(lista_turmas, n, j);
            // sobrenome
            break;

        case 3:
            procura_velho_todas_turmas(lista_turmas, n);
            // nome
            break;

        case 4:
            procura_novo_todas_turmas(lista_turmas, n);
            // sobrenome
            break;

        case 5:
            scanf(" %s", &padrao);
            conta_substrings(lista_turmas, n, padrao);
            break;

        case 6:
            /* Dados j, nome, sobrenome, dia, mês, e ano de nascimento, deve-se adicionar
            um novo aluno contendo o nome, sobrenome, dia, mês e ano de nascimento, informados
            previamente, na j-ésima turma. Após adicionado, deve-se retornar quantos alunos
            a turma j possui no momento. */
            break;

        case 7:
            /* Dado j, deve-se remover o ultimo aluno adicionado na turma j. Após removido,
            deve-se retornar quantos alunos a turma j possui no momento. */
            break;

        default:
            break;
        }
}

int main(void)
{
    Turma lista_turmas[MAX_TURMAS];

    int n, k;
    int operacao;

    scanf(" %d %d", &n, &k);
    ler_turmas(lista_turmas, n);

    for (size_t i = 0; i < k; i++)
    {
        scanf(" %d", &operacao);
        faz_operacao(lista_turmas, operacao, n);
    }

    return 0;
}
