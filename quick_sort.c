#include "quick_sort.h"
#include "area.h"
#include "estruturas.h"
#include <stdio.h>
#include <time.h>



// Le o dado do arquivo superior
void readSup(FILE **ArqLEs, Register *UltLido, int *Ls, short *OndeLer,
             Runtime *__run) {
  fseek(*ArqLEs, (*Ls - 1) * sizeof(Register), SEEK_SET);
  fread(UltLido, sizeof(Register), 1, *ArqLEs);
  (*Ls)--;
  __run->transfersReadCount += 1;
  *OndeLer = false;
}

// Le o dado do arquivo inferior
void readInf(FILE **ArqLi, Register *UltLido, int *Li, short *OndeLer,
             Runtime *__run) {
  fread(UltLido, sizeof(Register), 1, *ArqLi);
  (*Li)++;
  __run->transfersReadCount += 1;
  *OndeLer = true;
}

void insertArea(Area *area, Register *UltLido, int *NRArea, Runtime *__run) {
  // Insere UltLido de forma ordenada na Area
  insertItem(*UltLido, area, __run);

  *NRArea = area->n;
}

// Escreve o item no arquivo superior
void writeMax(FILE **ArqLEs, Register R, int *Es, Runtime *__run) {
  fseek(*ArqLEs, (*Es - 1) * sizeof(Register), SEEK_SET);
  fwrite(&R, sizeof(Register), 1, *ArqLEs);
  __run->transfersWriteCount += 1;

  (*Es)--;
}

// Escreve o item no arquivo inferior
void writeMin(FILE **ArqEi, Register R, int *Ei, Runtime *__run) {
  fwrite(&R, sizeof(Register), 1, *ArqEi);
  __run->transfersWriteCount += 1;

  (*Ei)++;
}

// Remove o maior valor do pivo

void removeMax(Area *area, Register *R, int *NRArea) {
  removeLast(area, R);
  *NRArea = area->n;
}

// Remove o menor valor do pivo
void removeMin(Area *area, Register *R, int *NRArea) {
  removeFirst(area, R);
  *NRArea = area->n;
}

// Função de particionamento para o algoritmo de ordenação externa

void partition(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Area area, int Esq,
               int Dir, int *i, int *j, Runtime *__run) {
  int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
  double Linf = INT_MIN, Lsup = INT_MAX;
  short OndeLer = true;
  Register UltLido, R;

  fseek(*ArqLi, (Li - 1) * sizeof(Register), SEEK_SET);
  fseek(*ArqEi, (Ei - 1) * sizeof(Register), SEEK_SET);

  *i = Esq - 1;
  *j = Dir + 1;

  // Lendo ate que os ponteiros de leitura se cruzem
  while (Ls >= Li) {
    if (NRArea < AREA_SIZE - 1) {
      if (OndeLer)
        readSup(ArqLEs, &UltLido, &Ls, &OndeLer, __run);
      else
        readInf(ArqLi, &UltLido, &Li, &OndeLer, __run);

      insertArea(&area, &UltLido, &NRArea, __run);
      continue;
    }

    // Lendo na alternancia correta
    // Verifica se os ponteiros de leitura e escrita estao juntos para mudar a
    // alternancia da leitura
    if (Ls == Es)
      readSup(ArqLEs, &UltLido, &Ls, &OndeLer, __run);
    else if (Li == Ei)
      readInf(ArqLi, &UltLido, &Li, &OndeLer, __run);
    else if (OndeLer)
      readSup(ArqLEs, &UltLido, &Ls, &OndeLer, __run);
    else
      readInf(ArqLi, &UltLido, &Li, &OndeLer, __run);

    // Tratativa do ultimo item lido
    // Caso em que o ultimo elemento vai para o subarquivo A2 (itens superiores
    // ao pivo)

    __run->comparisonCount += 1;

    if (UltLido.grade > Lsup) {
      *j = Es;
      writeMax(ArqLEs, UltLido, &Es, __run);
      continue;
    }
    __run->comparisonCount += 1;

    // Caso em que o ultimo elemento vai para o subarquivo A1 (itens inferiores
    // ao pivo)
    if (UltLido.grade < Linf) {
      *i = Ei;
      writeMin(ArqEi, UltLido, &Ei, __run);
      continue;
    }

    // Caso em que o ultimo elemento vai para o pivo
    insertArea(&area, &UltLido, &NRArea, __run);

    // Verificando qual o menor sub arquivo e escrevendo nele
    if (Ei - Esq < Dir - Es) {
      removeMin(&area, &R, &NRArea);
      writeMin(ArqEi, R, &Ei, __run);
      Linf = R.grade;
    } else {
      removeMax(&area, &R, &NRArea);
      writeMax(ArqLEs, R, &Es, __run);
      Lsup = R.grade;
    }
  }

  while (Ei <= Es) {
    removeMin(&area, &R, &NRArea);
    writeMin(ArqEi, R, &Ei, __run);
  }
}

void externalQuickSort(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq,
                       int Dir, Runtime *__run) {
  int i, j;

  if (Dir - Esq < 1)
    return;

  Area area;
  initializeArea(&area);

  partition(ArqLi, ArqEi, ArqLEs, area, Esq, Dir, &i, &j, __run);

  fflush(*ArqLi);
  fflush(*ArqEi);
  fflush(*ArqLEs);

  if (i - Esq < Dir - j) {
    externalQuickSort(ArqLi, ArqEi, ArqLEs, Esq, i, __run);
    externalQuickSort(ArqLi, ArqEi, ArqLEs, j, Dir, __run);
  } else {
    externalQuickSort(ArqLi, ArqEi, ArqLEs, j, Dir, __run);
    externalQuickSort(ArqLi, ArqEi, ArqLEs, Esq, i, __run);
  }
}

void quickSort(Arguments *arguments, char *temp_bin, Runtime *__run) {

  FILE *ArqLi = fopen(temp_bin, "rb+");
  FILE *ArqEi = fopen(temp_bin, "rb+");
  FILE *ArqLEs = fopen(temp_bin, "rb+");

  __run->startToCreateTre = clock();
  externalQuickSort(&ArqLi, &ArqEi, &ArqLEs, 1, arguments->nRegisters, __run);
  __run->endToCreateTre = clock();

  __run->totalTime = (double)(__run->endToCreateTre - __run->startToCreateTre) /
                     CLOCKS_PER_SEC;
  fclose(ArqLi);
  fclose(ArqEi);
  fclose(ArqLEs);
}


