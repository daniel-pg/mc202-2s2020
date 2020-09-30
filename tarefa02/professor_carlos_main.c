#include <stdio.h>
#include "professor_carlos.h"

#define MAX_SUBSTRING 6
#define MAX_TURMAS 50

void ler_turmas(Turma lista_turmas[], int n)
{
    Aluno entrada_aluno;
    Data entrada_data;
    int dia, mes, ano;
    int m; // Numero de alunos na turma

    for (size_t i = 0; i < n; i++)
    {
        scanf(" %d", &m);
        // O número de alunos por turma já é dado:
        lista_turmas[i].qtd = m;

        for (size_t j = 0; j < m; j++)
        {
            scanf(" %s %s %d %d %d", entrada_aluno.nome, entrada_aluno.sobrenome, &dia, &mes, &ano);
            entrada_data.dia = dia;
            entrada_data.mes = mes;
            entrada_data.ano = ano;
            entrada_aluno.nascimento = entrada_data;
            lista_turmas[i].alunos[j] = entrada_aluno;
            // Precisaria contar os alunos um a um:
            // add_aluno(lista_turmas, entrada_aluno, i);
        }
    }
}

void faz_operacao(Turma lista_turmas[], int operacao, int n)
{
    Aluno aluno_saida;
    Aluno aluno_entrada;
    Data data_entrada;
    char padrao[MAX_SUBSTRING];
    int contagem_substrings;
    int j;
    int dia, mes, ano;
    int qtd_alunos;

    switch (operacao)
    {
    case 1:
        scanf(" %d", &j);
        aluno_saida = procura_novo_na_turma(lista_turmas, n, j);
        printf("%s\n", aluno_saida.nome);
        break;

    case 2:
        scanf(" %d", &j);
        aluno_saida = procura_velho_na_turma(lista_turmas, n, j);
        printf("%s\n", aluno_saida.sobrenome);
        break;

    case 3:
        aluno_saida = procura_velho_todas_turmas(lista_turmas, n);
        printf("%s\n", aluno_saida.nome);
        break;

    case 4:
        aluno_saida = procura_novo_todas_turmas(lista_turmas, n);
        printf("%s\n", aluno_saida.sobrenome);
        break;

    case 5:
        scanf(" %s", padrao);
        contagem_substrings = conta_substrings(lista_turmas, n, padrao);
        printf("%d\n", contagem_substrings);
        break;

    case 6:
        scanf(" %d %s %s %d %d %d", &j, aluno_entrada.nome, aluno_entrada.sobrenome, &dia, &mes, &ano);
        data_entrada.dia = dia;
        data_entrada.mes = mes;
        data_entrada.ano = ano;
        aluno_entrada.nascimento = data_entrada;
        qtd_alunos = add_aluno(lista_turmas, aluno_entrada, j);
        printf("%d\n", qtd_alunos);
        break;

    case 7:
        /* Dado j, deve-se remover o ultimo aluno adicionado na turma j. Após removido,
            deve-se retornar quantos alunos a turma j possui no momento. */
        scanf(" %d", &j);
        qtd_alunos = remove_aluno(lista_turmas, j);
        printf("%d\n", qtd_alunos);
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
