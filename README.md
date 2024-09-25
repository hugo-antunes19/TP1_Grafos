*Esse é o TP da disciplina de Grafos de 2024.2*
Alunos responsáveis: Hugo Antunes e Vivian Souza

O nosso trabalho foi inteiramente feito em c++, sendo separado em 3 arquivos que precisam ser baixados para a devida importação da biblioteca.
O arquivo graph.h é o cabeçalho da classe, graph.cpp é a implementação dos métodos da classe e o main.cpp é a utilização da biblioteca diretamente, onde foram realizados os testes.
Favor prestar atenção na importação feita, uma vez que isso impacta diretamente no uso da nossa biblioteca 'graph'.

Para compilar a nossa biblioteca, sugerimos os seguintes comandos (em linux).

1- Entrar no diretório onde está localizado os arquivos graph.h, graph.cpp e main.pp
  cd ./path/

2- Compilar o arquivo (fizemos utilizando a otimização O3)
  g++ -O3 -o a.exe main.cpp graph.cpp

3- Rodar o executável (que chamamos de a.exe)
  ./a.exe


Exemplo de como calcular e imprimir componentes conexas (código utilizado para obter os resultados dos experimentos)

Grafo grafo(grafo_1.txt, usaMatriz) primeiro termo é alterado de acordo com o grafo que se deseja utilizar

map<unsigned int, vector<vector<unsigned int>>, greater<unsigned int>> Comp_do_Grafo = grafo.ComponentesConexas();
grafo.imprimirComponentesConexas(Comp_do_Grafo);

cout << "Numero de Componentes Conexas: " << grafo.n_CompConexa << endl;

Exemplo de chamada para um método que você precisa implementar
grafo.graus(); // Certifique-se de que o método graus() esteja definido
