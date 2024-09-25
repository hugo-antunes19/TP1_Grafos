#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
#include <algorithm>
using namespace std;

class Grafo {
private:
    vector<vector<bool>> matrizAdj;
    vector<vector<unsigned int>> listAdj;
    unsigned int vertices;
    unsigned int arestas;
    bool usaMatriz;
    vector<bool> visitado;
    vector<int> pai;
    vector<int> nivel;
    unsigned int n_CompConexa; 

public:
    // Construtor
    Grafo(const string &grafo, bool isMatriz);

    // Get vértices
    unsigned int getVertices();

    // Criar txt
    void write_general_info(const string &arquivo);

    // Métodos
    void adicionarAresta(unsigned int x, unsigned int y);
    
    // Graus de um vértice
    tuple<unsigned int, unsigned int, unsigned int, float> graus();

    // Imprime a Matriz de Adjacência
    void printMatrizAdj() const;

    // Imprime a Lista de Adjacência
    void printListAdj() const;

    // Escrever em arquivo (para retornar a árvore gerada por busca)
    void Write_file_busca(std::vector<int> pai, std::vector<int> nivel, const std::string& outputFile, unsigned int s);

    // Obtém os vizinhos de um vértice na matriz de adjacência
    std::vector<unsigned int> getVizinhosMatriz(unsigned int v) const;

    // Algoritmo Diâmetro aproximado
    int aprox(unsigned int start, const std::string& outputFile, bool write_tree);

    // Algoritmo diâmetro não aproximado
    int diameter();

    // Algoritmo Distância
    int distancia(unsigned int start, const std::string& outputFile, bool write_tree, unsigned int end);

    // Algoritmo BFS
    void BFS(unsigned int s, const std::string& outputFile, bool write_tree, unsigned int e = 0);

    // Algoritmo DFS
    void DFS(unsigned int s, const std::string& outputFile, bool write_tree);

    // Componentes Conexas
    std::map<unsigned int, std::vector<std::vector<unsigned int>>, std::greater<unsigned int>> ComponentesConexas();

    // Imprimir Componentes Conexas
    void imprimirComponentesConexas(const map<unsigned int, vector<vector<unsigned int>>, std::greater<unsigned int>>& componentesConexas);
};
#endif // GRAPH_H
