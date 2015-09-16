// Bibliotecas usadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Esta biblioteca é usada para calcular o tempo de execução dos programas.
#include "bib_arv.h" // Biblioteca criada para as funções implementadas no trabalho.

// Função que lê linhas do arquivo e armazena na LDE.
// Entrada: - Ponteiro pra arquivo (arquivotxt).
//          - Ponteiro pra árvore (PtArv).
// Saída: - Ponteiro pra árvore (PtArv).
palavra* cria_arvore (FILE* arquivotxt, palavra* PtArv)
{
    char buffer_linha[TAM_LINHA+1]; // Variável para pegar a linha inteira do arquivo de texto.
    char *verbeteaux; // String que recebe as palavras e manda pra função.
    int ok;

    while (fgets(buffer_linha, TAM_LINHA+1, arquivotxt)) // Enquanto houverem linhas sendo lidas.
    {
        if((verbeteaux = strtok(buffer_linha, " ,.\n:\"?!;0123456789()[]/-"))) // Se a função strtok retornar algo diferente de 0.
        {
            strlwr(verbeteaux); // Todas as letras da string recebidas se tornam minúsculas.
            PtArv = InsereAVL(PtArv, verbeteaux, &ok); // Insere novo nó na lista.
        }
        while ((verbeteaux = strtok(NULL, " ,.\n:\"?!;0123456789()[]/-"))) // Enquanto a função strtok retornar algo diferente de 0.
        {
            strlwr(verbeteaux); // Todas as letras da string recebidas se tornam minúsculas.
            PtArv = InsereAVL(PtArv, verbeteaux, &ok); // Insere novo nó na lista.
        }
    }
    return PtArv; // Retorna ponteiro para a lista.
}

// Função que imprime árvore com palavras que apareceram entre k1 e k2 vezes.
// Entrada: - Ponteiro pra árvore (PtArv).
//          - Limite inferior (K1).
//          - Limite superior (K2).
// Saída: não há retorno na função.
//        Um arquivo saída é criado, na pasta do executável, com tudo que foi impresso no prompt.
void imprime_arvore (palavra *PtArv, int K1, int K2, FILE* saida)
{
    if (PtArv != NULL)
    {
        imprime_arvore (PtArv->esquerda, K1, K2, saida);
        if(PtArv->aparicoes >= K1 && PtArv->aparicoes <= K2) // Se a palavra tiver aparecido entre K1 e K2 vezes.
        {
            //printf("%4d - %s\n", PtArv->aparicoes, PtArv->verbete); // Imprime na tela.
            fprintf(saida, "    %4d - %s\n", PtArv->aparicoes, PtArv->verbete); // Imprime no arquivo de saída.
        }
        imprime_arvore (PtArv->direita, K1, K2, saida);
    }
}

// Inicializa ponteiros para a struct PtPalavra.
// Entrada: não tem entrada na função.
// Saída: - NULL.
palavra* inicializa_ponteiro(void)
{
    return NULL;
}

// Destrói árvore.
// Entrada: - Ponteiro para árvore (PtArv).
// Saída: não tem saída.
void destroi_arvore (palavra *PtArv)
{
    if (PtArv!= NULL)
    {
        destroi_arvore(PtArv->esquerda);
        destroi_arvore(PtArv->direita);
        free(PtArv);
    }
}

// Verifica validade dos dados K1 e K2.
// Entrada: - Endereço do limite inferior (K1).
//          - Endereço do limite superior (K2).
// Saída: - 0, se pelo menos um dos valores de K1 ou K2 não forem válidos.
//        - 1, se os valores de K1 e K2 forem válidos.
int verifica_limites (int *K1, int *K2)
{
    int aux;
    if (*K1 < 0 || *K2 < 0) // O programa não pode continuar se os valores de K1 ou K2 forem negativos.
    {
        printf("\nOs valores de K1 e K2 n\706o podem ser negativos.\n"); // Aviso ao usuário.
        return 0;
    }
    if (*K1 > *K2) // No caso do limite superior ser menor que o limite inferior, programa avisa o erro, mas faz um swap.
    {
        printf("\nK1 precisa ser limite inferior e K2 limite superior.\nInvertemos os valores para voc\210.\n"); // Aviso ao usuário.
        aux = *K1; // SWAP
        *K1 = *K2;
        *K2 = aux;
    }
    return 1;
}

