#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    // Open the input file
    std::ifstream inputFile("example.txt");

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    int i = 0;
    while (std::getline(inputFile, line)) {

        // Primeira linha possui a quantidade de vértices
        if (i == 0){
            std::stringstream ss(line);
            int vertices;
            ss >> vertices;
        }
        else{
            for (size_t i = 0; i < line.length(); ++i) {
                if (line[i] == ' ' || line[i] == '  '){
                    std::stringstream ss(line[i]);
                }
    }
        }
        std::cout << line << std::endl;
        i = i+1;
    }

    // Close the file
    inputFile.close();

    return 0;
}
