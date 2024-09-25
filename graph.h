#ifndef GRAPH_H
#define GRAPH_H

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
    // Construtor
    Grafo(unsigned int v, bool isMatriz);

    // Métodos
    void adicionarAresta(unsigned int x, unsigned int y);
    
    // Graus de um vértice
    void graus();

    // Imprime a Matriz de Adjacência
    void printMatrizAdj() const;

    // Imprime a Lista de Adjacência
    void printListAdj() const;

    // Escrever em arquivo (para retornar a árvore gerada por busca)
    void Write_file_busca(std::vector<unsigned int> pai, std::vector<unsigned int> nivel, const std::string& outputFile, unsigned int s);

    // Obtém os vizinhos de um vértice na matriz de adjacência
    std::vector<unsigned int> getVizinhosMatriz(unsigned int v) const;

    // Algoritmo Diâmetro aproximado
    int aprox(unsigned int start, const std::string& outputFile, bool write_tree);

    // Algoritmo diâmetro não aproximado
    int diameter(const std::string& outputFile, bool write_tree);

    // Algoritmo Distância
    int distancia(unsigned int start, const std::string& outputFile, bool write_tree, unsigned int end);

    // Algoritmo BFS
    void BFS(unsigned int s, const std::string& outputFile, bool write_tree, unsigned int e = 0);

    // Algoritmo DFS
    void DFS(unsigned int s, const std::string& outputFile, bool write_tree);

    // Componentes Conexas
    std::map<unsigned int, std::vector<std::vector<unsigned int>>, std::greater<unsigned int>> ComponentesConexas();

    // Imprimir Componentes Conexas
    void imprimirComponentesConexas(const map<long long, vector<vector<long long>>, std::greater<long long>>& componentesConexas);
};
#endif // GRAPH_H
