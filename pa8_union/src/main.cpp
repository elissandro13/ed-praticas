#include  "../include/unionFind.hpp"
#include "../include/heap.hpp"
#include <iostream>





int main () {

    int n, m, u, v, c, custo, cont_uni;

    custo = cont_uni = 0;

    


    std::cin >> n >> m;

    UnionFind grafo(n);
    Heap arestas(m);


    for (int i = 0; i < m; i++)
    {
         std::cin >> u >> v >> c;
         s_edge edge = {u,v,c};
         arestas.Inserir(edge);

    }



    while (!arestas.Vazio() && cont_uni < n-1)
    {
        s_edge tmp_aresta = arestas.Remover();
        std::cout << "Analissando arestas " << tmp_aresta.u << " e " << tmp_aresta.v << " Custo " << tmp_aresta.custo << " Pai " << grafo.Find(tmp_aresta.u) << " Pai " << grafo.Find(tmp_aresta.v) << std::endl;
        if(grafo.Find(tmp_aresta.u) != grafo.Find(tmp_aresta.v)) {
            grafo.Union(tmp_aresta.u, tmp_aresta.v);
            cont_uni++;
            custo += tmp_aresta.custo;
            std::cout << "Novo custo " << custo << std::endl;
            
        }
    }
    

    std::cout << custo << std::endl;
    

    return 0;
}