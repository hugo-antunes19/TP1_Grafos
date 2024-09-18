#include <bits/stdc++.h>
#include <iostream>
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

int main() {
    // Abrir o arquivo
    ifstream file("./grafo_1.txt");
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }

    long long vertices;
    file >> vertices;
    vector<vector<long long>> listAdj(vertices+1); // Cria vetor de vetores
    vector<vector<long long>> matrizAdj(vertices+1, vector<long long>(vertices+1, 0)); // Inicializa a matriz
    long long x, y, arestas = 0;

    while (file >> x >> y) { // Atribui os inteiros das colunas para cada variável (x e y)
        if (x <= vertices && y <= vertices) { // Verifica se x e y estão dentro dos limites
            listAdj[x].push_back(y); // Adiciona na Lista de Adjacência
            listAdj[y].push_back(x);
            matrizAdj[x][y] = 1; // Adiciona na Matriz de Adjacência
            matrizAdj[y][x] = 1;
            arestas++;
        }
    }
    // Fechar o arquivo
    file.close();

    cout << "Lista de Adjacência:" << endl;
    printListAdj(listAdj);

    return 0;
}
