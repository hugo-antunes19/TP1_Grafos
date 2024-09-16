#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    // Abrir o arquivo
    std::ifstream inputFile("example.txt");

    // checar se o arquivo está abrindo
    if (!inputFile.is_open()) {
        std::cerr << "Não conseguimos abrir o arquivo =[" << std::endl;
        return 1;
    }

    // ler o arquivo linha por linha
    std::string line;
    int i = 0;
    std::vector< int > esq; // o array esq contém todos os números da coluna da esquerda
    std::vector< int > dir; // o array dir os da direita
    while (std::getline(inputFile, line)) { // percorrer as linhas do arquivo

        // primeira linha possui a quantidade de vértices
        if (i == 0){
            std::stringstream ss(line);
            int vertices;
            ss >> vertices;
        }

        // esse else e while separam os números do input file
        else{
            std::string numberStr; // string para armazenar o número em string
            size_t x = 0;
        while (x < line.length()) { // percorrer os caracteres das linhas
            if (line[x] == '\t' || line[x] == ' ') { // teremos apenas duas colunas por linha, separadas por tab ou espaço
                std::stringstream ss(numberStr); // transformar string em inteiro
                int number;
                ss >> number;
                esq.push_back(number); // colocando o inteiro na lista
                numberStr = "";
            }
            numberStr += line[x];
            if (x == line.length() - 1) { // a coluna da direita acaba quando i chega no seu valor máximo
                std::stringstream ss(numberStr);
                int number;
                ss >> number;
                dir.push_back(number);
                numberStr = "";
            }
            x = x+1;
        }
    }
        i = i+1;
    }

    // fechar o arquivo
    inputFile.close();

    return 0;
}
