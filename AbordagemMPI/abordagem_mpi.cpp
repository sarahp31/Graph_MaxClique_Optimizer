#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Função para verificar se um subconjunto de vértices forma um clique
bool is_clique(const vector<vector<int>>& graph, const vector<int>& vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = i + 1; j < vertices.size(); j++) {
            if (!graph[vertices[i]][vertices[j]]) {
                return false;
            }
        }
    }
    return true;
}

// Função para encontrar o clique máximo no grafo
vector<int> max_clique(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> max_clique_vertices;

    for(int mask = 1; mask < (1 << n); mask++) {
        vector<int> vertices;
        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                vertices.push_back(i);
            }
        }

        if(is_clique(graph, vertices) && vertices.size() > max_clique_vertices.size()) {
            max_clique_vertices = vertices;
        }
    }

    return max_clique_vertices;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    vector<vector<int>> graph;
    int n_vertices, n_edges;

    if (world_rank == 0) {
        ifstream file("grafo10.txt");
        if(!file.is_open()) {
            cerr << "Erro ao abrir o arquivo." << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }

        file >> n_vertices >> n_edges;
        graph.resize(n_vertices, vector<int>(n_vertices, 0));

        for(int i = 0; i < n_edges; i++) {
            int u, v;
            file >> u >> v;
            graph[u-1][v-1] = 1;
            graph[v-1][u-1] = 1;
        }
        file.close();
    }

    MPI_Bcast(&n_vertices, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0) {
        graph.resize(n_vertices, vector<int>(n_vertices, 0));
    }

    for (int i = 0; i < n_vertices; ++i) {
        MPI_Bcast(graph[i].data(), n_vertices, MPI_INT, 0, MPI_COMM_WORLD);
    }

    int subset_size = 1 << n_vertices;
    int subset_per_process = subset_size / world_size;
    int start = world_rank * subset_per_process;
    int end = (world_rank + 1) * subset_per_process;

    vector<int> local_max_clique;

    for (int mask = start; mask < end; mask++) {
        vector<int> vertices;
        for (int i = 0; i < n_vertices; i++) {
            if (mask & (1 << i)) {
                vertices.push_back(i);
            }
        }
        if (is_clique(graph, vertices) && vertices.size() > local_max_clique.size()) {
            local_max_clique = vertices;
        }
    }

    vector<int> global_max_clique;
    int local_size = local_max_clique.size();
    int global_size;

    MPI_Reduce(&local_size, &global_size, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (local_size == global_size) {
        if (world_rank != 0) {
            MPI_Send(local_max_clique.data(), local_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else {
            global_max_clique = local_max_clique;
            for (int i = 1; i < world_size; i++) {
                vector<int> temp_clique(global_size);
                MPI_Recv(temp_clique.data(), global_size, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // Aqui você pode querer combinar os cliques locais, se necessário
            }
        }
    }

    if (world_rank == 0) {
        cout << "Vértices do clique máximo: ";
        for (int v : global_max_clique) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}
