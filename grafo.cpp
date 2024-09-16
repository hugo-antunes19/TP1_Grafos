#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    // Abrir o arquivo
    ifstream file("grafos_2.txt");

    // Checar se o file está abrindo
    if (!file.is_open()) {
        cout << "Não conseguimos abrir o arquivo =[" << endl;
        return 1;
    }
    long long vertices;
    file >> vertices;
    vector<vector< long long>> listAdj(vertices+1); // Cria vetor de vetores
    vector<vector< long long>> matrizAdj(vertices+1);
    long long x, y, arestas;

    while (file >> x >> y) { // Atribui os inteiros das colunas para cada variável (x e y)
        listAdj[x].push_back(y); // Adiciona na Lista de Adjacência
        listAdj[y].push_back(x);
        matrizAdj[x][y] = 1; // Adiciona na Matriz de Adjacência
        matrizAdj[y][x] = 1;
        arestas++;
    }


    // Fechar o arquivo
    file.close();

    return 0;
}
