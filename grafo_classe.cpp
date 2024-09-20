#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
using namespace std;

class Grafo {
private:
    vector<vector<long long>> matrizAdj;
    vector<vector<long long>> listAdj;
    long long vertices;
    long long arestas;
    bool usaMatriz;
    vector<bool> visitado;
    vector<long long> pai;
    vector<long long> nivel;

public:
    Grafo(long long v, bool isMatriz) : vertices(v), usaMatriz(isMatriz), visitado(vertices + 1, false), 
    pai(vertices + 1, -1), nivel(vertices + 1, -1) {

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

    //escrever em arquivo (para retornar a arvore gerada por busca)
    void Write_file_busca(vector<long long> pai,vector<long long> nivel, const string& outputFile, long long s){
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "Erro ao abrir arquivo de saída." << endl;
            return;
        }
        outFile << "Árvore gerada por busca\n";

        for (long long v = 1; v <= vertices; v++)
        if (pai[v] != -1 || v == s) {
            outFile << "Vértice: " << v << ", Pai: " << pai[v] << ", Nível: " << nivel[v] << endl;
           }
        outFile.close();
    }

    // Algoritmo BFS
    void BFS(long long s, const string& outputFile, bool write_tree) {
        visitado.assign(vertices + 1, false);
        pai.assign(vertices + 1, -1);
        nivel.assign(vertices + 1, -1);

        queue<long long> Q;
        
        visitado[s] = true;
        nivel[s] = 0;
        Q.push(s);

        while (!Q.empty()) {
            long long v = Q.front();
            Q.pop();

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
        if (write_tree){
            Write_file_busca(pai, nivel, outputFile, s);
        }

    }

    void DFS(long long s, const string& outputFile, bool write_tree) {
        visitado.assign(vertices + 1, false);
        pai.assign(vertices + 1, -1);
        nivel.assign(vertices + 1, -1);

        stack<long long> pilha;

        pilha.push(s);
        nivel[s] = 0;

        while (!pilha.empty()) {
            long long v = pilha.top();
            pilha.pop();

            if (!visitado[v]) {
                visitado[v] = true;

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
        if (write_tree){
            Write_file_busca(pai, nivel, outputFile, s);
        }

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
    string inputFile, outputFile, timeFile_bfs; 
    string timeFile_dfs; // Arquivo para salvar o tempo de execução
    string useMatrix; // Matriz ou Lista

    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"output", required_argument, 0, 'u'},
        {"timeFile_bfs", required_argument, 0, 'o'},
        {"timeFile_dfs", required_argument, 0, 't'},
        {"useMatrix", required_argument, 0, 'm'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "f:u:o:t:m", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                inputFile = optarg;
                break;
            case 'u':
                outputFile = optarg;
                break;
            case 'o':
                timeFile_bfs = optarg;
                break;
            case 't':
                timeFile_dfs = optarg;
                break;
            case 'm':
                useMatrix = optarg;
                break;
        }
    }

    if (inputFile.empty() || timeFile_bfs.empty() || outputFile.empty()) {
        cerr << "Uso: " << argv[0] << " --file <inputfile> --output <outputfile> --option <option>" << endl;
        return 1;
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }

    long long vertices;
    long long arestas = 0;
    file >> vertices;

    bool usaMatriz = (useMatrix == "matriz");
    Grafo grafo(vertices, usaMatriz);

    long long x, y;
    while (file >> x >> y) {
        if (x <= vertices && y <= vertices) {
            grafo.adicionarAresta(x, y);
            arestas++;
        }
    }

    ofstream timeOutFile_bfs(timeFile_bfs, ios::app);
    if (!timeOutFile_bfs.is_open()) {
        cerr << "Erro ao abrir arquivo de tempo de execução bfs." << endl;
        return 1;
    }

    ofstream timeOutFile_dfs(timeFile_dfs, ios::app);
    if (!timeOutFile_dfs.is_open()) {
        cerr << "Erro ao abrir arquivo de tempo de execução dfs." << endl;
        return 1;
    }

    // Inicializa o gerador de números aleatórios com um seed (semente)
    random_device rd;  
    mt19937 gen(rd()); // Gerador de números aleatórios Mersenne Twister
    
    // Define a distribuição de números (neste caso, inteiros entre 1 e vertices)
    uniform_int_distribution<> distrib(1, vertices);

    for (int n = 1; n <= 100; n++){

        long long random_number = distrib(gen);

        auto inicio_bfs = chrono::high_resolution_clock::now(); // Início do tempo
        grafo.BFS(random_number, outputFile, false);
        auto fim_bfs = chrono::high_resolution_clock::now(); // Fim do tempo
        chrono::duration<double> duracao_bfs = fim_bfs - inicio_bfs;
        timeOutFile_bfs << fixed << setprecision(6) << duracao_bfs.count() << " s= " << random_number << endl;


        auto inicio_dfs = chrono::high_resolution_clock::now(); // Início do tempo
        grafo.DFS(random_number, outputFile, false);
        auto fim_dfs = chrono::high_resolution_clock::now(); // Fim do tempo
        chrono::duration<double> duracao_dfs = fim_dfs - inicio_dfs;
        timeOutFile_dfs << fixed << setprecision(6) << duracao_dfs.count() << " s= " << random_number << endl;

    }


    timeOutFile_bfs.close();
    timeOutFile_dfs.close();
    file.close();
    return 0;
}



// g++ seu_codigo.cpp -o seu_programa
// ./seu_programa -f grafo_1.txt -o matriz (EXEMPLO)

//./seu_programa --file grafo.txt --output bfs_output.txt --option bfs

//./grafo.exe --file grafo_1.txt --output bfs_output.txt --option bfs