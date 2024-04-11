#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include "structures.h"


void printa_Arquivo(tItem);

tItem leitor_de_registros(FILE *);

void gera_registros_ordenados();

void imprime_Registros_Txt(FILE *, tItem);

char *incrementa_Nome(char *);

void define_Nome_Fita_Saida(char[]);

void printa_Fita(int);

void printa_Todas_Fitas();

void printa_registros_ordenados();

void printa_registros_terminal(tItem,int);

#endif
