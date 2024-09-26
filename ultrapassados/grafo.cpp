#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
using namespace std;

void printMatrizAdj(const vector<vector<long long>>& matrizAdj) {
    for (size_t i = 1; i < matrizAdj.size(); ++i) {
        for (size_t j = 1; j < matrizAdj[i].size(); ++j) {
            cout << matrizAdj[i][j] << " ";
        }
        cout << endl;
    }
}

void printListAdj(const vector<vector<long long>>& listAdj) {
    for (size_t i = 1; i < listAdj.size(); ++i) {
        cout << i << ": ";
        for (size_t j = 0; j < listAdj[i].size(); ++j) {
            cout << listAdj[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    // Abrir o arquivo
    int opt;
    string inputFile;
    string option; // Matriz ou Lista
    int matriz;
    int lista;
    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"option", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "f:o:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                inputFile = optarg;
                break;
            case 'o':
                option = optarg;
                break;
        }
    }

    if (option == "matriz"){
        matriz = 1;
    }

    else {
        lista = 1;
    }

    if (inputFile.empty() || option.empty()) {
        cerr << "Uso: " << argv[0] << " --file <inputfile> --option <option>" << endl;
        return 1;
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }
    long long vertices;
    file >> vertices;
    long long x, y, arestas = 0;
    if (lista ==1){
        vector<vector<long long>> listAdj(vertices+1); // Cria Lista de Adjacência
        while (file >> x >> y) { // Atribui os inteiros das colunas para cada variável (x e y)
        if (x <= vertices && y <= vertices) { // Verifica se x e y estão dentro dos limites
            listAdj[x].push_back(y); // Adiciona na Lista de Adjacência
            listAdj[y].push_back(x);
            arestas++;
            }
        }
        cout << "Lista de Adjacência:" << endl;
        printListAdj(listAdj);
    }
    if (matriz == 1){
        vector<vector<long long>> matrizAdj(vertices+1, vector<long long>(vertices+1, 0)); // Inicializa a matriz

        while (file >> x >> y) { // Atribui os inteiros das colunas para cada variável (x e y)
        if (x <= vertices && y <= vertices) { // Verifica se x e y estão dentro dos limites
            matrizAdj[x][y] = 1; // Adiciona na Matriz de Adjacência
            matrizAdj[y][x] = 1;
            arestas++;
            }
        }
        cout << "Matriz de Adjacência:" << endl;
        printMatrizAdj(matrizAdj);
    }
    // Fechar o arquivo
    file.close();

    return 0;
}

// g++ seu_codigo.cpp -o seu_programa
// ./seu_programa -f grafo_1.txt -o matriz (EXEMPLO)
