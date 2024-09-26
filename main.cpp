#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include "graph.h" // Certifique-se de que você tem o cabeçalho correto
using namespace std;

double media_lista_BFS(int vezes, const string &arquivo){
        Grafo grafo(arquivo,false);
        int i = 0;
        double acumulado_bfs = 0;
        unsigned int acumulado_dfs = 0;
        while (i<vezes){
            unsigned int s = std::rand() % grafo.getVertices();
            auto inicio = std::chrono::high_resolution_clock::now();
            grafo.BFS(s,"a.txt",0);
            auto fim = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duracao = fim - inicio;
            acumulado_bfs = acumulado_bfs + duracao.count();
            i++;
        }
        return acumulado_bfs;
    }

double media_lista_DFS(int vezes, const string &arquivo){
        Grafo grafo(arquivo,false);
        int i = 0;
        double acumulado_bfs = 0;
        unsigned int acumulado_dfs = 0;
        while (i<vezes){
            unsigned int s = std::rand() % grafo.getVertices();
            auto inicio = std::chrono::high_resolution_clock::now();
            grafo.DFS(s,"a.txt",0);
            auto fim = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duracao = fim - inicio;
            acumulado_bfs = acumulado_bfs + duracao.count();
            i++;
        }
        return acumulado_bfs;
    } 

int main(int argc, char *argv[]) {
    Grafo grafo("grafo_1.txt",true);
    int d = 0;
    d = grafo.distancia(20,"output.txt",false,30);
    cout << d << endl;
    double acumulado_bfs=0;
    double acumulado_dfs=0;
    for (int i =0;i<11;i++){

        unsigned int s = std::rand() % grafo.getVertices();
        auto inicio = std::chrono::high_resolution_clock::now();
        grafo.BFS(s,"a.txt",0);
        auto fim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracao = fim - inicio;
        acumulado_bfs= acumulado_bfs + duracao.count();
        std::cout << "Tempo de execução BFS: " << duracao.count() << " segundos" << std::endl;

        s = std::rand() % grafo.getVertices();
        inicio = std::chrono::high_resolution_clock::now();
        grafo.DFS(s,"a.txt",0);
        fim = std::chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        acumulado_dfs= acumulado_dfs + duracao.count();
        std::cout << "Tempo de execução DFS: " << duracao.count() << " segundos" << std::endl;
    }
    cout<< std::setprecision(6) << acumulado_bfs/10 << endl;
    cout << std::setprecision(10) << acumulado_dfs/10 << endl;
    return 0;
}

// g++ -O3 -o a.exe main.cpp graph.cpp
// ./a.exe --file grafo_0.txt --useMatrix nao
