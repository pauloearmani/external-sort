#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include "arquivo.h"
#include "structures.h"


//cria um heap de acordo com a capacidade
Heap* criarHeap(int capacidade);

//desaloca o heap
void desalocaHeap(Heap* heap);

//troca 2 registros de posicao
void trocar(tRegistro* a, tRegistro* b) ;

//reconstitui o heap
void minHeapify(Heap* heap, int indice,int*);

//tira a base do heap e reconstitui
tRegistro extrairMinimo(Heap* heap,int*);

//insere um registro no heap
void inserir(Heap* heap, tRegistro elemento,int*);

//imprime o elemento do heap
void imprimirHeap(Heap* heap);

//tira a marcacao dos elementos do heap
void desmarcaHeap(Heap* heap);


#endif
