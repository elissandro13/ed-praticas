#include "../include/unionFind.hpp"
#include "../include/heap.hpp"



UnionFind::UnionFind(int quantidade_subconjuntos) {

    this->subconjuntos = new Subconjunto[quantidade_subconjuntos];
    this->tamanho = quantidade_subconjuntos;

    for (int i = 0; i < quantidade_subconjuntos; i++)
    {
        Make(i);
    }
    
};

UnionFind::~UnionFind() {

    delete[] subconjuntos;

};

void UnionFind::Make(int x) {

    if (x >= tamanho) {
        // Verifica se x está dentro dos limites válidos
        return;
    }
    
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0; // Pode ser definido como 0
    


};

int UnionFind::Find(int x) {
    
    if (x < 0 || x >= tamanho) {
        // Verifica se x está dentro dos limites válidos
        return -1; // Indica um valor inválido ou erro
    }

    if (subconjuntos[x].representante != x) {
        // Se x não é o representante do seu conjunto, encontre o verdadeiro representante recursivamente
        subconjuntos[x].representante = Find(subconjuntos[x].representante);
    }
    
    return subconjuntos[x].representante;

};

void UnionFind::Union(int x, int y) {

    int representanteX = Find(x);
    int representanteY = Find(y);

    if (representanteX == representanteY) {
        return; // Já estão no mesmo conjunto
    }

    if (subconjuntos[representanteX].rank < subconjuntos[representanteY].rank) {
        subconjuntos[representanteX].representante = representanteY;
    } else if (subconjuntos[representanteX].rank > subconjuntos[representanteY].rank) {
        subconjuntos[representanteY].representante = representanteX;
    } else {
        subconjuntos[representanteY].representante = representanteX;
        subconjuntos[representanteX].rank++;
    }
                
};
