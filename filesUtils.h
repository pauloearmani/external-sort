#ifndef __FILES_UTILS
#define __FILES_UTILS

#include "estruturas.h"
#include <stdbool.h>
#include <stdlib.h>

// Função para converter um arquivo binário para texto e imprimir os dados
void binaryToTxtAndPrintData(Arguments *, char *);

// Função para gerar uma cópia do arquivo de entrada para um arquivo temporário
void generateCopyFile(Arguments *arguments, char *);

#endif
