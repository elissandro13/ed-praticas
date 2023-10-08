#include "ListaAdjacencia.hpp"
#include <iostream>

using namespace std;


ListaAdjacencia::ListaAdjacencia() {
    primeiro_vertice = nullptr;
    ultimo_vertice = nullptr;
    index_vertices = 0;    
}



void ListaAdjacencia::InserirAresta(int valor_vertice, int valor_aresta) {

  Vertice* tmp_vertice = primeiro_vertice;
  while(tmp_vertice->valor_vertice != valor_vertice && tmp_vertice->proximo_vertice != nullptr)
  {
    tmp_vertice = tmp_vertice->proximo_vertice;
  }

  if(tmp_vertice->valor_vertice != valor_vertice) return;

  Aresta* tmp_aresta = tmp_vertice->aresta;
  
  do 
  {
    if(tmp_aresta->valor_aresta == -1) {
      tmp_aresta->valor_aresta = valor_aresta;
      tmp_aresta->proximo_aresta = new Aresta{-1, nullptr}; 
      return;
    }

    tmp_aresta = tmp_aresta->proximo_aresta;
  } while (tmp_aresta != nullptr); 
  

}

void ListaAdjacencia::InserirVertice() {

  int num = index_vertices;
  index_vertices++;

  if(TamanhoVertices() == 0){
        Aresta* tmp_aresta = new Aresta{-1,nullptr};
        Vertice* tmp_vertice = new Vertice{num,tmp_aresta,nullptr};
        primeiro_vertice = tmp_vertice;
        ultimo_vertice = tmp_vertice;
  } else if (TamanhoVertices() == 1){
      Aresta* tmp_aresta = new Aresta{-1,nullptr};
      Vertice* tmp_vertice = new Vertice{num,tmp_aresta,nullptr};
      ultimo_vertice = tmp_vertice;
      primeiro_vertice->proximo_vertice = ultimo_vertice;

  } else {
    Aresta* tmp_aresta = new Aresta{-1,nullptr};
    Vertice* tmp_vertice = new Vertice{num,tmp_aresta,nullptr};

    ultimo_vertice->proximo_vertice = tmp_vertice;
    ultimo_vertice = tmp_vertice;
  }

}


bool ListaAdjacencia::Vazia() {
  return (primeiro_vertice == nullptr);

}

int ListaAdjacencia::TamanhoVertices() {
  if(Vazia())
        return 0;
  int tam = 0;
  
  Vertice* tmp_vertice = primeiro_vertice;
  do 
  {
    tmp_vertice = tmp_vertice->proximo_vertice;
    tam++;
  } while(tmp_vertice != nullptr);

  //cout << "pppasasdas " << tam << " sss";
  return tam;
}

int ListaAdjacencia::TamanhoAresta(int valor_vertice) {
  if(Vazia())
        return 0;

  int tam = 0;
  
  Vertice* tmp_vertice = primeiro_vertice;
  while(tmp_vertice->valor_vertice != valor_vertice && tmp_vertice->proximo_vertice != nullptr)
  {
    tmp_vertice = tmp_vertice->proximo_vertice;
  }

  if(tmp_vertice->valor_vertice != valor_vertice) return 0;

  Aresta* tmp_aresta = tmp_vertice->aresta;
  
  do 
  {
    if(tmp_aresta->valor_aresta == -1) {
      return tam;
    }
    tam++;
    tmp_aresta = tmp_aresta->proximo_aresta;
  } while (tmp_aresta != nullptr);
  
  return tam;

}

void ListaAdjacencia::ImprimirLista() {
  if(Vazia())
        return;

  Vertice* tmp_vertice = primeiro_vertice;
  do
  {
    cout << "Vertice " << tmp_vertice->valor_vertice << " ";
    Aresta* tmp_aresta = tmp_vertice->aresta;

    do 
    {
      if(tmp_aresta->valor_aresta == -1) {
        break;
      }
      cout << "A" << tmp_aresta->valor_aresta << " ";
      tmp_aresta = tmp_aresta->proximo_aresta;
    } while (tmp_aresta != nullptr);

    cout << endl;



    tmp_vertice = tmp_vertice->proximo_vertice;
  } while(tmp_vertice != nullptr);
  
  

}

