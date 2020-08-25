#include <iostream>
#include <fstream>
#include <vector>
#include "grafo.hpp"

using std::string;
using std::vector;


int main (int argc, char **argv){

    if(argc > 0){
        std::ifstream entrada;
        string nomeArquivo = argv[1];
        entrada.open(nomeArquivo);

        if (!entrada) {
            std::cout << "Falha para abrir o arquivo";
            return -1;
        }

        Grafo grafo;
        int n, linhas, colunas, numero;

        entrada >> n >> colunas >> linhas;
        
        grafo.n = n;
        grafo.linhasQuadrante = linhas;
        grafo.colunasQuadrante = colunas;

        int **matriz;
        matriz = new int*[n];
        
        for (int i = 0; i < n; ++i)
            matriz[i] = new int[n];

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                entrada >> numero;
                matriz[i][j] =  numero;
            }
        }

        grafo.setGrafo(matriz);
        grafo.buscaSolucao();
        entrada.close();

    }       
    else{
        std::cout << "Por favor explicite como parâmetro um arquivo a ser lido";
    }
    
}
