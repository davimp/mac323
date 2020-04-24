#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef LD_H
#define LD_H


/***************** Lista Desordenada **************************/
struct celulaDes
{
    std::string chave;
    int valor;
    struct celulaDes * prox;
};
typedef struct celulaDes CelulaDes;

template<class Chave, class Item>
class listaDes
{
    private:
    CelulaDes * ini;

    public:
    listaDes(std::string texto); /* construtor */
    ~listaDes();/* destrutor */

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);/*devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux = 0;
    ini = new CelulaDes;
    ini->chave = "";
    ini->valor = 0;
    arquivo.open(texto);

    if (arquivo.fail()) {
        std::cout << "ERRO: arquivo" << texto << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }
    while(arquivo >> str){
        aux = devolve(str);
        insere(str, aux+1);
    }

    arquivo.close();
}

template<class Chave, class Item>
listaDes<Chave, Item>::~listaDes()
{
    CelulaDes * aux;
    while(ini->prox != nullptr){
        aux = ini->prox;
        ini->prox = aux->prox;
        delete aux;
    }
    delete ini;
}

template <class Chave, class Item> 
void listaDes<Chave, Item>::insere(Chave chave, Item valor)
{
    CelulaDes * i;
    CelulaDes * aux;
    i = ini;
    while(i->prox != nullptr && i->chave != chave) 
        i = i->prox;

    if(i->chave == chave){
        i->valor = valor;
    }
    else{
        aux = new CelulaDes;
        aux->chave = chave;
        aux->valor = valor;
        i->prox = aux;
    }
}

template<class Chave, class Item>
Item listaDes<Chave, Item>::devolve(Chave chave)
{
    CelulaDes * i;
    for(i = ini->prox; i != nullptr; i = i->prox)
    {   
        if(i->chave == chave)
            break;
    }
    if(i == nullptr || i->chave != chave) return 0;
    else return i->valor;
}

template<class Chave, class Item>
void listaDes<Chave, Item>::remove(Chave chave)
{
    CelulaDes *i,  *p;
    p = ini;
    i = ini->prox;
    while(i->chave != chave && i->prox != nullptr){
        i = i->prox;
        p = p->prox;
    }
    if(i->chave == chave){
        p->prox = i->prox;
        delete i;
    }
}

template<class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave)
{
    CelulaDes *i;
    int ans;
    ans = 0;
    i = ini->prox;
    while(i != nullptr){
        if(i->chave < chave) ans++;
        i = i->prox;
    }
    return ans;
}

template<class Chave, class Item>
Chave listaDes<Chave, Item>::seleciona(int k)
{
    CelulaDes *i;
    i = ini->prox;
    while(i != nullptr){
        if(rank(i->chave) == k) break;
        i = i->prox;
    }
    return i->chave;
}


/*************************************************************************/


#endif