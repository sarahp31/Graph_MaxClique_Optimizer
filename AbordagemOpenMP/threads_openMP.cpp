#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>  // OpenMP

using namespace std;

/// Função para verificar se um subconjunto de vértices forma um clique
bool is_clique(const vector<vector<bool>>& graph, const vector<int>& vertices) {
    // Iterar sobre todos os pares de vértices do subconjunto
    for(int i = 0; i < vertices.size(); i++) {
        for(int j = i+1; j < vertices.size(); j++) {
            // Se algum par de vértices não está conectado, o subconjunto não é um clique.
            if(!graph[vertices[i]][vertices[j]]) {
                return false;
            }
        }
    }
    return true;
}

// Função para encontrar o clique máximo no grafo
vector<int> max_clique(const std::vector<std::vector<bool>>& graph) {
    // Número de vértices no grafo
    int n = graph.size();
    // Vetor para armazenar os vértices do clique máximo
    vector<int> max_clique_vertices;

    // Iterar sobre todos os possíveis subconjuntos de vértices
    for(int mask = 1; mask < (1 << n); mask++) {
        vector<int> vertices;
        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                vertices.push_back(i);
            }
        }

        // Se o subconjunto atual é um clique e é maior que o maior clique encontrado,
        // atualizar max_clique_vertices
        if(is_clique(graph, vertices) && vertices.size() > max_clique_vertices.size()) {
            max_clique_vertices = vertices;
        }
    }
    // Retornar os vértices do clique máximo encontrado
    return max_clique_vertices;
}

int main() {
    // Abrir o arquivo para leitura
    ifstream file("grafo.txt");

    if(!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }
    // Número de vértices e arestas
    int n_vertices, n_edges;
    file >> n_vertices >> n_edges;

    // Criar matriz de adjacência para armazenar o grafo
    vector<vector<bool>> graph(n_vertices, vector<bool>(n_vertices, false));

    // Ler as arestas do arquivo e preencher a matriz de adjacência.
    for(int i = 0; i < n_edges; i++) {
        int u, v;
        file >> u >> v;
        // Ajustar os índices para começar de 0 e marcar u e v como conectados
        graph[u-1][v-1] = true;
        // Como o grafo é não direcionado, marcar v e u como conectados também
        graph[v-1][u-1] = true;
    }

    file.close();

    vector<int> max_clique_vertices;

    // Medir o tempo de execução em paralelo
    double start_time = omp_get_wtime();

    // Diretiva OpenMP para paralelizar o bloco de código a seguir
    #pragma omp parallel
    {
        vector<int> local_max_clique;

        // Diretiva OpenMP para dividir iterações do loop entre as threads
        #pragma omp for nowait
        for(int mask = 1; mask < (1 << n_vertices); mask++) {
            vector<int> vertices;
            for(int i = 0; i < n_vertices; i++) {
                if(mask & (1 << i)) {
                    vertices.push_back(i);
                }
            }
            if(is_clique(graph, vertices) && vertices.size() > local_max_clique.size()) {
                local_max_clique = vertices;
            }
        }

        // Diretiva OpenMP para seção crítica: apenas uma thread por vez pode executar
        #pragma omp critical
        {
            if(local_max_clique.size() > max_clique_vertices.size()) {
                max_clique_vertices = local_max_clique;
            }
        }
    }

    double end_time = omp_get_wtime();

    cout << "Vértices do clique máximo: ";
    for(int vertex : max_clique_vertices) {
        cout << vertex + 1 << " ";
    }
    cout << endl;

    cout << "Tempo de execução paralelizado: " << end_time - start_time << " segundos" << std::endl;

    return 0;
}