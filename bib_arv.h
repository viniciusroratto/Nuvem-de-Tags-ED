
#define TAM_PALAVRA 47 // Tamanho máximo para cada palavra.
#define TAM_LINHA 255 // Tamanho máximo para linha lida no arquivo de texto.
#define TAM_NOME_ARQUIVO 40 // Tamanho máximo para o nome do arquivo.

typedef struct PtPalavra palavra;

struct PtPalavra
{
	char verbete[TAM_PALAVRA+1]; // A palavra.
	int aparicoes; // Quantas vezes a palavra apareceu.
	int fator;
	palavra* esquerda; // Ponteiro para próximo nó.
	palavra* direita; // Ponteiro para nó anterior.
};

//Funções.

// Função que lê linhas do arquivo e armazena na LDE.
// Entrada: - Ponteiro pra arquivo (arquivotxt).
//          - Ponteiro pra árvore (PtArv).
// Saída: - Ponteiro pra árvore (PtArv).
palavra* cria_arvore (FILE* arquivotxt, palavra* PtArv);

// Função que imprime árvore com palavras que apareceram entre k1 e k2 vezes.
// Entrada: - Ponteiro pra árvore (PtArv).
//          - Limite inferior (K1).
//          - Limite superior (K2).
// Saída: não há retorno na função.
//        Um arquivo saída é criado, na pasta do executável, com tudo que foi impresso no prompt.
void imprime_arvore (palavra *PtArv, int K1, int K2, FILE* saida);

// Função que aloca um novo nó e insere no lugar correto da árvore.
// Entrada: - Ponteiro pra árvore (PtArv).
//          - String que é a palavra (info).
//          - Inteiro flag (ok)
// Saída: - Ponteiro para árvore (PtArv).
palavra* insere_palavra (palavra *PtArv, char *info, int *ok);

// Inicializa ponteiros para a struct PtPalavra.
// Entrada: não tem entrada na função.
// Saída: - NULL.
palavra* inicializa_ponteiro (void);

// Destrói árvore.
// Entrada: - Ponteiro para árvore (PtArv).
// Saída: não tem saída.
void destroi_arvore (palavra *PtArv);

// Verifica validade dos dados K1 e K2.
// Entrada: - Endereço do limite inferior (K1).
//          - Endereço do limite superior (K2).
// Saída: - 0, se pelo menos um dos valores de K1 ou K2 não forem válidos.
//        - 1, se os valores de K1 e K2 forem válidos.
int verifica_limites (int *K1, int *K2);

// Calcula a altura de um nó.
// Entrada: - Ponteiro para um nó.
// Saída: - Altura da árvore.
int Altura (palavra *PtArv);

// Calcula o fator de um nó da árvore.
// Entrada: - Ponteiro para um nó.
// Saída - Fator do nó.
int calcula_fator(palavra *PtArv);

// Faz a rotação simples à direita.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_direita(palavra *PtArv);

// Faz a rotação simples à esquerda.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_esquerda(palavra *PtArv);

// Faz rotação dupla à direita.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_dupla_direita (palavra *PtArv);

// Faz rotação dupla à esquerda.
// Entrada: - Ponteiro para nó
// Saída: - Ponteiro para nó rotacionado.
palavra* rotacao_dupla_esquerda (palavra *PtArv);

// Transfere nodos de uma AVL para uma ABP organizando em ordem de frequência.
// Entrada: - Ponteiro para AVL
//          - Ponteiro para ABP
// Saída: - Ponteiro para ABP
palavra* transfere_arvore (palavra *PtArv, palavra *PtArv2);

// Insere um nodo em uma ABP organizando por ordem de frequência.
// Entrada: - Ponteiro para ABP
//          - Frequencia de aparições da palavra.
//          - String com a palavra.
// Saída: - Ponteiro para ABP.
palavra* insere_ABP(palavra *PtArv2, int frequencia, char *info);

// Insere um nodo em uma AVL organizando por ordem alfabética.
// Entrada: - Ponteiro para AVL
//          - Frequencia de aparições da palavra.
//          - String com a palavra.
// Saída: - Ponteiro para AVL.
palavra* InsereAVL (palavra *PtArv, char *info, int *ok);

// Decide entre o uso da rotação simples à direita ou dupla à direita.
// Entrada: - Ponteiro para AVL
//          - Flag ok
// Saída: - Ponteiro para AVL.
palavra* Caso1 (palavra* PtArv , int *ok);

// Decide entre o uso da rotação simples à esquerda ou dupla à esquerda.
// Entrada: - Ponteiro para AVL
//          - Flag ok
// Saída: - Ponteiro para AVL.
palavra* Caso2 (palavra *PtArv , int *ok);
