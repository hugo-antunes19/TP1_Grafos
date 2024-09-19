#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> // Para BFS
using namespace std;

class Grafo {
private:
    vector<vector<long long>> matrizAdj;
    vector<vector<long long>> listAdj;
    long long vertices;
    bool usaMatriz;

public:
    Grafo(long long v, bool isMatriz) : vertices(v), usaMatriz(isMatriz) {
        if (usaMatriz) {
            matrizAdj.resize(vertices + 1, vector<long long>(vertices + 1, 0));
        } else {
            listAdj.resize(vertices + 1);
        }
    }

    // Adiciona uma aresta ao grafo
    void adicionarAresta(long long x, long long y) {
        if (usaMatriz) {
            matrizAdj[x][y] = 1;
            matrizAdj[y][x] = 1;
        } else {
            listAdj[x].push_back(y);
            listAdj[y].push_back(x);
        }
    }

    // Imprime a Matriz de Adjacência
    void printMatrizAdj() const {
        for (size_t i = 1; i < matrizAdj.size(); ++i) {
            for (size_t j = 1; j < matrizAdj[i].size(); ++j) {
                cout << matrizAdj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Imprime a Lista de Adjacência
    void printListAdj() const {
        for (size_t i = 1; i < listAdj.size(); ++i) {
            cout << i << ": ";
            for (size_t j = 0; j < listAdj[i].size(); ++j) {
                cout << listAdj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Algoritmo BFS
    void BFS(long long s, const string& outputFile) {
        vector<bool> visitado(vertices + 1, false);
        vector<long long> pai(vertices + 1, -1);
        vector<long long> nivel(vertices + 1, -1);
        queue<long long> Q;

        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "Erro ao abrir arquivo de saída." << endl;
            return;
        }
        outFile << "Busca em Profundidade (DFS)\n";
        
        visitado[s] = true;
        nivel[s] = 0;
        Q.push(s);

        while (!Q.empty()) {
            long long v = Q.front();
            Q.pop();
            
            // Escreve no arquivo imediatamente ao visitar o vértice
            if (pai[v] != -1 || v == s) {
                outFile << "Vértice: " << v << ", Pai: " << pai[v] << ", Nível: " << nivel[v] << endl;
            }

            const vector<long long>& vizinhos = usaMatriz ? getVizinhosMatriz(v) : listAdj[v];
            for (long long w : vizinhos) {
                if (!visitado[w]) {
                    visitado[w] = true;
                    pai[w] = v;      // Armazena o pai de w
                    nivel[w] = nivel[v] + 1; // Define o nível de w
                    Q.push(w);
                }
            }
        }

        outFile.close();
    }

    void DFS(long long s, const string& outputFile) {
        vector<bool> visitado(vertices + 1, false);
        vector<long long> pai(vertices + 1, -1);
        vector<long long> nivel(vertices + 1, -1);
        stack<long long> pilha;

        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "Erro ao abrir arquivo de saída." << endl;
            return;
        }
        outFile << "Busca em Profundidade (DFS)\n";

        // Inicialmente, marca o vértice de origem
        pilha.push(s);
        nivel[s] = 0;

        while (!pilha.empty()) {
            long long v = pilha.top();
            pilha.pop();

            if (!visitado[v]) {
                visitado[v] = true;

                // Escreve no arquivo imediatamente ao visitar o vértice
                if (pai[v] != -1 || v == s) {
                    outFile << "Vértice: " << v << ", Pai: " << pai[v] << ", Nível: " << nivel[v] << endl;
                }

                // Para cada vizinho do vértice v
                const vector<long long>& vizinhos = usaMatriz ? getVizinhosMatriz(v) : listAdj[v];
                for (long long w : vizinhos) {
                    if (!visitado[w]) {
                        pilha.push(w);
                        pai[w] = v;           // Define o pai de w
                        nivel[w] = nivel[v] + 1; // Define o nível de w
                    }
                }
            }
        }

        outFile.close();
    }

    // Obtém os vizinhos de um vértice na matriz de adjacência
    vector<long long> getVizinhosMatriz(long long v) const {
        vector<long long> vizinhos;
        for (long long i = 1; i <= vertices; ++i) {
            if (matrizAdj[v][i] == 1) {
                vizinhos.push_back(i);
            }
        }
        return vizinhos;
    }
};

int main(int argc, char *argv[]) {
    // Variáveis para capturar as opções
    int opt;
    string inputFile, outputFile, option; // Matriz ou Lista
    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"output", required_argument, 0, 'u'},
        {"option", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "f:u:o:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                inputFile = optarg;
                break;
            case 'u':
                outputFile = optarg;
                break;
            case 'o':
                option = optarg;
                break;
        }
    }

    if (inputFile.empty() || option.empty() || outputFile.empty()) {
        cerr << "Uso: " << argv[0] << " --file <inputfile> --output <outputfile> --option <option>" << endl;
        return 1;
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }

    long long vertices;
    file >> vertices;

    bool usaMatriz = (option == "matriz");
    Grafo grafo(vertices, usaMatriz);

    long long x, y;
    while (file >> x >> y) {
        if (x <= vertices && y <= vertices) {
            grafo.adicionarAresta(x, y);
        }
    }

    // Executa BFS ou DFS a partir do vértice 1 (pode ser alterado conforme necessidade)
    if (option == "bfs") {
        grafo.BFS(1, outputFile);
    } else if (option == "dfs") {
        grafo.DFS(1, outputFile);
    } else {
        cerr << "Opção inválida. Use 'bfs' ou 'dfs'." << endl;
    }

    file.close();
    return 0;
}


// g++ seu_codigo.cpp -o seu_programa
// ./seu_programa -f grafo_1.txt -o matriz (EXEMPLO)

//./seu_programa --file grafo.txt --output bfs_output.txt --option bfs

//./grafo.exe --file grafo_1.txt --output bfs_output.txt --option bfs