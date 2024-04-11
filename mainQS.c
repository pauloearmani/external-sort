#include "estruturas.h"
#include "filesUtils.h"
#include "quick_sort.h"
#include <stdbool.h>
#include <stdio.h>

Runtime initializeRuntime() {
  Runtime __run = {0, 0, 0.0, 0, 0, 0};
  return __run;
}

int mainQS(int quantidade, int situacao, int opcional) {
  // Declaração de variáveis
  Arguments arguments;
  Runtime __run = initializeRuntime();
  char temp_bin[50];

  // Configuração dos argumentos a partir da linha de comando
  arguments.nRegisters = quantidade;
  arguments.method = 3; // Método específico (metodo 3 = QuickSort)
  if (opcional == 1) {
    arguments.p = true; // Flag 'p' inicializada como printar no terminal ou não;
  } else {
    arguments.p = false;
  }
  arguments.situation = situacao;

  // Geração do arquivo de cópia
  generateCopyFile(&arguments, temp_bin);

  // Ordenação externa utilizando quick sort
  quickSort(&arguments, temp_bin, &__run);

  // Conversão binária para texto e impressão dos dados
  binaryToTxtAndPrintData(&arguments, temp_bin);

  // Saída formatada dos resultados
  printf("---------------------------------------------------------------------"
         "--------"
         "------------\n");
  printf("Houve %d comparações para ordenação externa utilizando quick sort\n",
         __run.comparisonCount);
  printf("Houve %d transferências de leitura para ordenação externa utilizando "
         "quick sort\n",
         __run.transfersReadCount);
  printf("Houve %d transferências de escrita para ordenação externa utilizando "
         "quick sort\n",
         __run.transfersWriteCount);
  printf("Foi levado %fs finalizar a ordenação\n", __run.totalTime);
  printf("\n");

  return 0;
}
