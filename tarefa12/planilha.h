/**
 * Daniel Paulo Garcia © 2021
 *
 * planilha.h
 *
 * Descrição: Contém as estruturas de dados utilizadas para armazenar a tabela, bem como as funções
 * associadas a ela.
 */

#ifndef TAREFA12_PLANILHA_H
#define TAREFA12_PLANILHA_H

/* Máximo de caracteres que um "token" pode ter */
#define MAX_TOKEN 6

typedef struct celula_t
{
    int valor, tmh_formula;
    char (*formula)[MAX_TOKEN]; /* vetor de tokens//strings */

    /**
     * Guarda algumas informações úteis sobre cada célula
     * 
     * bit 0: célula já descoberta
     * bit 1: célula já visitada/finalizada
     * bit 2: célula contém um ciclo
     * bits 3-7: reservados! */
    unsigned char status;
} celula_t;

typedef struct planilha_t
{
    celula_t *planilha; /* matriz de células */
    int w, h;
} planilha_t;

/**
 * @brief Inicializa uma planilha previamente alocada na stack pelo usuário.
 * 
 * @param p Ponteiro para a planilha.
 */
void planilha_inicializar(planilha_t *p);


/**
 * @brief Libera a memória interna alocada pela planilha, mas não libera o ponteiro p!
 * 
 * @param p Ponteiro para a planilha.
 */
void planilha_liberar(planilha_t *p);


/**
 * @brief Converte a posição de uma célula da planilha da forma de coordenadas para o seu índice.
 * 
 * @param p Ponteiro para a planilha.
 * @param coord String contendo a coluna e a linha da planilha. Ex.: "A11" descreve a coluna 'A' na linha 11.
 * 
 * @return long Índice para o elemento na coordenada apontada.
 */
long planilha_coord_to_idx(planilha_t *p, const char *coord);


/**
 * @brief Imprime o valor de uma célula da planilha contendo um número ou uma fórmula.
 * 
 * @param p Ponteiro para a planilha.
 * @param coord String contendo a coluna e a linha da planilha.
 * @param idx Índice da célula na tabela (redundante ao parâmetro coord, mas evita recalcular o índice).
 */
void planilha_ler_celula(planilha_t *p, const char *coord, size_t idx);


/**
 * @brief Atualiza o valor de uma célula com um novo número. A célula não pode conter uma fórmula.
 * 
 * @param p Ponteiro para a planilha.
 * @param coord String contendo a coluna e a linha da planilha.
 * @param idx Índice da célula na tabela (redundante ao parâmetro coord, mas evita recalcular o índice).
 */
void planilha_escrever_celula(planilha_t *p, const char *coord, size_t idx);


/**
 * @brief Divide a string da fórmula em vários "tokens", e armazena-os na célula indicada.
 * 
 * @param celula Célula que se deseja atualizar a fórmula.
 * @param formula String contendo uma fórmula com os símbolos separados por espaços.
 */
void planilha_ler_formula(celula_t *celula, char *formula);


#endif //TAREFA12_PLANILHA_H