// Calcula a altura de um nó.
// Entrada: - Ponteiro para um nó.
// Saída: - Altura da árvore.
int Altura (palavra *PtArv)
{
    int Alt_Esq, Alt_Dir;
    if (PtArv == NULL)
      return 0;
    else
    {
       Alt_Esq = Altura (PtArv->esquerda);
       Alt_Dir = Altura (PtArv->direita);
       if (Alt_Esq > Alt_Dir)
         return (1 + Alt_Esq);
       else
         return (1 + Alt_Dir);
     }
}

// Calcula o fator de um nó da árvore.
// Entrada: - Ponteiro para um nó.
// Saída - Fator do nó.
int calcula_fator(palavra *PtArv)
{
    return (Altura(PtArv->esquerda) - Altura(PtArv->direita));
}

// Faz a rotação simples à direita.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_direita(palavra *PtArv)
{
    palavra* ptu;

    ptu = PtArv->esquerda;
    PtArv->esquerda = ptu->direita;
    ptu->direita = PtArv;
    PtArv->fator = 0;
    PtArv = ptu;
    return PtArv;
}

// Faz a rotação simples à esquerda.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_esquerda(palavra *PtArv)
{
    palavra* ptu;

    ptu = PtArv->direita;
    PtArv->direita = ptu->esquerda;
    ptu->esquerda = PtArv;
    PtArv->fator = 0;
    PtArv = ptu;
    return PtArv;
}

// Faz rotação dupla à direita.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_dupla_direita (palavra *PtArv)
{
    palavra* ptu, *ptv;

    ptu = PtArv->esquerda;
    ptv = ptu->direita;
    ptu->direita = ptv->esquerda;
    ptv->esquerda = ptu;
    PtArv->esquerda = ptv->direita;
    ptv->direita = PtArv;
    if (ptv->fator == 1)
        PtArv->fator = -1;
    else
        PtArv->fator = 0;
    if (ptv->fator == -1)
        ptu->fator = 1;
    else
        ptu->fator = 0;
    PtArv = ptv;
    return PtArv;
}

// Faz rotação dupla à esquerda.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_dupla_esquerda (palavra *PtArv)
{
    palavra *ptu, *ptv;

    ptu = PtArv->direita;
    ptv = ptu->esquerda;
    ptu->esquerda = ptv->direita;
    ptv->direita = ptu;
    PtArv->direita = ptv->esquerda;
    ptv->esquerda = PtArv;
    if (ptv->fator == -1)
        PtArv->fator = 1;
    else
        PtArv->fator = 0;
    if (ptv->fator == 1)
        ptu->fator = -1;
    else
        ptu->fator = 0;
    PtArv = ptv;
    return PtArv;
}

// Transfere nodos de uma AVL para uma ABP organizando em ordem de frequência.
// Entrada: - Ponteiro para AVL
//          - Ponteiro para ABP
// Saída: - Ponteiro para ABP
palavra* transfere_arvore (palavra *PtArv, palavra *PtArv2)
{
    if (PtArv != NULL)
    {
        PtArv2 = transfere_arvore(PtArv->esquerda, PtArv2);
        PtArv2 = insere_ABP(PtArv2, PtArv->aparicoes, PtArv->verbete);
        PtArv2 = transfere_arvore(PtArv->direita, PtArv2);
    }
    return PtArv2;
}

