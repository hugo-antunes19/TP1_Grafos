#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
#include <numeric>
using namespace std;

class Grafo {
private:
    vector<vector<bool>> matrizAdj;
    vector<vector<unsigned int>> listAdj;
    unsigned int vertices;
    unsigned int arestas;
    bool usaMatriz;
    vector<bool> visitado;
    vector<unsigned int> pai;
    vector<unsigned int> nivel;
    unsigned int n_CompConexa;


public:


    Grafo(unsigned int v, bool isMatriz) : vertices(v), usaMatriz(isMatriz), visitado(vertices + 1, false), 
    pai(vertices + 1, -1), nivel(vertices + 1, -1) {

        if (usaMatriz) {
            matrizAdj.resize(vertices + 1, vector<bool>(vertices + 1, 0));
        } else {
            listAdj.resize(vertices + 1);
        }
    }

    // Adiciona uma aresta ao grafo
    void adicionarAresta(unsigned int x, unsigned int y) {
        if (usaMatriz) {
            matrizAdj[x][y] = 1;
            matrizAdj[y][x] = 1;
        } else {
            listAdj[x].push_back(y);
            listAdj[y].push_back(x);
        }
    }

    void graus() {
        int max=0;
        int min=0;
        vector <int> graus(vertices + 1, -1);
        if (usaMatriz) {
            for (int i = 0; i<vertices;i++){
                graus[i] = accumulate(matrizAdj[i].begin(),matrizAdj[i].end(),0); //criando vetor que contém os graus de cada vértice
            }
            for (int i = 0; i < vertices; i ++){ //selecionando o menor e maior
                if (graus[i]>max){
                    max = graus[i];
                }
                if (graus[i]<min){
                    min = graus[i];
                }
            }

        } else {
            for (int i = 0; i<vertices;i++){
                graus[i] = listAdj[i].size(); //criando vetor que contém os graus de cada vértice
            }
            for (int i = 0; i < vertices; i ++){ //selecionando o menor e maior
                if (graus[i]>max){
                    max = graus[i];
                }
                if (graus[i]<min){
                    min = graus[i];
                }
            }

        }
        cout << max << ' ' << min << endl;
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
    void Write_file_busca(vector<unsigned int> pai,vector<unsigned int> nivel, const string& outputFile, unsigned int s){
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "Erro ao abrir arquivo de saída." << endl;
            return;
        }
        outFile << "Árvore gerada por busca\n";

        for (unsigned int v = 1; v <= vertices; v++)
        if (pai[v] != -1 || v == s) {
            outFile << "Vértice: " << v << ", Pai: " << pai[v] << ", Nível: " << nivel[v] << endl;
           }
        outFile.close();
    }

    // Obtém os vizinhos de um vértice na matriz de adjacência
    vector<unsigned int> getVizinhosMatriz(unsigned int v) const {
        vector<unsigned int> vizinhos;
        for (unsigned int i = 1; i <= vertices; ++i) {
            if (matrizAdj[v][i] == 1) {
                vizinhos.push_back(i);
            }
        }
        return vizinhos;
    }

    // Algoritmo Diâmetro aproximado
    int aprox(unsigned int start, const string& outputFile, bool write_tree){
        BFS (start, outputFile, write_tree); // encontrando a primeira extremidade (x)
        int maior = 0;
        int x;
        for (int i = 0; i < nivel.size(); i++){
            if (nivel[i]> maior and nivel[i] != 4294967295){
                maior = nivel[i];
                x = i;
            }
        }
        BFS (x, outputFile, write_tree); // encontrando a segunda extremidade começando da primeira extremidade (x)
        for (int i = 0; i < nivel.size(); i++){
            if (nivel[i]> maior and nivel[i] != 4294967295){
                maior = nivel[i];
                x = i;
            }
        }
        return maior;
    }

    // Algoritmo diâmetro não aproximado
    int diameter(const std::string& outputFile, bool write_tree) {
        int x = 0;
        int maior = 0; // Inicializa maior com um valor negativo

        for (int i = 1; i < vertices; i++) {
            BFS(i, outputFile, 1);
            for (int j = 0; j < nivel.size(); j++) {
                if (nivel[j] > maior and nivel[j] != 4294967295 and !nivel.empty()) {
                    maior = nivel[j];
                    x = j; // primeira extremidade
                }
            }
        }

        int ext = 0; // segunda extremidade
        BFS(x, outputFile, 1);
        for (int j = 0; j < nivel.size(); j++) {
            if (nivel[j] > maior and nivel[j] != 4294967295 and !nivel.empty()) {
                maior = nivel[j];
                ext = j;
            }
        }

        return maior;
    }

