#include "../include/heap.hpp"
#include <iostream>

Heap::Heap(int maxsize) {
    this->tamanho = 0;
    this->data = new Aresta[maxsize];

};

Heap::~Heap() {
    delete[] data;
};

void Heap::Inserir(Aresta vertice) {

    data[tamanho] = vertice;
    int i = tamanho;
    int p = GetAncestral(i);

    while(data[i].custo < data[p].custo) {

        s_edge tmp;

        tmp = data[i];
        data[i] = data[p]; 
        data[p] = tmp;

        i = p;
        p = GetAncestral(i);
    }


    tamanho++;

};

Aresta Heap::Remover() {
    
    
    if(!Vazio()) {
        Aresta x = data[0];
        data[0] = data[tamanho-1];
        tamanho--;

        int i = 0;


        int esquerda = GetSucessorEsq(i);
        int direita = GetSucessorDir(i);

        int s = 0;

        if (esquerda < tamanho && direita < tamanho) {
            s = data[esquerda].custo < data[direita].custo ? esquerda : direita;
            // Resto do código de remoção
        } else if (esquerda < tamanho) {
            s = esquerda;
            // Resto do código de remoção
        } else {
            // Lida com o caso onde i não tem sucessores
             return x;
        }

        //int s = data[GetSucessorEsq(i)].custo < data[GetSucessorDir(i)].custo ? GetSucessorEsq(i) : GetSucessorDir(i);


        while(data[i].custo > data[s].custo && s < tamanho) {
                
                //std::cout << "Trocando os n " << i << " " << s << std::endl;
                Aresta tmp;

                tmp = data[i];
                data[i] = data[s]; 
                data[s] = tmp;

                i = s;
                //aq
                esquerda = GetSucessorEsq(i);
                direita = GetSucessorDir(i);

                if (esquerda < tamanho && direita < tamanho) {
                    s = data[esquerda].custo < data[direita].custo ? esquerda : direita;
                    // Resto do código de remoção
                } else if (esquerda < tamanho) {
                    s = esquerda;
                    // Resto do código de remoção
                } else {
                    // Lida com o caso onde i não tem sucessores
                    return x;
                }
        }


    
        return x;
    }

    Aresta x = data[0];
    return x;
    

};

//Retorna true caso o heap esteja vazio, false caso contrário.

bool Heap::Vazio() {
    return this->tamanho == 0;
};


int Heap::GetAncestral(int posicao) {

    return (posicao-1)/2;

};

int Heap::GetSucessorEsq(int posicao) {

    return 2 * posicao + 1;

};

int Heap::GetSucessorDir(int posicao) {

    return 2 * posicao + 2;

};
