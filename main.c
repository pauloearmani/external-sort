#include <stdio.h>
#include <stdlib.h>
#include "./mainQS.h"
#include "./main2f.h"
#include "./fm1.h"


int main(int argc, char *argv[]) {

    if(argc < 4 || argc > 5){
        printf("Quantidade de argumentos invalida\n");
        exit(1);
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int opcional = 0;

    if(metodo < 1 || metodo > 3){
        printf("Metodo deve ser 1, 2 ou 3\n");
        exit(1);
    }

    if(quantidade <= 0){
        printf("Quantidade deve ser maior que 0\n");
        exit(1);
    }

    if(situacao < 1 || situacao > 3){
        printf("Situacao deve ser 1, 2 ou 3\n");
        exit(1);
    }

    if (argc == 5) {
        if (argv[4][0] == '-' && argv[4][1] == 'P' && argv[4][2] == '\0') {
            opcional = 1;
        } else {
            printf("Opção inválida\n");
            exit(1);
        }
    }

    switch (metodo) {
    case 1:
        main2f(quantidade, situacao, opcional);
        break;
    case 2:
        mainf1(quantidade, situacao, opcional);
        break;
    case 3:
        mainQS(quantidade, situacao, opcional);
        break;
    default:
        break;
    }

    return 0;

}