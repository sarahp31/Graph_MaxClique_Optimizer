# Graph_MaxClique_Optimizer


## Descrição do Projeto

Este projeto aborda o desafio computacional de encontrar a clique máxima em um grafo no contexto da Análise de Redes Sociais (ARS). A ARS foca nas ligações relacionais entre atores sociais, sejam eles indivíduos ou entidades coletivas, e a clique máxima representa um subconjunto de uma rede onde todos os membros estão interligados, evidenciando grupos coesos dentro da rede.

## Objetivo

O principal objetivo é desenvolver e comparar diferentes abordagens computacionais para identificar a clique máxima em um grafo, uma tarefa desafiadora devido à complexidade combinatória do problema.

## Abordagens Implementadas

### 1. Abordagem Exaustiva
Esta abordagem envolve a análise iterativa de combinações de vértices para formar cliques. Um pseudo-código é fornecido para orientar a implementação em C++, mas a solução completa e otimizações são deixadas como um desafio.

### 2. Implementação com Threads OpenMP
Utiliza a API OpenMP para paralelizar o processo de busca de cliques, visando reduzir o tempo de execução. O código-fonte modificado e as métricas de desempenho devem ser apresentados.

### 3. Paralelização e Distribuição do Processamento com MPI
Emprega MPI para distribuir o problema em várias unidades de processamento, com cada uma encontrando cliques em uma parte do grafo. O foco é na escalabilidade e eficiência em sistemas distribuídos.


## Códigos-Fonte de Apoio

- **Geração do Grafo**: Um script Python é fornecido para gerar um grafo aleatório.
- **Leitura do Grafo**: Código-fonte em C++ para ler o grafo e armazená-lo como uma matriz de adjacência.
- **Verificação da Clique Máxima**: Script Python para verificar a correção da clique máxima encontrada.
