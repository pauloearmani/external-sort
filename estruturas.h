#ifndef ESTRTURAS_H
#define ESTRTURAS_H

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição do tipo 'TipoChave' como um alias para 'int'
typedef int TipoChave;

// Definição da estrutura 'Register' contendo campos para chave, nota, estado,
// cidade e curso
typedef struct {
  TipoChave key;
  double grade;
  char state[3];
  char city[51];
  char course[31];
} Register;

// Definição da estrutura 'Arguments' que contém informações sobre o método de
// ordenação, número de registros, situação, flag 'p' e nome do arquivo
typedef struct {
  int method;
  int nRegisters;
  int situation;
  bool p;

} Arguments;

// Definição da estrutura 'Runtime' que mede o tempo e mantém contadores de
// comparação e transferências
typedef struct {
  clock_t startToCreateTre, endToCreateTre;
  double totalTime;
  int comparisonCount;
  int transfersReadCount;
  int transfersWriteCount;
} Runtime;

#endif
