#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
#include "graph.h"
// Certifique-se de que você tem o cabeçalho correto

using namespace std;

int main(int argc, char *argv[]) {
    // Variáveis para capturar as opções
    int opt;
    string inputFile, outputFile, timeFile_bfs, timeFile_dfs; 
    string useMatrix;

    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"output", required_argument, 0, 'u'},
        {"timeFile_bfs", required_argument, 0, 'o'},
        {"timeFile_dfs", required_argument, 0, 't'},
        {"useMatrix", required_argument, 0, 'm'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "f:u:o:t:m:", long_options, NULL)) != -1) {
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
            default:
                cerr << "Opção inválida." << endl;
                return 1;
        }
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo: " << inputFile << endl;
        return 1;
    }

    unsigned int vertices;
    file >> vertices;

    bool usaMatriz = (useMatrix == "matriz");
    Grafo grafo(vertices, usaMatriz);

    unsigned int x, y;
    while (file >> x >> y) {
        if (x <= vertices && y <= vertices) {
            grafo.adicionarAresta(x, y);
        }
    }

    // Exemplo de como registrar tempo de execução (você pode implementar isso)
    /*
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
    */

    //Exemplo de como calcular e imprimir componentes conexas (código utilizado para obter os resultados dos experimentos)

    /*
    Grafo grafo(grafo_1.txt, usaMatriz) // o primeiro termo é alterado de acordo com o grafo que se deseja utilizar
    
    map<unsigned int, vector<vector<unsigned int>>, greater<unsigned int>> Comp_do_Grafo = grafo.ComponentesConexas();
    grafo.imprimirComponentesConexas(Comp_do_Grafo);

    cout << "Numero de Componentes Conexas: " << grafo.n_CompConexa << endl;
    */

    // Exemplo de chamada para um método que você precisa implementar
    grafo.graus(); // Certifique-se de que o método graus() esteja definido

    return 0;
}


// g++ -o a.exe main.cpp graph.cpp
// ./a.exe --file grafo_0.txt --useMatrix nao
