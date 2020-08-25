#ifndef GRAFO
#define GRAFO

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using std::list;
using std::vector;

struct Vertice{
    list<int> adjList;
    int valor, posicaoMatriz;
    bool colorido;
    bool *coresNaoDisponiveis;
    int grauSaturacao;
};

class Grafo{
    public:
        vector<Vertice> grafo;    
        int n, linhasQuadrante, colunasQuadrante;

        void setGrafo(int **matriz);
        list<int> getAdjList(int linha, int coluna);

        void buscaSolucao();
        vector<Vertice> verticesSemCor();
        vector<Vertice> grauMaxSaturacao(vector<Vertice> semCor);
        void colorirVertice(int posicao);
        
        void verificaSolucao();
        void printResultado();

};

#endif