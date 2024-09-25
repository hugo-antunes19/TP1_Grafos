# **Trabalho Prático de Grafos - 2024.2**

**Alunos responsáveis:** Hugo Antunes e Vivian Souza

## Descrição

Este é o Trabalho Prático (TP) da disciplina de Grafos de 2024.2. O projeto foi inteiramente desenvolvido em C++ e está organizado em três arquivos principais:

- `graph.h`: Cabeçalho da classe.
- `graph.cpp`: Implementação dos métodos da classe.
- `main.cpp`: Utilização da biblioteca e realização dos testes.

## Instruções de Compilação e Execução

Para compilar e executar a biblioteca, siga os passos abaixo (em Linux):

1. **Entrar no diretório onde estão localizados os arquivos `graph.h`, `graph.cpp` e `main.cpp`:**

   ```sh
   cd ./path/
   
2. **Compilar os arquivos (utilizando a otimização O3):**
   
   ```sh
   g++ -O3 -o a.exe main.cpp graph.cpp
   
4. **Executar o programa:**

   ```sh
   ./a.exe

## Exemplo de Uso
### Calcular e Imprimir Componentes Conexas
O código abaixo mostra como calcular e imprimir as componentes conexas do grafo:

  ```sh
   Grafo grafo("grafo_1.txt", usaMatriz); // O primeiro argumento é alterado de acordo com o grafo que se deseja utilizar

std::map<unsigned int, std::vector<std::vector<unsigned int>>, std::greater<unsigned int>> Comp_do_Grafo = grafo.ComponentesConexas();
grafo.imprimirComponentesConexas(Comp_do_Grafo);

std::cout << "Número de Componentes Conexas: " << grafo.n_CompConexa << std::endl
```

### Chamada para um Método a Ser Implementado
Certifique-se de que o método graus() esteja definido:

  ```sh
  grafo.graus();
   ```
## Observações
- Preste atenção na importação dos arquivos, pois isso impacta diretamente no uso da biblioteca graph
- Certifique-se de que todos os arquivos necessários (graph.h, graph.cpp, main.cpp) estão no mesmo diretório antes de compilar.




