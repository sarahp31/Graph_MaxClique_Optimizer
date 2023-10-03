#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool is_clique(const vector<vector<bool>>& graph, const vector<int>& vertices) {
    for(int i = 0; i < vertices.size(); i++) {
        for(int j = i+1; j < vertices.size(); j++) {
            if(!graph[vertices[i]][vertices[j]]) {
                return false;
            }
        }
    }
    return true;
}

vector<int> max_clique(const std::vector<std::vector<bool>>& graph) {
    int n = graph.size();
    vector<int> max_clique_vertices;  // Vetor para armazenar os vértices do clique máximo.

    // Iterar sobre todos os possíveis subconjuntos de vértices.
    for(int mask = 1; mask < (1 << n); mask++) {
        vector<int> vertices;
        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                vertices.push_back(i);
            }
        }

        // Se o subconjunto atual é um clique e é maior que o maior clique encontrado,
        // atualizar max_clique_vertices.
        if(is_clique(graph, vertices) && vertices.size() > max_clique_vertices.size()) {
            max_clique_vertices = vertices;
        }
    }
    return max_clique_vertices;  // Retornar os vértices do clique máximo encontrado.
}

int main() {
    ifstream file("grafo.txt");

    if(!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    int n_vertices, n_edges;
    file >> n_vertices >> n_edges;

    vector<vector<bool>> graph(n_vertices, vector<bool>(n_vertices, false));

    for(int i = 0; i < n_edges; i++) {
        int u, v;
        file >> u >> v;
        graph[u-1][v-1] = true;
        graph[v-1][u-1] = true;
    }

    file.close();

    // Encontrar e imprimir os vértices do maior clique.
    vector<int> max_clique_vertices = max_clique(graph);
    cout << "Vértices do clique máximo: ";
    for(int vertex : max_clique_vertices) {
        cout << vertex + 1 << " ";  // Ajustando índices para imprimir começando de 1.
    }
    cout << endl;

    return 0;
}