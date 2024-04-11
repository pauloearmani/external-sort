#include <stdio.h>
#include <stdlib.h>
#include "intercalacao.h"
#include "heap.h"

void criaFitas()
{
    FILE *arq;
    char nome[] = "bin/fita00.bin";

    for (int i = 0; i < NUM_FITAS; i++)
    {

        nome[8] = i / 10 + '0';
        nome[9] = i % 10 + '0';

        arq = fopen(nome, "wb");

        if (arq == NULL)
        {
            printf("Erro ao criar fita %d\n", i);
            return;
        }
        fclose(arq);
    }
}

int somatorioVetor(int vetor[], int n)
{
    int somatorio = 0;
    for (int i = 0; i < n; i++)
    {
        somatorio = somatorio + vetor[i];
    }
    return somatorio;
}

void selecao_por_substituicao(int *numLeitura, int *numEscrita, int *numComparacao,char *nomeBase,int numReg)
{

    Heap *heap;
    heap = criarHeap(TAM_MEM_INTERNA);

    // heap construido, agora recebe os registros e joga pro heap
    FILE *arquivoProvao = fopen(nomeBase, "r");
    char nomeFitaEntrada[] = "bin/fita00.bin";
    FILE *arquivoFita = fopen(nomeFitaEntrada, "ab");

    if (arquivoProvao == NULL)
        printf("\nFalha ao abrir o arquivo\n");
    if (arquivoFita == NULL)
        printf("\nFalha ao abrir o arquivo\n");

    int total = 0;
    int contadorRegistros = 0;
    // recebe os itens do provao, adiciona no registro com o marcador 0 e insere no heap
    for (int i = 0; i < TAM_MEM_INTERNA; i++)
    {
        tItem itemAux;
        tRegistro regAux;

        // le os registros do arquivo provao
        itemAux = leitor_de_registros(arquivoProvao);
        (*numLeitura)++;

        // salva na estrutra de registro o item, e deixa desmarcado
        regAux.item = itemAux;
        regAux.marcador = 0;
        // insere no heap
        inserir(heap, regAux, numComparacao);
    }

    int contaItensMarcados = 0;
    tRegistro novoReg, minReg;

    tItem marcaFim = {-1, 0, "", "", ""};
    do
    {
        do
        {
            // comparando o menor do heap com o novo registro para saber se o novo sera marcado
            minReg = extrairMinimo(heap, numComparacao);

            total++;
            contadorRegistros++;
            (*numEscrita)++;
            fwrite(&minReg.item, sizeof(tItem), 1, arquivoFita);
            if (contadorRegistros >= numReg)
            {
                (*numEscrita)++;
                fwrite(&marcaFim, sizeof(tItem), 1, arquivoFita);
                break;
            }
            (*numLeitura)++;
            novoReg.item = leitor_de_registros(arquivoProvao);

            (*numComparacao)++;
            if (minReg.item.nota > novoReg.item.nota)
            {
                novoReg.marcador = 1;
                contaItensMarcados++;
            }
            else
                novoReg.marcador = 0;

            inserir(heap, novoReg, numComparacao);
        } while (contaItensMarcados < TAM_MEM_INTERNA || minReg.marcador == 1);
        contaItensMarcados = 0;

        // Desmarco o Heap
        desmarcaHeap(heap);

        // printa um marcador de fim de bloco, onde a inscricao eh -1
        (*numEscrita)++;
        fwrite(&marcaFim, sizeof(tItem), 1, arquivoFita);

        // fecha a fita e abre a proxima
        fclose(arquivoFita);
        if (nomeFitaEntrada[9] == '0' + ((NUM_FITAS / 2) - 1))
        {
            nomeFitaEntrada[9] = '0';
        }
        else{
            incrementa_Nome(nomeFitaEntrada);
            }
        fopen(nomeFitaEntrada, "ab");

    } while (contadorRegistros < numReg);
    
    
    fclose(arquivoProvao);
    fclose(arquivoFita);
    desalocaHeap(heap);
}

