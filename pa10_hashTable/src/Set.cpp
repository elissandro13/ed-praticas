#include "../include/Set.hpp"

StringSet::StringSet(int tamanho) {

    tabela = new ElementoTabela[tamanho];
    tamanhoTabela  = tamanho;
    tamanhoConjunto = 0;
    tamanhoOriginal = tamanho;

    for(int i  = 0 ; i < tamanho; i ++) {

        tabela[i].vazio = true;
        tabela[i].retirada = false;
        tabela[i].dado = "";

    }

};

StringSet::~StringSet() {

    delete [] tabela;
};

void StringSet::Inserir(string s) {

    //cout << "Elemento 1";

    if (tamanhoConjunto + 1 >= tamanhoTabela / 2) {
        
        Resize(2 * tamanhoTabela);
    }

    //cout << "Elemento 1";

    if(Pertence(s)) {/*cout << "Elemento já presente" */; return;}

    //cout << "Elemento 3";

    int pos = Hash(s);

    //cout << "Elemento 4";
    
    int i = 0;

    while ((i<tamanhoTabela) && !tabela[(pos+i)%tamanhoTabela].vazio && !tabela[(pos+i)%tamanhoTabela].retirada) {

        i++;
    }


    //if(i == tamanhoTabela) cout << "tabela cheia";

    
    tabela[(pos+i)%tamanhoTabela].dado = s;
    tabela[(pos+i)%tamanhoTabela].vazio = false;
    tabela[(pos+i)%tamanhoTabela].retirada = false;
    tamanhoConjunto++;


    //cout << "Elemento in";


};

void StringSet::Remover(string s) {

    int pos = Hash(s);
    int i = 0;

    while ((i<tamanhoTabela) && !tabela[(pos+i)%tamanhoTabela].vazio && !tabela[(pos+i)%tamanhoTabela].dado.compare(s) == 0) {

        i++;
    }

    if (tabela[(pos+i)%tamanhoTabela].dado.compare(s) == 0 && !tabela[(pos+i)%tamanhoTabela].retirada) {

        tabela[(pos+i)%tamanhoTabela].retirada = true;
        tamanhoConjunto--;

    }
    
    


};

bool StringSet::Pertence(string s) {
    
    int pos = Hash(s);
     
    int i = 0;

    while ((i<tamanhoTabela) && !tabela[(pos+i)%tamanhoTabela].vazio && !tabela[(pos+i)%tamanhoTabela].dado.compare(s) == 0) {

        i++;
    }

    if(tabela[(pos+i)%tamanhoTabela].dado.compare(s) == 0 && !tabela[(pos+i)%tamanhoTabela].retirada) {
        return true;
    }

    return false;
    

};

StringSet* StringSet::Intersecao(StringSet* S) {

    StringSet *novoConjunto = new StringSet(tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; ++i) {

        if (!tabela[i].vazio && !tabela[i].retirada && S->Pertence(tabela[i].dado)) {
            novoConjunto->Inserir(tabela[i].dado);
        }
    }

    return novoConjunto;



};

StringSet* StringSet::Uniao(StringSet* S) {

    StringSet *novoConjunto = new StringSet(tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; ++i) {

        if (!tabela[i].vazio && !tabela[i].retirada) {
            novoConjunto->Inserir(tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; ++i) {

        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            novoConjunto->Inserir(S->tabela[i].dado);
        }
    }

     return novoConjunto;


};

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {

    StringSet *conjuntoIntersecao = Intersecao(S);

    StringSet *novoConjunto = Uniao(S);


    for (int i = 0; i < conjuntoIntersecao->tamanhoTabela; ++i) {

        if (!tabela[i].vazio && !tabela[i].retirada) {
            novoConjunto->Remover(conjuntoIntersecao->tabela[i].dado);
        }
    }

      return novoConjunto;



};

void StringSet::Imprimir() {
    cout << "{ ";
    
    for (int i = 0; i < tamanhoTabela; ++i) {


        if(i > 0 && !tabela[i].vazio && !tabela[i].retirada) {
            std::cout << " ";
        }
        if (!tabela[i].vazio && !tabela[i].retirada) {
            std::cout << tabela[i].dado;
        }
        if(i < tamanhoConjunto - 1 && !tabela[i].vazio && !tabela[i].retirada) {
            std::cout << ",";
        }
        
    }
    cout << " }";
    std::cout << std::endl;

};

void StringSet::ImprimirInverso() {
    cout << "{ ";
    
    for (int i = tamanhoTabela - 1; i >= 0; --i) {


        if(i < tamanhoTabela - 1 && !tabela[i].vazio && !tabela[i].retirada) {
            std::cout << " ";
        }
        if (!tabela[i].vazio && !tabela[i].retirada) {
            std::cout << tabela[i].dado;
        }
        if(i > 0 && !tabela[i].vazio && !tabela[i].retirada) {
            std::cout << ",";
        }
        
    }
    cout << " }";
    std::cout << std::endl;

};

int StringSet::Hash(string s) {

    int hash = 0;
    for (char c : s) {
        hash = (hash * 31 + c) % tamanhoTabela;
    }
    return hash;


};

void StringSet::Rehash(int pos) {
    if (tabela[pos].vazio || tabela[pos].retirada) {
        return;
    }

    int newPos = Hash(tabela[pos].dado);

    while (!tabela[newPos].vazio) {
        newPos = (newPos + 1) % tamanhoTabela;
    }

    tabela[newPos] = tabela[pos];

};

void StringSet::Resize(int tamanho) {

    StringSet *novoConjunto = new StringSet(tamanho);

    int newPos = 0;

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            newPos = Hash(tabela[i].dado);

            while (!novoConjunto->tabela[newPos].vazio) {
                newPos = (newPos + 1) % tamanho;
            }            

            novoConjunto->tabela[newPos] = tabela[i];
        }

        
    }

    delete[] this->tabela;
    this->tabela = novoConjunto->tabela;
    this->tamanhoTabela = tamanho;

};


