#include "heapf1.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

/* Funcoes Heap que usa nas funcoes de selecao  blocos ordenados*/

void trocarf1(tRegistro* a, tRegistro* b) {
    tRegistro temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapifyf1(Heap* heap, int indice, int *comparacoes) {
    int menor = indice;
    int esquerdo = 2 * indice + 1;
    int direito = 2 * indice + 2;

    (*comparacoes)++;
    // Ordenar primeiro por marcado e depois por nota em caso de empate
    if (esquerdo < heap->tamanho &&
        (heap->array[esquerdo].marcador < heap->array[menor].marcador ||
         (heap->array[esquerdo].marcador == heap->array[menor].marcador &&
          heap->array[esquerdo].item.nota < heap->array[menor].item.nota))) {
        menor = esquerdo;
    }
    (*comparacoes)++;
    if (direito < heap->tamanho &&
        (heap->array[direito].marcador < heap->array[menor].marcador ||
         (heap->array[direito].marcador == heap->array[menor].marcador &&
          heap->array[direito].item.nota < heap->array[menor].item.nota))) {
        menor = direito;
    }

    if (menor != indice) {
        trocarf1(&heap->array[indice], &heap->array[menor]);
        minHeapifyf1(heap, menor, comparacoes);
    }
}


tRegistro extrairMinimof1(Heap* heap, int *comparacoes) {
    tRegistro valorInvalido = {{0, 0.0, "", "", ""}, 0}; // Valor inválido para indicar erro

    if (heap->tamanho <= 0) {
        printf("Erro: Heap vazio.\n");
        return valorInvalido;
    }

    tRegistro raiz = heap->array[0];
    heap->array[0] = heap->array[heap->tamanho - 1];
    heap->tamanho--;

    minHeapifyf1(heap, 0, comparacoes);

    return raiz;
}

void inserirf1(Heap* heap, tRegistro elemento, int *comparacoes) {
    if (heap->tamanho == heap->capacidade) {
        printf("Erro: Heap cheio.\n");
        return;
    }
    
    int indice = heap->tamanho;
    heap->array[indice] = elemento;
    heap->tamanho++;

    while (indice != 0 &&
           (heap->array[indice].marcador < heap->array[(indice - 1) / 2].marcador ||
            (heap->array[indice].marcador == heap->array[(indice - 1) / 2].marcador &&
             heap->array[indice].item.nota < heap->array[(indice - 1) / 2].item.nota))) {
        (*comparacoes)++;
        trocarf1(&heap->array[indice], &heap->array[(indice - 1) / 2]);
        indice = (indice - 1) / 2;
    }
}
int marcaRegistrof1(tRegistro antigo,tRegistro novo){
    //se o novo for menor que o antigo retorna 1 
    if(antigo.item.nota > novo.item.nota){
        return 1;
    }else return 0;
}

void desalocaHeapf1(Heap* heap) {
    free(heap->array);
}

Heap* criarHeapf1(int capacidade){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->capacidade = capacidade;

    if (heap == NULL) {
        // Falha na alocação da estrutura do heap
        return NULL;
    }

    heap->array = (tRegistro*)malloc(capacidade * sizeof(tRegistro));
    heap->tamanho = 0;
    return heap;
}

void imprimirHeapf1(Heap* heap) {
    if (heap == NULL) {
        printf("Heap nulo.\n");
        return;
    }

    printf("Elementos do Heap:\n");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("Nota: %.2f(%d),\n",heap->array[i].item.nota,heap->array[i].marcador);
    }
}

void desmarcaHeapf1(Heap* heap){
    for(int i = 0; i < heap->tamanho; i++){
        heap->array[i].marcador = 0;
    }
}