void intercalacao_Balanceada_Fitas_entrada(int *numLeitura, int *numEscrita, int *numComparacao)
{

    // definicao dos nomes das fitas de entrada e saida
    char nomeArquivoEntrada[] = "bin/fita00.bin";

    char nomeArquivoSaida[] = "bin/fita00.bin";
    define_Nome_Fita_Saida(nomeArquivoSaida);

    // vetor de ponteiros de arquivos para a leitura e escrita das fitas
    FILE *arquivosEntrada[NUM_FITAS / 2];
    FILE *arquivosSaida[NUM_FITAS / 2];

    // Abre os arquivos de fita de entrada
    for (int i = 0; i < (NUM_FITAS / 2); i++)
    {
        arquivosEntrada[i] = fopen(nomeArquivoEntrada, "rb");
        if (arquivosEntrada[i] == NULL)
            printf("\n\nerro na abertura do arquivo(NULL): %s", nomeArquivoEntrada);
        incrementa_Nome(nomeArquivoEntrada);

        arquivosSaida[i] = fopen(nomeArquivoSaida, "wb");
        if (arquivosSaida[i] == NULL)
            printf("\n\nerro na abertura do arquivo(NULL): %s", nomeArquivoSaida);
        incrementa_Nome(nomeArquivoSaida);
    }

    // variavel auxiliar
    tItem auxItem;
    // simulação da memeoria interna
    tItem registros[NUM_FITAS / 2];
    tItem marcaFim = {-1, 0, "", "", ""};

    int atvFitas[NUM_FITAS / 2], marcador = 0;
    int k = 0;
    int acabaLoop = 0;
    do
    {
        // lendo os primeiros f registros, adiciono numa estrutura de dados ja ordenada
        // atualizo a atividade de cada fita
        for (int i = 0; i < NUM_FITAS / 2; i++)
        {
            atvFitas[i] = 1;
            (*numLeitura)++;
            if (fread(&registros[i], sizeof(tItem), 1, arquivosEntrada[i]) != 1)
            {
                atvFitas[i] = 0;
            }

            if (registros[i].inscricao < 0)
                atvFitas[i] = 0;
        }

        if (somatorioVetor(atvFitas, (NUM_FITAS / 2)) == 0)
            break;
        // processo de intercalação dos blocos

        do
        {

            if (somatorioVetor(atvFitas, (NUM_FITAS / 2)) == 0)
                break;
            // Defino o elemento base para comparar
            for (int i = 0; i < (NUM_FITAS / 2); i++)
            {
                if (atvFitas[i] == 1)
                {
                    auxItem = registros[i];
                    break;
                }
            }

            for (int i = 0; i < (NUM_FITAS / 2); i++)
            {
                if (atvFitas[i] == 0)
                {
                    continue;
                }
                else if (registros[i].nota <= auxItem.nota)
                {
                    auxItem = registros[i];
                    marcador = i;
                }
                (*numComparacao)++;
            }
            (*numEscrita)++;
            fwrite(&auxItem, sizeof(tItem), 1, arquivosSaida[k]);
            (*numLeitura)++;
            if (fread(&registros[marcador], sizeof(tItem), 1, arquivosEntrada[marcador]) != 1)
            {
                acabaLoop = 1;
                break;
                atvFitas[marcador] = 0;
            }
            if (registros[marcador].inscricao <= 0)
            {
                atvFitas[marcador] = 0;
            }

        } while (somatorioVetor(atvFitas, (NUM_FITAS / 2)) != 0);
        // finaliza o bloco

        if (acabaLoop == 1)
            break;
        (*numEscrita)++;
        fwrite(&marcaFim, sizeof(tItem), 1, arquivosSaida[k]);
        if (k < (NUM_FITAS / 2) - 1)
        {
            k++;
        }
        else
            k = 0;

    } while (1);

    // fecha os arquivos abertos
    for (int i = 0; i < (NUM_FITAS / 2); i++)
    {
        fclose(arquivosEntrada[i]);
        fclose(arquivosSaida[i]);
    }
}

