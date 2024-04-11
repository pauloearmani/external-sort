#ifndef __QUICKSORT__
#define __QUICKSORT__

#include "area.h"
#include "estruturas.h"

// Função principal de ordenação externa usando QuickSort
void quickSort(Arguments *, char *, Runtime *);

// Função de particionamento para o algoritmo de ordenação externa
void externalQuickSort(FILE **, FILE **, FILE **, int, int, Runtime *);

// Funções auxiliares para leitura e escrita durante o processo de ordenação
void readSup(FILE **, Register *, int *, short *, Runtime *);
void readInf(FILE **, Register *, int *, short *, Runtime *);
void insertArea(Area *, Register *, int *, Runtime *);
void writeMax(FILE **, Register, int *, Runtime *);
void writeMin(FILE **, Register, int *, Runtime *);
void removeMax(Area *, Register *, int *);
void removeMin(Area *, Register *, int *);

// Função de particionamento para o QuickSort externo
void partition(FILE **, FILE **, FILE **, Area, int, int, int *, int *,
               Runtime *);

#endif