// Insere um nodo em uma ABP organizando por ordem de frequência.
// Entrada: - Ponteiro para ABP
//          - Frequencia de aparições da palavra.
//          - String com a palavra.
// Saída: - Ponteiro para ABP.
palavra* insere_ABP(palavra *PtArv2, int frequencia, char *info)
{
    if (PtArv2 == NULL)  // Para inserção do primeiro nó.
    {
        PtArv2 = (palavra*)malloc(sizeof(struct PtPalavra));
        strcpy(PtArv2->verbete, info);
        PtArv2->esquerda = NULL;
        PtArv2->direita = NULL;
        PtArv2->aparicoes = frequencia;
        return PtArv2;
    }
    else if (frequencia > PtArv2->aparicoes)
    {
        PtArv2->esquerda = insere_ABP(PtArv2->esquerda, frequencia, info);
    }
    else if (frequencia <= PtArv2->aparicoes)
    {
        PtArv2->direita = insere_ABP(PtArv2->direita, frequencia, info);
    }

    return PtArv2;
}

// Decide entre o uso da rotação simples à direita ou dupla à direita.
// Entrada: - Ponteiro para AVL
//          - Flag ok
// Saída: - Ponteiro para AVL.
palavra* Caso1 (palavra* PtArv , int *ok)
{
    palavra *ptu;

    ptu = PtArv->esquerda;
    if (ptu->fator == 1)
    {
        PtArv = rotacao_direita(PtArv);
    }
    else
    {
        PtArv = rotacao_dupla_direita(PtArv);
    }

    PtArv->fator = 0;
    *ok = 0;
    return PtArv;
}

// Decide entre o uso da rotação simples à esquerda ou dupla à esquerda.
// Entrada: - Ponteiro para AVL
//          - Flag ok
// Saída: - Ponteiro para AVL.
palavra* Caso2 (palavra *PtArv , int *ok)
{
    palavra *ptu;

    ptu = PtArv->direita;
    if (ptu->fator == -1)
    {
        PtArv=rotacao_esquerda(PtArv);
    }
    else
    {
        PtArv=rotacao_dupla_esquerda(PtArv);
    }
    PtArv->fator = 0;
    *ok = 0;
    return PtArv;
}

// Insere um nodo em uma AVL organizando por ordem alfabética.
// Entrada: - Ponteiro para AVL
//          - Frequencia de aparições da palavra.
//          - String com a palavra.
// Saída: - Ponteiro para AVL.
palavra* InsereAVL (palavra *PtArv, char *info, int *ok)
{
/* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
  x, a chave a ser inserida e h a altura da árvore */

     if (PtArv == NULL)
     {
     	PtArv = (palavra*)malloc(sizeof(struct PtPalavra));
        strcpy(PtArv->verbete, info);
        PtArv->esquerda = NULL;
        PtArv->direita = NULL;
        PtArv->aparicoes = 1;
        PtArv->fator = 0;
     }
     else if (strcmp(PtArv->verbete, info) == 1)
     {
		PtArv->esquerda = InsereAVL(PtArv->esquerda, info, ok);
        if (*ok)
        {
   		    switch (PtArv->fator)
   		    {
        	  case -1:
                PtArv->fator = 0;
                *ok = 0;
                break;
			  case  0:
			      PtArv->fator = 1;
			      break;
			  case  1:
			      PtArv=Caso1(PtArv,ok);
			      break;
            }
         }
     }
	 else if (strcmp(PtArv->verbete, info) == -1)
     {
  		    PtArv->direita = InsereAVL(PtArv->direita, info, ok);
            if (*ok)
            {
              switch (PtArv->fator)
              {
                case  1:  PtArv->fator = 0; *ok = 0; break;
                case  0:  PtArv->fator = -1; break;
			    case -1:  PtArv = Caso2(PtArv,ok); break;
             }
            }
     }
     else
    {
        PtArv->aparicoes += 1;
    }
     return PtArv;
}

