#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef LO_H
#define LO_H


/***************** Lista Ordenada **************************/
struct celulaOrd
{
    std::string chave;
    int valor;
    struct celulaOrd * prox;
};
typedef struct celulaOrd CelulaOrd;

template<class Chave, class Item>
class listaOrd
{
    private:
    CelulaOrd * ini;
    int n;

    public:
    listaOrd(std::string texto); /* construtor */
    ~listaOrd();/* destrutor */

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);/*devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
listaOrd<Chave, Item>::listaOrd(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux = 0;
    ini = new CelulaOrd;
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
listaOrd<Chave, Item>::~listaOrd()
{
    CelulaOrd * aux;
    aux = ini->prox;
    while(ini->prox != nullptr){
        aux = ini->prox;
        ini->prox = aux->prox;
        delete aux;
    }
    delete ini;
}

template <class Chave, class Item> 
void listaOrd<Chave, Item>::insere(Chave chave, Item valor)
{
    CelulaOrd *i, * q;
    i = ini;
    q = ini;
    while(i->prox != nullptr && i->prox->chave <= chave){
        i = i->prox;
    }

    if(i->chave == chave){
        i->valor = valor;
    }
    else{
       q = new CelulaOrd;
       q->chave = chave;
       q->valor = valor;
       q->prox = i->prox;
       i->prox = q;
    }
}

template<class Chave, class Item>
Item listaOrd<Chave, Item>::devolve(Chave chave)
{
    CelulaOrd * i;
    for(i = ini->prox; i != nullptr; i = i->prox)
    {   
        if(i->chave >= chave)
            break;
    }
    if(i == nullptr || i->chave != chave) return 0;
    else return i->valor;
}

template<class Chave, class Item>
void listaOrd<Chave, Item>::remove(Chave chave)
{
    CelulaOrd *i,  *p;
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
int listaOrd<Chave, Item>::rank(Chave chave)
{
    CelulaOrd *i;
    int ans;
    ans = 0;
    i = ini->prox;
    while(i != nullptr){
        if(i->chave < chave) ans++;
        else break;
        i = i->prox;
    }
    return ans;
}

template<class Chave, class Item>
Chave listaOrd<Chave, Item>::seleciona(int k)
{
    CelulaOrd *i;
    int r;
    r = 0;
    i = ini->prox;

    while(i != nullptr){
        if(r == k) break;
        i = i->prox;
        r++;
    }

    if(i != nullptr) return i->chave;
    return "";
}


/*************************************************************************/


#endif