    // Algoritmo Distância
    int distancia(unsigned int start, const string& outputFile, bool write_tree, unsigned int end){
        int level;
        BFS(start, outputFile, write_tree,end);
        level = nivel[end];
        return level;
    }

    // Algoritmo BFS
    void BFS(unsigned int s, const string& outputFile, bool write_tree, unsigned int e = 0) {
        visitado.assign(vertices + 1, false);
        pai.assign(vertices + 1, -1);
        nivel.assign(vertices + 1, -1);

        queue<unsigned int> Q;
        
        visitado[s] = true;
        nivel[s] = 0;
        Q.push(s);

        while (!Q.empty()) {
            if (e!= 0 and visitado[e]){
                break;
            }
            unsigned int v = Q.front();
            Q.pop();

            const vector<unsigned int>& vizinhos = usaMatriz ? getVizinhosMatriz(v) : listAdj[v];
            for (unsigned int w : vizinhos) {
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

    void DFS(unsigned int s, const string& outputFile, bool write_tree) {
        visitado.assign(vertices + 1, false);
        pai.assign(vertices + 1, -1);
        nivel.assign(vertices + 1, -1);

        stack<unsigned int> pilha;

        pilha.push(s);
        nivel[s] = 0;

        while (!pilha.empty()) {
            unsigned int v = pilha.top();
            pilha.pop();

            if (!visitado[v]) {
                visitado[v] = true;

                // Para cada vizinho do vértice v
                const vector<unsigned int>& vizinhos = usaMatriz ? getVizinhosMatriz(v) : listAdj[v];
                for (unsigned int w : vizinhos) {
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

    map<unsigned int, vector<vector<unsigned int>>, greater<unsigned int>> ComponentesConexas() {   
        // Mapa onde a chave é o tamanho da componente e os valores são os vértices da componente
        map<unsigned int, vector<vector<unsigned int>>, greater<unsigned int>> componentesConexas;
        vector<bool> visitado(vertices + 1, false); // Vetor para marcar vértices visitados
        queue<unsigned int> Q; // Fila para a BFS

        // Percorre todos os vértices do grafo
        for (unsigned int i = 1; i <= vertices; ++i) {
            if (!visitado[i]) {
                // Se o vértice ainda não foi visitado, achamos uma nova componente conexa
                vector<unsigned int> componenteAtual; // Armazena os vértices da componente atual
                n_CompConexa ++;
                // Executa a BFS a partir do vértice 'i'
                Q.push(i);
                visitado[i] = true;

                while (!Q.empty()) {
                    unsigned int v = Q.front();
                    Q.pop();

                    componenteAtual.push_back(v); // Adiciona o vértice à componente atual

                    const vector<unsigned int>& vizinhos = usaMatriz ? getVizinhosMatriz(v) : listAdj[v];
                    for (unsigned int w : vizinhos) {
                        if (!visitado[w]) {
                            visitado[w] = true;
                            Q.push(w);
                        }
                    }
                }

                // Adiciona a componente atual ao mapa, usando o tamanho da componente como chave
                unsigned int tamanho = componenteAtual.size();
                componentesConexas[tamanho].push_back(componenteAtual); 
            }
        }

        return componentesConexas; // Retorna o mapa de componentes
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
            case 'm':
                useMatrix = optarg;
                break;
        }
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }

    unsigned int vertices;
    unsigned int arestas = 0;
    file >> vertices;

    bool usaMatriz = (useMatrix == "matriz");
    Grafo grafo(vertices, usaMatriz);

    unsigned int x, y;
    while (file >> x >> y) {
        if (x <= vertices && y <= vertices) {
            grafo.adicionarAresta(x, y);
            arestas++;
        }
    }

    // ofstream timeOutFile_bfs(timeFile_bfs, ios::app);
    // if (!timeOutFile_bfs.is_open()) {
    //     cerr << "Erro ao abrir arquivo de tempo de execução bfs." << endl;
    //     return 1;
    // }

    // ofstream timeOutFile_dfs(timeFile_dfs, ios::app);
    // if (!timeOutFile_dfs.is_open()) {
    //     cerr << "Erro ao abrir arquivo de tempo de execução dfs." << endl;
    //     return 1;
    // }
    grafo.graus();
    return 0;
}


// g++ seu_codigo.cpp -o seu_programa
// ./seu_programa -f grafo_1.txt -o matriz (EXEMPLO)

//./seu_programa --file grafo.txt --output bfs_output.txt --option bfs

//./grafo.exe --file grafo_1.txt --output bfs_output.txt --option bfs