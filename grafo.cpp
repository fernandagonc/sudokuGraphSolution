#include "grafo.hpp"
#include <vector>
#include <algorithm> 

void Grafo::setGrafo(int **matriz){
    int i, j;
    Vertice vertice;


    for(i = 0; i < this->n; i++){
        for(j = 0; j < this->n; j++){
            vertice.valor = matriz[i][j];

            if(vertice.valor != 0)
                vertice.colorido = true;
            else
                vertice.colorido = false;            
            
            vertice.grauSaturacao = 0;
            vertice.coresNaoDisponiveis = new bool[n];
            vertice.posicaoMatriz = this->n*i + j;
            vertice.adjList = getAdjList(i,j);

            grafo.push_back(vertice);

        }
    }
}

list<int> Grafo::getAdjList(int linha, int coluna){
    int i, j, posicao;
    int quadranteColuna, quadranteLinha;
    list<int> adjList;
    
// posicao = this->n*linha + coluna;
//quadrante coluna = coluna / colunasQuad
//quadrante linha = linha / linhaQuad
//posicQuad = n*quadrante linha + quadrante coluna

    for(j = 0; j < this->n; j++){//adjacencia da mesma linha
        if (j != coluna){
            //vertice = matriz[linha][j];
            posicao = this->n*linha + j;
            adjList.push_back(posicao);
        }
    }

    for(i = 0; i < this->n; i++){ //adiacencia da mesma coluna
        if (i != linha){
            //vertice = matriz[i][coluna];
            posicao = this->n*i + coluna;
            adjList.push_back(posicao);
        }
    }

    quadranteLinha = linha / this->linhasQuadrante;
    quadranteColuna = coluna / this->colunasQuadrante;


    int inicioQuadranteLinha = this->linhasQuadrante * quadranteLinha;
    int inicioQuadranteColuna = this->colunasQuadrante * quadranteColuna;
    
    for(i = inicioQuadranteLinha; i < (inicioQuadranteLinha + this->linhasQuadrante); i++){ //adiacencia do mesmo bloco
       for(j = inicioQuadranteColuna; j < (inicioQuadranteColuna + this->colunasQuadrante); j++){
           if(i == linha || j == coluna)
                continue;
           else{
                posicao = this->n*i + j;
                adjList.push_back(posicao);
           }
       
        }
    
    }
    return adjList;

}

vector<Vertice> Grafo::verticesSemCor(){
    vector<Vertice> semCor;

    for(int i = 0; i < n*n; i++){
        if(grafo[i].colorido)
            continue;
        else
            semCor.push_back(grafo[i]);
    }
    return semCor;

}

bool comparacao(Vertice &a, Vertice &b){ //organiza os em ordem decrescente de grau de saturacao
    return a.grauSaturacao > b.grauSaturacao;
}


vector<Vertice> Grafo::grauMaxSaturacao(vector<Vertice> semCor){
    Vertice vertice;
    list<int>::iterator iterator;

    if(!semCor.empty()){
        int nroVerticesNaoColoridos = semCor.size();
        for(int i = 0; i < nroVerticesNaoColoridos; i++){

            for(iterator = semCor[i].adjList.begin(); iterator != semCor[i].adjList.end(); ++iterator){
                int adjacente = *iterator;
            
                if(grafo[adjacente].colorido){
                    int corAdjacente = grafo[adjacente].valor-1;

                    if(semCor[i].coresNaoDisponiveis[corAdjacente] == false){
                        grafo[semCor[i].posicaoMatriz].grauSaturacao = grafo[semCor[i].posicaoMatriz].grauSaturacao +1;
                        grafo[semCor[i].posicaoMatriz].coresNaoDisponiveis[corAdjacente] = true;

                        semCor[i].grauSaturacao = grafo[semCor[i].posicaoMatriz].grauSaturacao;
                        semCor[i].coresNaoDisponiveis[corAdjacente] = true;
                    }
                }       
            }  
        }

        std::sort(semCor.begin(), semCor.end(), comparacao); 

        return semCor;
    }
    else
        return semCor;    

}

void Grafo::colorirVertice(int posicao){
   for(int i=0; i<n; i++){
       if(grafo[posicao].coresNaoDisponiveis[i] == false){
           grafo[posicao].valor = i+1;
           grafo[posicao].colorido = true;
           break;
       }
   }
}

void Grafo::buscaSolucao(){
    int verticesColoridos = 0;
    int numeroVertices = grafo.size();
    vector<Vertice> semCor = verticesSemCor();;
    int posicaoMaxSaturacao;

    for(int j=0; j<n*n; j++){
        if(grafo[j].valor != 0)
            verticesColoridos++;
    }

    while(verticesColoridos < numeroVertices){
        
        if (!semCor.empty()){
        
            semCor = grauMaxSaturacao(semCor);
            posicaoMaxSaturacao = semCor[0].posicaoMatriz;
           
            int corAnterior = grafo[posicaoMaxSaturacao].valor;
            colorirVertice(posicaoMaxSaturacao);
            
            if(grafo[posicaoMaxSaturacao].valor == corAnterior){
                printResultado();
                return;
            }

            verticesColoridos++;
            semCor.erase(semCor.begin());
        }
               
    }

    printResultado();
}

void Grafo::printResultado(){
    int totalVertices = n*n;
    int aux = 0;

    verificaSolucao();
    for(int i = 0; i < totalVertices; i++){
        aux++;
        std::cout << grafo[i].valor << " ";
        if(aux == n){
            std::cout  << " \n" ;
            aux = 0;
        }
    }
}

void Grafo::verificaSolucao(){
    int totalVertices = n*n;

    for(int i = 0; i < totalVertices; i++){
        if(grafo[i].valor != 0 && grafo[i].valor <= n){
            continue;
        }
        else{
            std::cout << "sem solução\n";
            return;
        }
        
    }
    std::cout << "solução\n";
    
}