void intercalacao_Balanceada_Fitas_Saida(int *numLeitura, int *numEscrita, int *numComparacao)
{

    // definicao dos nomes das fitas de entrada e saida
    char nomeArquivoEntrada[] = "bin/fita00.bin";

    char nomeArquivoSaida[] = "bin/fita00.bin";
    define_Nome_Fita_Saida(nomeArquivoSaida);

    // vetor de ponteiros de arquivos para a leitura e escrita das fitas
    FILE *arquivosEntrada[NUM_FITAS / 2];
    FILE *arquivosSaida[NUM_FITAS / 2];

    // Abre os arquivos de fita de entrada
    for (int i = 0; i < (NUM_FITAS / 2); i++)
    {
        arquivosEntrada[i] = fopen(nomeArquivoEntrada, "wb");
        if (arquivosEntrada[i] == NULL)
            printf("\n\nerro na abertura do arquivo(NULL): %s", nomeArquivoEntrada);
        incrementa_Nome(nomeArquivoEntrada);

        arquivosSaida[i] = fopen(nomeArquivoSaida, "rb");
        if (arquivosSaida[i] == NULL)
            printf("\n\nerro na abertura do arquivo(NULL): %s", nomeArquivoSaida);
        incrementa_Nome(nomeArquivoSaida);
    }

    // variavel auxiliar
    tItem auxItem;
    // simulação da memeoria interna
    tItem registros[NUM_FITAS / 2];
    tItem marcaFim = {-1, 0, "", "", ""};

    int atvFitas[NUM_FITAS / 2], marcador = 0;
    int k = 0;
    int acabaLoop = 0;
    do
    {
        // lendo os primeiros f registros, adiciono numa estrutura de dados ja ordenada
        // atualizo a atividade de cada fita
        for (int i = 0; i < NUM_FITAS / 2; i++)
        {
            atvFitas[i] = 1;
            (*numLeitura)++;
            if (fread(&registros[i], sizeof(tItem), 1, arquivosSaida[i]) != 1)
                atvFitas[i] = 0;

            if (registros[i].inscricao < 0)
                atvFitas[i] = 0;
        }

        if (somatorioVetor(atvFitas, (NUM_FITAS / 2)) == 0)
            break;
        // processo de intercalação dos blocos

        do
        {

            if (somatorioVetor(atvFitas, (NUM_FITAS / 2)) == 0)
                break;
            // Defino o elemento base para comparar
            for (int i = 0; i < (NUM_FITAS / 2); i++)
            {
                if (atvFitas[i] == 1)
                {
                    auxItem = registros[i];
                    break;
                }
            }

            for (int i = 0; i < (NUM_FITAS / 2); i++)
            {
                if (atvFitas[i] == 0)
                {
                    continue;
                }
                else if (registros[i].nota <= auxItem.nota)
                {
                    auxItem = registros[i];
                    marcador = i;
                }
                (*numComparacao)++;
            }
            (*numEscrita)++;
            fwrite(&auxItem, sizeof(tItem), 1, arquivosEntrada[k]);
            (*numLeitura)++;
            if (fread(&registros[marcador], sizeof(tItem), 1, arquivosSaida[marcador]) != 1)
            {
                acabaLoop = 1;
                break;
                atvFitas[marcador] = 0;
            }
            if (registros[marcador].inscricao <= 0)
            {
                atvFitas[marcador] = 0;
            }

        } while (somatorioVetor(atvFitas, (NUM_FITAS / 2)) != 0);
        // finaliza o bloco

        if (acabaLoop == 1)
            break;
        (*numEscrita)++;
        fwrite(&marcaFim, sizeof(tItem), 1, arquivosEntrada[k]);
        if (k < (NUM_FITAS / 2) - 1)
        {
            k++;
        }
        else
            k = 0;

    } while (1);

    // fecha os arquivos abertos
    for (int i = 0; i < (NUM_FITAS / 2); i++)
    {
        fclose(arquivosEntrada[i]);
        fclose(arquivosSaida[i]);
    }
}

int confere_Intercalacao()
{
    FILE *arquivo = fopen("bin/fita00.bin", "rb");
    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo...");
        return -1;
    }

    int quantidade = 0;
    tItem aux;
    aux.inscricao = -2;

    do
    {
        if (fread(&aux, sizeof(tItem), 1, arquivo) != 1)
            break;
        if (aux.inscricao < 0)
        {
            break;
        }
        quantidade++;
    } while (1);

    fclose(arquivo);
    return (quantidade);
}

void imprime_conteudo_fita()
{
    char nomeArquivo[] = "bin/fita00.bin";
    int c = 0;
    FILE *arquivo;
    for (int i = 0; i < NUM_FITAS; i++)
    {

        arquivo = fopen(nomeArquivo, "rb");
        printf("\n\nFita: %s", nomeArquivo);
        tItem aux;
        while (fread(&aux, sizeof(tItem), 1, arquivo) != 0)
        {
            if (aux.nota == -1)
            {
                printf("\n -----------------");
                break;
            }
            else
            {
                printf("\n%d)%ld - %lf", c, aux.inscricao, aux.nota);
                c++;
            }
        }
        fclose(arquivo);
    }
}