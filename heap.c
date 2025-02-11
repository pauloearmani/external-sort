#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void trocar(tRegistro *a, tRegistro *b)
{
    tRegistro temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(Heap *heap, int indice, int *numComparacao)
{
    int menor = indice;
    int esquerdo = 2 * indice + 1;
    int direito = 2 * indice + 2;

    // Ordenar primeiro por marcado e depois por nota em caso de empate
    (*numComparacao)++;
    
    if (esquerdo < heap->tamanho &&
        (heap->array[esquerdo].marcador < heap->array[menor].marcador ||
         (heap->array[esquerdo].marcador == heap->array[menor].marcador &&
          heap->array[esquerdo].item.nota < heap->array[menor].item.nota)))
    {
        menor = esquerdo;
    }
    (*numComparacao)++;
    if (direito < heap->tamanho &&
        (heap->array[direito].marcador < heap->array[menor].marcador ||
         (heap->array[direito].marcador == heap->array[menor].marcador &&
          heap->array[direito].item.nota < heap->array[menor].item.nota)))
    {
        menor = direito;
    }

    if (menor != indice)
    {
        trocar(&heap->array[indice], &heap->array[menor]);
        minHeapify(heap, menor, numComparacao);
    }
}

tRegistro extrairMinimo(Heap *heap, int *numComparacao)
{
    tRegistro valorInvalido = {{0, 0.0, "", "", ""}, 0}; // Valor inválido para indicar erro

    if (heap->tamanho <= 0)
    {
        printf("Erro: Heap vazio.\n");
        return valorInvalido;
    }

    tRegistro raiz = heap->array[0];
    heap->array[0] = heap->array[heap->tamanho - 1];
    heap->tamanho--;

    minHeapify(heap, 0, numComparacao);

    return raiz;
}

void inserir(Heap *heap, tRegistro elemento, int *numComparacao)
{
    if (heap->tamanho == heap->capacidade)
    {
        printf("Erro: Heap cheio.\n");
        return;
    }

    int indice = heap->tamanho;
    heap->array[indice] = elemento;
    heap->tamanho++;

    while (indice != 0 &&
           (heap->array[indice].marcador < heap->array[(indice - 1) / 2].marcador ||
            (heap->array[indice].marcador == heap->array[(indice - 1) / 2].marcador &&
             heap->array[indice].item.nota < heap->array[(indice - 1) / 2].item.nota)))
    {
        (*numComparacao)++;
        trocar(&heap->array[indice], &heap->array[(indice - 1) / 2]);
        indice = (indice - 1) / 2;
    }
}

int marcaRegistro(tRegistro antigo,tRegistro novo){
    //se o novo for menor que o antigo retorna 1 
    if(antigo.item.nota > novo.item.nota){
        return 1;
    }else return 0;
}


void desalocaHeap(Heap *heap)
{
    free(heap->array);
}

Heap *criarHeap(int capacidade)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->capacidade = capacidade;

    if (heap == NULL)
    {
        // Falha na alocação da estrutura do heap
        return NULL;
    }

    heap->array = (tRegistro *)malloc(capacidade * sizeof(tRegistro));
    heap->tamanho = 0;
    return heap;
}

void imprimirHeap(Heap *heap)
{
    if (heap == NULL)
    {
        printf("Heap nulo.\n");
        return;
    }

    printf("Elementos do Heap:\n");
    for (int i = 0; i < heap->tamanho; i++)
    {
        printf("Nota: %.2f(%d),\n", heap->array[i].item.nota, heap->array[i].marcador);
    }
}

void desmarcaHeap(Heap *heap)
{
    for (int i = 0; i < heap->tamanho; i++)
    {
        heap->array[i].marcador = 0;
    }
}