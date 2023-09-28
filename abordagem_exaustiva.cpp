#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


// Função para ler o grafo a partir do arquivo de entrada
vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

vector<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    vector<int> cliqueMaxima;
    vector<int> candidatos;

    // Inicialmente, todos os nós são candidatos
    for (int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {
        // ultimo elemento de candidatos
        int v = candidatos.back();
        // remove ultimo elemento de canditados
        candidatos.pop_back();
        bool podeAdicionar = true;

        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);
            vector<int> novosCandidatos;

            for (int u : candidatos) {
                bool adjacenteATodos = true;

                for (int c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }

            candidatos = novosCandidatos;
        }
    }

    return cliqueMaxima;
}

int main() {
    int numVertices;
    vector<vector<int>> grafo = LerGrafo("grafo.txt", numVertices); // Substitua "grafo.txt" pelo nome do seu arquivo de entrada

    vector<int> cliqueMaxima = EncontrarCliqueMaxima(grafo, numVertices);

    cout << "Clique Máxima: ";
    for (int node : cliqueMaxima) {
        cout << node + 1 << " "; // Adicione 1 para exibir os nós a partir de 1, não de 0
    }
    cout << endl;

    return 0;
}