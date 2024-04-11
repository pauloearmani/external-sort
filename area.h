#ifndef AREA_H
#define AREA_H

#include "estruturas.h"

#define AREA_SIZE 10

// Definição da estrutura de dados 'Area' que contém um array de 'Register' e um
// contador 'n'
typedef struct TipoArea {
  Register area[AREA_SIZE];
  int n;
} Area;

// Inicializa a área, configurando o contador 'n' para zero
void initializeArea(Area *);

// Insere um item na área
void insertItem(Register, Area *, Runtime *__run);

// Remove o último item da área, retornando-o por referência
void removeLast(Area *, Register *);

// Remove o primeiro item da área, retornando-o por referência
void removeFirst(Area *, Register *);

#endif
