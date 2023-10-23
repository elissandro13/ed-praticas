#include "../include/heap.hpp"
#include <iostream>

Heap::Heap(int maxsize) {
    this->tamanho = 0;
    this->data = new int[maxsize];

};

Heap::~Heap() {
    delete[] data;
};

void Heap::Inserir(int x) {

    data[tamanho] = x;
    int i = tamanho;
    int p = GetAncestral(i);

    while(data[i] < data[p]) {

        int tmp = 0;

        tmp = data[i];
        data[i] = data[p]; 
        data[p] = tmp;

        i = p;
        p = GetAncestral(i);
    }


    tamanho++;

};

int Heap::Remover() {
    
    
    if(!Vazio()) {
        int x = data[0];
        data[0] = data[tamanho-1];
        tamanho--;

        int i = 0;
        int s = data[GetSucessorEsq(i)] < data[GetSucessorDir(i)] ? GetSucessorEsq(i) : GetSucessorDir(i);


        while(data[i] > data[s] && s <= tamanho) {
                
                //std::cout << "Trocando os n " << i << " " << s << std::endl;
                int tmp = 0;

                tmp = data[i];
                data[i] = data[s]; 
                data[s] = tmp;

                i = s;
                s = data[GetSucessorEsq(i)] < data[GetSucessorDir(i)] ? GetSucessorEsq(i) : GetSucessorDir(i);
        }


    
        return x;
    }


    return 0;
    

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
