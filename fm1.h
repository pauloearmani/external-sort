#ifndef fm1
#define fm1

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "heapf1.h"
#include <string.h>

tItem leitor_de_registrosf1(FILE *arquivo);
void selecao_por_substituicaof1(int numRegs, int *comparacoes);
void readProvao(const char *txtFile, const char *binFile, long numReg);
void createTapes(int n);
void initTapes(int numRegs, int *comparacoes);
void binaryToTxt(const char *binaryFileName, const char *txtFileName);
void swap(ItemsHeap *a, ItemsHeap *b);
void heapify(ItemsHeap heap[], int n, int i, int* comparacoes);
void buildHeap(ItemsHeap heap[], int n, int *comparacoes);
int intercalateFM1(int *transfRead, int *transfWrite, int *comparacoes);
void formatFinalOutput(FILE *output, FILE *formatedOutput);
void callIntercalate(int *comparacoes);
void callFormatFinalOutput();
void switchNameFile(char *nameFile, int situacao);
int mainf1(int quantidade, int situacao, int opcional);

#endif