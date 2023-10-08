#include "graph.hpp"
#include "ListaAdjacencia.hpp"

#include <iostream>

using namespace std;

//vertices
//arrestas

Grafo::Grafo() {
   
    return;
}

Grafo::~Grafo() {
    return;
}

void Grafo::InsereVertice() {
    vertices.InserirVertice();
    
}

void Grafo::InsereAresta(int v, int w) {
    vertices.InserirAresta(v,w);
    
    
}

int Grafo::QuantidadeVertices() {
    return vertices.TamanhoVertices();

}

int Grafo::QuantidadeArestas() {
    int sum = 0;
    for (int i = 0; i < vertices.TamanhoVertices(); i++)
    {
        //cout << "Soma : " << sum << endl;
        sum += vertices.TamanhoAresta(i);
    }
    //cout << "Soma Final: " << sum << endl;
    return sum;
        

}

int Grafo::GrauMinimo() {
    int sum = 10000;
    for (int i = 0; i < vertices.TamanhoVertices(); i++)
    {
        if(sum > vertices.TamanhoAresta(i))
            sum = vertices.TamanhoAresta(i);
    }
    return sum;

}

int Grafo::GrauMaximo() {
    int sum = 0;
    for (int i = 0; i < vertices.TamanhoVertices(); i++)
    {
        if(sum < vertices.TamanhoAresta(i))
            sum = vertices.TamanhoAresta(i);
    }
    return sum;

}

void Grafo::ImprimeVizinhos(int v) {
    vertices.ImprimirVizinho(v);
}


