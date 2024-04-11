#ifndef HEAPf1_H
#define HEAPf1_H

#include <stdio.h>
#include "structures.h"

Heap* criarHeapf1(int capacidade);


void desalocaHeapf1(Heap* heap);

void trocarf1(tRegistro* a, tRegistro* b) ;

void minHeapifyf1(Heap* heap, int indice, int *comparacoes);

tRegistro extrairMinimof1(Heap* heap, int *comparacoes);

void inserirf1(Heap* heap, tRegistro elemento, int *comparacoes);

int marcaRegistrof1(tRegistro,tRegistro);

void imprimirHeapf1(Heap* heap);

void desmarcaHeapf1(Heap* heap);


#endif