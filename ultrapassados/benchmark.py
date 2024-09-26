import subprocess
import random
import time

arquivos_grafos = ['grafo_1.txt', 'grafo_2.txt']#, 'grafo_3.txt', 'grafo_4.txt', 'grafo_5.txt', 'grafo_6.txt']
vertices = [10000, 49948, 375000, 375000, 4843750, 4843750]
vezes_para_rodar = 100

def executar_busca(input_file, output_file, time_file_bfs, time_file_dfs, usar_matriz):
 
        subprocess.run([
            './grafo_classe.exe',  
            '--file', input_file,
            '--output', output_file,
            '--timeFile_bfs', time_file_bfs,
            '--timeFile_dfs', time_file_dfs,  
            '--useMatrix', usar_matriz
        ])

if __name__ == "__main__":
    output_file = 'saida.txt' 
    for i in range(len(arquivos_grafos)):
        grafo = arquivos_grafos[i]
        saida_bfs_l = "saida_bfs_L_" + grafo 
        saida_dfs_l = "saida_dfs_L_" + grafo 
        saida_bfs_m = "saida_bfs_M_" + grafo 
        saida_dfs_m = "saida_dfs_M_" + grafo 

        executar_busca(grafo, output_file, saida_bfs_l, saida_dfs_l, "nao")
        executar_busca(grafo, output_file, saida_bfs_m, saida_dfs_m, "matriz")
