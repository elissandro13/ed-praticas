#include "../include/graph.hpp"
#include <iostream>

using namespace std;

/*** -d 
quantidade de vertices
quantidade arrestas
grau minimo
grau máximo


-n todos vizinho dos vértizes

-k retornar 1 para grafo complerto e 0 para a negativa

Entrada
N (número de vertices)
M número de (arestas) Ki até Km as conexões das arestas

***/


int main(int argc,char ** argv) {

    int n;
    int m;
    int u;

    cin >> n;

    if(n == 0)
        return 0;

    Grafo g;

    if(n == 1) {
        g.InsereVertice();
    } else {
        for(int i = 0; i < n; i++) {
        g.InsereVertice();
        cin >> m;
        for (int j = 0; j < m; j++)
        {
            cin >> u;
            g.InsereAresta(i,u);
        }
        
        }

    }

    
    //g.ImprimeVizinhos(0);

    char op = argv[1][1];
    int qtq_v = g.QuantidadeVertices();
    int qtd_a = g.QuantidadeArestas()/2;
    int x = (qtq_v * (qtq_v-1))/2;

    switch (op)
    {
    case 'k':
       
        if(x == qtd_a) {
            cout << "1" << endl;
        }
        cout << "0" << endl;
        break;

    case 'n':
        g.ImprimeVizinhos(0);
        
        
        break;

    case 'd':
        cout << g.QuantidadeVertices() << endl;
        cout << g.QuantidadeArestas()/2 << endl;
        cout << g.GrauMinimo() << endl;
        cout << g.GrauMaximo() << endl;
        break;
    
    default:
        break;
    }



    return 0;
}