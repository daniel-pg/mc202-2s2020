// Necessário pro compilador reconhecer o ponteiro NULL;
#include <stdlib.h>
#include "professor_carlos.h"

#define MAX_TURMAS 50

/** Retorna um inteiro i=0 se s e t forem iguais, i<0 se s<t ou i>0 se s>t
 * Substitui a função strcmp() da biblioteca string.h (proibida nessa tarefa, por causa de... motivos!). */
int compara_string (const char *str1, const char *str2)
{
    int i;
    for (i = 0; str1[i] == str2[i]; i++)
    {
        if (str1[i] == '\0') return 0; // É garantido que t[i] == '\0' também nesse caso
    }
    unsigned char si = str1[i], ti = str2[i];
    return si - ti; // casting implicito pra int
}

int eh_substring_comeco(const char *s, const char *padrao)
{
    int i;

    for (i = 0; padrao[i] != '\0'; i++)
    {
        if (padrao[i] != s[i])
        {
            return 0;
        }
    }

    return 1;
}

/** Retorna a posição onde inicia o padrão na string, caso não seja encontrado o padrão retorna NULL
 * Substitui a função strstr() da biblioteca string.h (proibida nessa tarefa, por causa de... motivos!). */
char* procura_substring(char *s, char *padrao)
{
    while (*s != '\0')
    {
        if (*s == *padrao && eh_substring_comeco(s, padrao))
        {
            return s;
        }
        s++;
    }

    return NULL;
}


int compara_idade_alunos(Data a, Data b)
{
    if ( a.ano < b.ano || (a.ano == b.ano &&  (a.mes < b.mes || (a.mes == b.mes && a.dia < b.dia))) )
    {
        // Aluno "a" é maais velho.
        return 0;
    }
    else if (a.ano == b.ano && a.mes == b.mes && a.dia == b.dia)
    {
        // Mesma idade!
        return 1;
    }
    else
    {
        // Aluno "b" é mais velho.
        return 2;
    }
}

/** A funcao recebe todas as turmas e a turma escolhida,
 * retornando o aluno mais novo da turma escolhida. */
Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j)
{
    // assert(qtd_turmas > 0);

    Turma turma_j = t[j];
    Aluno aluno_mais_novo = turma_j.alunos[0]; // é garantido sempre ter um aluno.
    Aluno aluno_atual;
    Data nasc_aluno_novo;
    Data nasc_aluno_atual;
    int comp_nome;
    int comp_idade;
    int i;

    for (i = 0; i < turma_j.qtd; i++)
    {
        aluno_atual = turma_j.alunos[i];
        nasc_aluno_atual = aluno_atual.nascimento;
        nasc_aluno_novo = aluno_mais_novo.nascimento;
        comp_idade = compara_idade_alunos(nasc_aluno_novo, nasc_aluno_atual);

        if (comp_idade == 0)
        {
            aluno_mais_novo = aluno_atual;
        }
        else if (comp_idade == 1)
        {
            comp_nome = compara_string(aluno_atual.nome, aluno_mais_novo.nome);
            if (comp_nome < 0 || (comp_nome == 0 && compara_string(aluno_atual.sobrenome, aluno_mais_novo.sobrenome) < 0))
            {
                aluno_mais_novo = aluno_atual;
            }
        }

    }

    return aluno_mais_novo;
}

/** A funcao recebe todas as turmas e retorna o aluno mais novo dentre todas as turmas. */
Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas)
{
    // O motivo de fazer isso é poder reaproveitar a função procura_novo_na_turma, que recebe array.
    Turma turma_novos;
    Turma* ptr_turma_novos = &turma_novos;
    Aluno aluno_novo_atual;

    turma_novos.qtd = qtd_turmas;

    for (int i = 0; i < qtd_turmas; i++)
    {
        aluno_novo_atual = procura_novo_na_turma(t, qtd_turmas, i);
        turma_novos.alunos[i] =aluno_novo_atual;
    }

    return procura_novo_na_turma(ptr_turma_novos, 1, 0);
}

/** A funcao recebe todas as turma e o indice da turma escolhida,
 * retornando o aluno mais velho da turma escolhida. */
Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j)
{
    // assert(qtd_turmas > 0);

    Turma turma_j = t[j];
    Aluno aluno_mais_velho = turma_j.alunos[0]; // é garantido sempre ter um aluno.
    Aluno aluno_atual;
    Data nasc_aluno_velho;
    Data nasc_aluno_atual;
    int comp_nome;
    int comp_idade;
    int i;

    for (i = 0; i < turma_j.qtd; i++)
    {
        aluno_atual = turma_j.alunos[i];
        nasc_aluno_atual = aluno_atual.nascimento;
        nasc_aluno_velho = aluno_mais_velho.nascimento;
        comp_idade = compara_idade_alunos(nasc_aluno_velho, nasc_aluno_atual);

        if (comp_idade == 2)
        {
            aluno_mais_velho = aluno_atual;
        }
        else if (comp_idade == 1)
        {
            comp_nome = compara_string(aluno_atual.nome, aluno_mais_velho.nome);
            if (comp_nome < 0 || (comp_nome == 0 && compara_string(aluno_atual.sobrenome, aluno_mais_velho.sobrenome) < 0))
            {
                aluno_mais_velho = aluno_atual;
            }
        }

    }

    return aluno_mais_velho;
}

/** A funcao recebe todas as turmas e retorna o aluno mais velho dentre todas as turmas. */
Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas)
{
    // O motivo de fazer isso é poder reaproveitar a função procura_velho_na_turma, que recebe array.
    Turma turma_velhos;
    Turma* ptr_turma_velhos = &turma_velhos;
    Aluno aluno_velho_atual;

    // Não precisa contar os alunos um por um dentro do loop com a função add_aluno()
    turma_velhos.qtd = qtd_turmas;

    for (int i = 0; i < qtd_turmas; i++)
    {
        aluno_velho_atual = procura_velho_na_turma(t, qtd_turmas, i);
        turma_velhos.alunos[i] = aluno_velho_atual;
    }

    return procura_velho_na_turma(ptr_turma_velhos, 1, 0);
}

/** A funcao recebe todoas as turmas e uma string,
 * retornando a quantidade de alunos que a string aparece em seu nome. */
int conta_substrings(Turma t[], int qtd_turmas, char *padrao)
{
    int contagem_substring = 0;

    // Para cada turma...
    for (int i = 0; i < qtd_turmas; i++)
    {
        // Para cada aluno...
        for (int j = 0; j < t[i].qtd; j++)
        {
            if (procura_substring(t[i].alunos[j].nome, padrao) != NULL)
            {
                contagem_substring++;
            }
        }
    }

    return contagem_substring;
}

/** Adiciona o aluno A na turma j, retornando a quantidade de alunos da turma j. */
int add_aluno(Turma t[], Aluno A, int j)
{
    int qtd_alunos;

    t[j].qtd++;
    qtd_alunos = t[j].qtd;
    t[j].alunos[qtd_alunos - 1] = A;
    return qtd_alunos;
}

/** Remove o ultimo aluno adicionado na turma j,
 * retornando a quantidade de alunos restante na turma j. */
int remove_aluno(Turma t[], int j)
{
    int qtd_alunos;

    t[j].qtd--;
    qtd_alunos = t[j].qtd;
    // Não é necessário "apagar" o aluno efetivamente da lista.
    return qtd_alunos;
}
