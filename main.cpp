#include <bits/stdc++.h>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <queue> 
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include "graph.h"
// Certifique-se de que você tem o cabeçalho correto

using namespace std;

int main(int argc, char *argv[]) {

    //Exemplo de como calcular e imprimir componentes conexas (código utilizado para obter os resultados dos experimentos)

    /*
    Grafo grafo(grafo_1.txt, usaMatriz) // o primeiro termo é alterado de acordo com o grafo que se deseja utilizar
    
    map<unsigned int, vector<vector<unsigned int>>, greater<unsigned int>> Comp_do_Grafo = grafo.ComponentesConexas();
    grafo.imprimirComponentesConexas(Comp_do_Grafo);

    cout << "Numero de Componentes Conexas: " << grafo.n_CompConexa << endl;
    */

    // Exemplo de chamada para um método que você precisa implementar
    // grafo.graus(); // Certifique-se de que o método graus() esteja definido
    for (int i =0;i<11;i++){
        Grafo grafo("grafo_3.txt",1);
        unsigned int s = std::rand() % grafo.getVertices();
        auto inicio = std::chrono::high_resolution_clock::now();
        grafo.BFS(s,"a.txt",0);
        auto fim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracao = fim - inicio;
        std::cout << "Tempo de execução BFS: " << duracao.count() << " segundos" << std::endl;

        s = std::rand() % grafo.getVertices();
        inicio = std::chrono::high_resolution_clock::now();
        grafo.DFS(s,"a.txt",0);
        fim = std::chrono::high_resolution_clock::now();
        duracao = fim - inicio;
        std::cout << "Tempo de execução DFS: " << duracao.count() << " segundos" << std::endl;
    }
    return 0;
}


// g++ -O3 -o a.exe main.cpp graph.cpp
// ./a.exe --file grafo_0.txt --useMatrix nao
