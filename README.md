# Nuvem-de-Tags-ED
Implementação de uma núvem de Tags em linguagem C
Relatório Final de Estruturas de Dados LDE x AVL+ABP
O trabalho final da disciplina de Estrutura de Dados consiste em desenvolver um algoritmo
que recebe um texto, conta o total de palavras e as repetições de cada palavra. O mesmo
algoritmo deveria ser implementado utilizando uma lista e uma árvore. Para o primeiro
algoritmo implementado foi escolhida a lista duplamente encadeada (LDE). A lista era
percorrida inteiramente a cada nova inserção, então, no texto do Alienista, por exemplo,
tínhamos um somatório de aproximadamente 4000 palavras. Repetir o processo a cada
inserção gastaria muito tempo. Apesar disso, o algoritmo bem organizado nos permitiu
alcançar resultados bem satisfatórios. É importante destacar que a LDE foi escolhida, entre
outras listas, por sua facilidade de comparação entre os elos anteriores e posteriores de um
elemento, característica importantíssima no processo de organização da lista. Em
comparação, o algoritmo desenvolvido com a estrutura de dados do tipo árvore foi muito mais
rápido. Para desenvolver uma organização otimizada, e, ao mesmo tempo, de fácil
implementação foram utilizadas árvores do tipo AVL e ABP. No primeiro nível de organização
(a ordem alfabética) utilizamos uma AVL devido à grande quantidade de consultas realizadas
a cada palavra lida. Na lista, poderíamos chegar a 4000 (~212) consultas em uma inserção,
na AVL este número chega no máximo a 12, que significa uma melhora muito grande,
mesmo levando em conta todos os testes e rotações diferentes utilizados para a organização
de uma árvore balanceada. Após a finalização das inserções na AVL em ordem alfabética, foi
criada uma árvore binária de pesquisa através de um caminhamento central à esquerda na
AVL. Como cada verbete já continha seu número de frequência registrado na estrutura, este
número foi utilizado como fator para construir a ABP. Uma vez que os elementos eram
selecionados em ordem alfabética, a ABP era facilmente organizada. A organização
separada em dois nível concedeu ao trabalho a eficiência desejada.
Para melhor visualização, representamos os dados através de gráficos e tabelas, mas é
importante lembrar que o tempo de execução varia de máquina para máquina.
Tabela 1: Tempo em mili segundos por texto:
Tabela 2: eficiência (caracteres/mili segundos)
Gráfico 1: porcentagem do tempo total que cada árvore utilizou
Gráfico 2: comparação de tempo, texto por texto.
Gráfico 3: comparação de eficiência em caracteres por mili segundos
