#ifndef INTERCALACAO_H
#define INTERCALACAO_H

#include "arquivo.h"
#include "stdlib.h"
#include "structures.h"

/// @brief Numero de fitas que serão utilizadas
#define NUM_FITAS 20

#define TAM_MEM_INTERNA 10


// criação das fitas para manipulação dos dados
void criaFitas();

// criacao dos blocos ordenados por meio do metodo de selecao por substituicao
void selecao_por_substituicao(int*,int*,int*,char*,int);

// soma os elementos de um vetor e retorna o resultado
int somatorioVetor(int vetor[],int n);

// processo de interecalação de blocos que coloca o resultado na fita de saida
void intercalacao_Balanceada_Fitas_entrada(int*,int*,int*);

// processo de interecalação de blocos que coloca o resultado na fita de entrada
void intercalacao_Balanceada_Fitas_Saida(int*,int*,int*);

// verifica se a intercalação foi concluida, retorna o numero de registros de um bloco na fita de entrada
int confere_Intercalacao();

// imprime na tela o conteudo de todas as fitas de entrada e saida
void imprime_conteudo_fita();

#endif