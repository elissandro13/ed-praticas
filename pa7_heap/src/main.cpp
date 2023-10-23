#include "../include/heap.hpp"
#include <iostream>

int main() {

    int n;
    int x;

    std::cin >> n;

    Heap heap(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        heap.Inserir(x);
    }

    //heap.ImprimirHeap();

    for (int i = 0; i < n; i++)
    {
        std::cout << heap.Remover();
    
        if(i != n-1) {
           std::cout << " ";
        }

       // heap.ImprimirHeap();
        
    }
    std::cout << std::endl;
    
    return 0;
}