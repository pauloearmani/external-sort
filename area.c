#include "area.h"
#include "estruturas.h"
#include <stdio.h>

// Insere um registro ordenadamente em uma área
bool insertRegister(Register *reg, Area *area, Runtime *__run) {
  // Verifica se a área está cheia
  if (area->n >= 10)
    return false;

  // Encontra a posição correta para inserção do registro
  int index = 0;
  for (size_t i = 0; i < area->n; i++) {
    __run->comparisonCount += 1;
    // Compara o grau do registro com o grau na posição atual da área
    if (reg->grade <= area->area[i].grade)
      break;

    index++;
  }

  // Desloca os registros para abrir espaço para o novo registro
  for (int i = area->n - 1; i >= index; i--) {
    area->area[i + 1] = area->area[i];
  }

  // Insere o registro na posição correta
  area->area[index] = *reg;
  (area->n)++;

  return true;
}

// Inicializa uma área, definindo o número de registros como zero
void initializeArea(Area *area) { area->n = 0; }

// Função de conveniência para inserir um item na área
void insertItem(Register UltLido, Area *Area, Runtime *__run) {
  insertRegister(&UltLido, Area, __run);
}

// Remove o último registro de uma área
void removeLast(Area *area, Register *R) {
  *R = area->area[area->n - 1];
  area->n--;
}

// Remove o primeiro registro de uma área
void removeFirst(Area *area, Register *R) {
  *R = area->area[0];

  // Desloca os registros restantes para preencher a lacuna
  for (int i = 0; i < area->n; i++)
    area->area[i] = area->area[i + 1];

  area->n--;
}
