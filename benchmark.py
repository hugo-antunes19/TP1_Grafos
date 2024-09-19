import subprocess
import random
import time

arquivos_grafos = ['grafo_1.txt', 'grafo_2.txt']#, 'grafo_3.txt', 'grafo_4.txt', 'grafo_5.txt', 'grafo_6.txt']
vertices = [10000, 49948, 375000, 375000, 4843750, 4843750]
vezes_para_rodar = 100

def executar_busca(tipo_busca, input_file, output_file, time_file, n_execucoes, usar_matriz, n):


    for _ in range(n_execucoes):
        vertice_inicial = random.randint(1, n)  

        subprocess.run([
            './grafo_classe.exe',  
            '--file', input_file,
            '--output', output_file,
            '--option', tipo_busca,
            '--time', time_file,  
            '--inicial', str(vertice_inicial),
            '--useMatrix', usar_matriz
        ])

if __name__ == "__main__":
    output_file = 'saida.txt' 
    for i in range(len(arquivos_grafos)):
        grafo = arquivos_grafos[i]
        n_vertices = vertices[i]
        saida_bfs_l = "saida_bfs_L_" + grafo 
        saida_dfs_l = "saida_dfs_L_" + grafo 
        saida_bfs_m = "saida_bfs_M_" + grafo 
        saida_dfs_m = "saida_dfs_M_" + grafo 

        executar_busca('bfs', grafo, output_file, saida_bfs_l, vezes_para_rodar, "nao", n_vertices)
        executar_busca('dfs', grafo, output_file, saida_dfs_l, vezes_para_rodar, "nao", n_vertices)
        executar_busca('bfs', grafo, output_file, saida_bfs_m, vezes_para_rodar, "matriz", n_vertices)
        executar_busca('dfs', grafo, output_file, saida_dfs_m, vezes_para_rodar, "matriz", n_vertices)
