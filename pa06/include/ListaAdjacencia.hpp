#ifndef LISTA_HPP
#define LISTA_HPP


struct Aresta {
  int valor_aresta;
  Aresta* proximo_aresta;
};

struct Vertice {
    int valor_vertice;
    Aresta* aresta;
    Vertice* proximo_vertice;

};

class ListaAdjacencia {

  public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    void Remover();

    void InserirAresta(int valor_vertice, int valor_arresta);
    void InserirVertice();

    bool Vazia();

    int TamanhoVertices();

    int TamanhoAresta(int valor_vertice);

    void ImprimirLista();
    void ImprimirVizinho(int valor_vertice); 
 

    Vertice* primeiro_vertice;
    Vertice* ultimo_vertice;
    int index_vertices;
}; 

#endif