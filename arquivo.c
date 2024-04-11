#include "arquivo.h"
#include "intercalacao.h"

void printa_Arquivo(tItem reg)
{
    printf("\n");

    printf("Inscricao: %ld\t Nota:%lf", reg.inscricao, reg.nota);

    printf("\n");

    printf("%s - %s", reg.cidade, reg.estado);

    printf("\n");

    printf("Curso: %s", reg.curso);

    printf("\n");
}

tItem leitor_de_registros(FILE *arquivo)
{
    tItem registro;
    char backspace;

    // lê inscricao
    fscanf(arquivo, "%8ld", &registro.inscricao);

    // lê o espaco
    fscanf(arquivo, "%c", &backspace);

    // lê a nota
    fscanf(arquivo, "%5lf", &registro.nota);

    fscanf(arquivo, "%c", &backspace);

    fscanf(arquivo, "%2s", registro.estado);

    fscanf(arquivo, "%c", &backspace);

    // fscanf(arquivo,"%50s", &registro.cidade);
    fgets(registro.cidade, 50, arquivo);

    fscanf(arquivo, "%c", &backspace);

    // fscanf(arquivo, "%30s", &registro.curso);
    fgets(registro.curso, 30, arquivo);

    // printa_Arquivo(registro);

    return registro;
}

char *incrementa_Nome(char *nome)
{
    int i = 0;
    i = nome[9] - '0' + 1;
    nome[8] = nome[8] + i / 10;
    nome[9] = i % 10 + '0';
    return nome;
}

void printa_Fita(int i)
{

    char nomeArquivo[] = "bin/fita00.bin";
    for (int k = 0; k < i; i++)
    {
        incrementa_Nome(nomeArquivo);
    }
    printf("\nLendo: %s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("\n\n\nFalha em abrir o arquivo");
        return;
    }
    tItem reg;
    int quantidade;

    fseek(arquivo, 0, SEEK_SET);
    printf("\nFITA: %s", nomeArquivo);
    while (!feof(arquivo))
    {
        quantidade = 0;
        fread(&quantidade, sizeof(int), 1, arquivo);
        printf("\nTamanho do bloco:%d\n", quantidade);
        for (int k = 0; k < quantidade; k++)
        {
            reg.nota = 0;
            fread(&reg, sizeof(tItem), 1, arquivo);
            // printa_Arquivo(reg);
            printf("\nNOTA:%lf", reg.nota);
        }
    }

    fclose(arquivo);
}

void printa_Todas_Fitas()
{
    for (int i = 0; i < NUM_FITAS; i++)
    {
        printa_Fita(i);
    }
}

void define_Nome_Fita_Saida(char nome[])
{
    int numFitasSaida = (NUM_FITAS / 2);
    if (numFitasSaida > 9)
    {
        nome[8] = nome[8] + (numFitasSaida / 10);
        nome[9] = nome[9] + (numFitasSaida % 10);
    }
    else
    {
        nome[9] += numFitasSaida;
    }
}

void gera_registros_ordenados()
{
    FILE *arquivo = fopen("bin/fita00.bin", "rb");
    FILE *arquivoSaida = fopen("regOrdenado.txt", "w");
    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo...");
        return;
    }

    tItem aux;
    aux.inscricao = -2;

    do
    {
        if (fread(&aux, sizeof(tItem), 1, arquivo) != 1)
            break;
        if (aux.inscricao < 0)
        {
            break;
        }
        else
            imprime_Registros_Txt(arquivoSaida, aux);

    } while (1);
    fclose(arquivo);
    fclose(arquivoSaida);
}

void imprime_Registros_Txt(FILE *arquivo, tItem item)
{
    fprintf(arquivo, "%08ld", item.inscricao);
    fprintf(arquivo, " ");
    fprintf(arquivo, "%-5.1lf", item.nota);
    fprintf(arquivo, " ");
    fprintf(arquivo, "%-2s", item.estado);
    fprintf(arquivo, " ");
    fprintf(arquivo, "%-50s", item.cidade);
    fprintf(arquivo, " ");
    fprintf(arquivo, "%-30s", item.cidade);
    fprintf(arquivo, "\n");
}


void printa_registros_ordenados(){
    FILE *arquivo = fopen("bin/fita00.bin", "rb");
    int i=1;

    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo...");
        return;
    }

    tItem aux;
    aux.inscricao = -2;

    do
    {
        if (fread(&aux, sizeof(tItem), 1, arquivo) != 1)
            break;
        if (aux.inscricao < 0)
        {
            break;
        }
        else
        {
            printa_registros_terminal(aux,i);
            i++;
        }

    } while (1);
    fclose(arquivo);
}
void printa_registros_terminal(tItem item,int i){

    printf("\n");
    printf("%d)",i);
    printf( "%08ld", item.inscricao);
    printf(" ");
    printf("%-5.1lf", item.nota);
    printf(" ");
    printf("%-2s", item.estado);
    printf(" ");
    printf("%-50s", item.cidade);
    printf(" ");
    printf("%-30s", item.cidade);
}