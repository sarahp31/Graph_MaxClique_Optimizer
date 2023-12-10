from igraph import *
import matplotlib.pyplot as plt

# Nome do arquivo .txt
nome_do_arquivo = 'grafo30.txt'

# Inicializa a lista de tuplas
lista_de_tuplas = []

# Lê o arquivo
with open(nome_do_arquivo, 'r') as arquivo:
    # Lê a primeira linha para obter o número de vértices e arestas
    n_vertices, n_arestas = map(int, arquivo.readline().split())

    # Processa o restante das linhas para criar a lista de tuplas
    for linha in arquivo:
        tupla = tuple(map(lambda x: int(x) - 1, linha.split()))
        lista_de_tuplas.append(tupla)

# Agora você tem o número de vértices e arestas e a lista de tuplas
print("Número de vértices:", n_vertices)
print("Número de arestas:", n_arestas)
print("Lista de tuplas:", lista_de_tuplas)

g = Graph()
g.add_vertices(n_vertices)
g.add_edges(lista_de_tuplas)
plot(g)
