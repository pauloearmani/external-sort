#include "estruturas.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Função para gerar uma cópia do arquivo de entrada para um arquivo temporário
void generateCopyFile(Arguments *arguments, char *temp_bin) {
  FILE *arq;

  // Seleção do arquivo de entrada com base na situação
  if (arguments->situation == 1) {
    arq = fopen("./arquivos/PROVAO_ASCENDENTE.bin", "rb");

  } else if (arguments->situation == 2) {
    arq = fopen("./arquivos/PROVAO_DECRESCENTE.bin", "rb");

  } else {
    arq = fopen("./arquivos/PROVAO_ALEATORIO.bin", "rb");
  }

  // Lendo os n primeiros dados do arquivo de origem
  Register *registros = malloc(arguments->nRegisters * sizeof(Register));
  fread(registros, sizeof(Register), arguments->nRegisters, arq);

  // Gerando o nome do arquivo de destino
  char newArqBin[100];
  snprintf(newArqBin, sizeof(newArqBin), "./tmp_bins/quicksort-%d.bin",
           arguments->situation);

  strcpy(temp_bin, newArqBin);

  // Escrevendo os n primeiros dados no arquivo de destino
  FILE *novoArq = fopen(newArqBin, "wb+");
  fwrite(registros, sizeof(Register), arguments->nRegisters, novoArq);

  fclose(arq);
  fclose(novoArq);
  free(registros);
}

// Função para converter o arquivo binário para texto e imprimir os dados
void binaryToTxtAndPrintData(Arguments *arguments, char *tmp_bin) {
  FILE *arqOrigem = fopen(tmp_bin, "rb");

  // Criando e abrindo o arquivo de saída
  char nomeArqDestino[100];
  snprintf(nomeArqDestino, sizeof(nomeArqDestino),
           "./respostas_txt/quicksort-%d.txt", arguments->situation);

  FILE *arqDestino = fopen(nomeArqDestino, "w");

  // Lendo os dados do binário e escrevendo no texto
  Register buffer[20];
  size_t itensLidos;

  printf("\n");
  int index = 1;
  while ((itensLidos = fread(buffer, sizeof(Register), 20, arqOrigem)) > 0) {
    for (int i = 0; i < itensLidos; i++) {
      if (arguments->p) {
        // Imprimir os dados no console, se a opção '-p' estiver ativada
        printf("%d - %-8d %-5.2f %-2s %-50s %-30s\n", (index), buffer[i].key,
               buffer[i].grade, buffer[i].state, buffer[i].city,
               buffer[i].course);
        index++;
      }

      // Escrever os dados no arquivo de destino
      fprintf(arqDestino, "%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].key,
              buffer[i].grade, buffer[i].state, buffer[i].city,
              buffer[i].course);
    }
  }
  printf("\n");

  fclose(arqDestino);
  fclose(arqOrigem);
}
