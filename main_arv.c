/*****************************************************************
 * Trabalho final de Estrutura de Dados:                         *
 * Gabriel Simonetti Souza - 243661                              *
 * Vinícius Roratto Carvalho - 160094                            *
 * Este programa lê arquivos de texto e faz a contagem das       *
 * palavras que se repetem e mostra na tela todas que aparecerem *
 * entre K1 e K2 vezes.                                          *
 *****************************************************************/

//Bibliotecas usadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //Esta biblioteca é usada para calcular o tempo de execução dos programas.
#include "bib_arv.h" //Biblioteca criada para as funções implementadas no trabalho.

int main (int argc, char*argv[])
{

// Declaração das variáveis.
    int K1=0; // Limite inferior.
    int K2=0; // Limite superior.
    char nomedotxt[TAM_NOME_ARQUIVO+1]; // Nome do arquivo de texto.
    char nome_arquivo_saida[TAM_NOME_ARQUIVO+8+1] = "Saída - "; // Nome do arquivo de saída.
    long unsigned int tempo_zero; // Tempo inicial na execução do programa.
    palavra* PtArv; // Ponteiro para o início da árvore em ordem alfabética.
    palavra* PtArv2; // Ponteiro para o início da ABP para organizar em ordem numérica.
    FILE* arquivotxt; // Ponteiro para o arquivo de texto que será lido.
    FILE *saida; // Ponteiro para o arquivo de texto de saida.

// Transformação dos argumentos na main.
    K1 = atoi(argv[1]); // Converte primeiro argumento em K1.
    K2 = atoi(argv[2]); // Converte segundo argumento em K2.
    strcpy(nomedotxt, argv[3]); // Converte terceira substring em string que recebe nome de arquivo.
    strcat(nome_arquivo_saida, nomedotxt); // Concatena o nome do arquivo de entrada com o nome do arquivo de saída para identificá-lo.

// Inicialização do contador de tempo.
    tempo_zero = GetTickCount();

// Inicialização do ponteiro de árvore.
    PtArv = inicializa_ponteiro();
    PtArv2 = inicializa_ponteiro();

// Testes.
    if(!(verifica_limites (&K1, &K2))) // Chama função que verifica a validade de K1 e K2.
    {
        printf("\nPrograma encerrado.\n");
        return 0;
    }

//Abrir arquivo de leitura.
    if (!(arquivotxt = fopen(nomedotxt, "r")))
        {
            puts("\nErro na leitura do arquivo.\n");
            return 0;
        }
    else
        puts("\nArquivo aberto com sucesso.\n");

// Abrir arquivo de saída.
    if (!(saida = fopen(nome_arquivo_saida, "w+")))
        {
            puts("\nErro na abertura do arquivo de sa\241da.\n");
            return 0;
        }
    else
        puts("\nArquivo de sa\241da criado com sucesso.\nAguarde \n\n");

// Manipulaçao dos dados do arquivo. A função cria_arvore é chamada que é onde o arquivo é lido e a árvore de palavras criada e ordenada.
    PtArv = cria_arvore (arquivotxt, PtArv);

// Transfere uma AVL para uma ABP em ordem de frequência.
    PtArv2 = transfere_arvore (PtArv, PtArv2);

// Impressão da árvore de palavras na do primeiro para o último.
    fprintf(saida, "Saída:\n");
    imprime_arvore (PtArv2, K1, K2, saida);

// Desalocar árvore.
    destroi_arvore(PtArv);
    destroi_arvore(PtArv2);

// Fechar arquivo de texto.
    fclose(arquivotxt);

// Imprime tempo de execução na tela e no arquivo.
    fprintf(saida, "\nTempo de execução: %lu milissegundos.\n\n", GetTickCount() - tempo_zero); // Tempo atual - tempo inicial. NO ARQUIVO.
    fclose(saida);
    printf("\nTempo de execu\207\706o: %lu milissegundos.\n\n", GetTickCount() - tempo_zero); // Tempo atual - tempo inicial.

// Fim do programa.
    return 0;
}
