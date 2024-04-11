#include <stdio.h>
#include "intercalacao.h"
#include "arquivo.h"
#include "heap.h"
#include <time.h>
#include "structures.h"


int main2f(int numReg, int ordemArquivo, int opcional)
{
    // variaveis para calcular o tempo
    clock_t inicio, fim;
    inicio = clock();

    // variavei para calcular a contagem
    int numLeitura = 0, numEscrita = 0, numComparacao = 0;
    
    // nome do arquivo que vai ser lido 
    char* nomeBase;
    
    
    switch (ordemArquivo)
    {
    case 1:
        nomeBase = "./arquivos/PROVAOASCENDENTE.TXT";
        break;
    case 2:
        nomeBase = "./arquivos/PROVAODESCENDENTE.TXT";
        break;
    case 3:
        nomeBase = "./arquivos/PROVAO.TXT";
        break;
    default:
        printf("\nErro na escolha do arquivo");
        return 0;
        break;
    }

    printf("\nCriacao das fitas para intercalacao...");
    criaFitas();



    printf("\n\n... Fase de selecao por substituicao ... ");
    selecao_por_substituicao(&numLeitura, &numEscrita, &numComparacao,nomeBase,numReg);



    printf("\n\n... Fase de intercalacao ... ");


    do
    {
        intercalacao_Balanceada_Fitas_entrada(&numLeitura, &numEscrita, &numComparacao);
        intercalacao_Balanceada_Fitas_Saida(&numLeitura, &numEscrita, &numComparacao);
        
    } while (confere_Intercalacao() != numReg);

    fim = clock();
    
    
    
    printf("\n\nTempo de execucao:\t%4f segundos\n\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("\nNumero de leitura:\t%d\n", numLeitura);
    printf("\nNumero de escrita:\t%d\n", numEscrita);
    printf("\nNumero de comparacoes:\t%d\n", numComparacao);
    printf("\n\n\n...Gerando registros ordenados...\n");
    
    //gera um arquivo com os registros ordenados em txt
    gera_registros_ordenados();

    printf("\n\n");
    if (opcional == 1) {
        printa_registros_ordenados();
    }

    return 0;
}