void ListaAdjacencia::ImprimirVizinho(int valor_vertice) {
  if(Vazia())
        return;
  
  Vertice* tmp_vertice = primeiro_vertice;
  while(tmp_vertice->valor_vertice != valor_vertice && tmp_vertice->proximo_vertice != nullptr)
  {
    tmp_vertice = tmp_vertice->proximo_vertice;
  }

  if(tmp_vertice->valor_vertice != valor_vertice) return;
  do
  {
    //cout << "Vertice " << tmp_vertice->valor_vertice << " ";
    Aresta* tmp_aresta = tmp_vertice->aresta;

    do 
    {
      if(tmp_aresta->valor_aresta == -1) {
        break;
      }
      cout << tmp_aresta->valor_aresta << " ";
      tmp_aresta = tmp_aresta->proximo_aresta;
    } while (tmp_aresta != nullptr);

    cout << endl;



    tmp_vertice = tmp_vertice->proximo_vertice;
  } while(tmp_vertice != nullptr);
  
  

}


void ListaAdjacencia::Remover() {
  if(Vazia())
        return;
  
    Vertice* tmp_vertice = primeiro_vertice;
    Aresta* tmp_aresta = primeiro_vertice->aresta;
    Aresta* aux;
    do 
    {
    if(tmp_aresta->valor_aresta == -1) {
      delete tmp_aresta;
      break;
    }
    aux = tmp_aresta;
    tmp_aresta = tmp_aresta->proximo_aresta;
    delete aux;
    } while (tmp_aresta != nullptr);

    index_vertices--;
    primeiro_vertice = primeiro_vertice->proximo_vertice;
    delete tmp_vertice;


}

ListaAdjacencia::~ListaAdjacencia(){
  while(!Vazia()){
        Remover();
    }

}


/*** int main() {
  ListaAdjacencia grafo;

  grafo.InserirVertice(0);
  grafo.InserirVertice(1);
  grafo.InserirVertice(2);

  cout << grafo.primeiro_vertice->valor_vertice << endl;
  cout << grafo.primeiro_vertice->aresta->valor_aresta << endl;
  grafo.InserirAresta(0,5);
  grafo.InserirAresta(0,15);

  cout << grafo.primeiro_vertice->aresta->valor_aresta << endl;
  cout << grafo.primeiro_vertice->aresta->proximo_aresta->valor_aresta << endl;
  grafo.InserirAresta(2,8);
  grafo.InserirAresta(2,11);
  grafo.InserirAresta(2,35);
  cout << grafo.ultimo_vertice->aresta->valor_aresta << endl;
  cout << grafo.ultimo_vertice->aresta->proximo_aresta->valor_aresta << endl;

  cout << grafo.primeiro_vertice->proximo_vertice->aresta->valor_aresta << endl;

  grafo.InserirAresta(1,19);
  cout << grafo.primeiro_vertice->proximo_vertice->aresta->valor_aresta << endl;
  cout << grafo.primeiro_vertice->proximo_vertice->aresta->proximo_aresta->valor_aresta << endl;



  //cout << grafo.primeiro_vertice->proximo_vertice->valor_vertice << endl;
  //cout << grafo.ultimo_vertice->valor_vertice << endl;

  grafo->InserirAresta(0,1);
  grafo->InserirAresta(0,2);
  grafo->InserirAresta(1,2); 

  grafo.ImprimirLista();

  grafo.InserirVertice(4);

  cout << "TA:" << grafo.TamanhoVertices() << endl;
  cout << "T1:" << grafo.TamanhoAresta(0) << endl;
  cout << "T2:" << grafo.TamanhoAresta(1) << endl;
  cout << "T3:" << grafo.TamanhoAresta(2) << endl;
  cout << "T4:" << grafo.TamanhoAresta(4) << endl;

  grafo.ImprimirLista();

} ***/







