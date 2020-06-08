#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef ABB_H
#define ABB_H

/***************** Arvore binaria de busca **************************/
struct nodeBin
{
    std::string chave;
    int valor;
    struct nodeBin * esq;
    struct nodeBin * dir;
};
typedef struct nodeBin NodeBin;

template<class Chave, class Item>
class arvoreBin
{
    private:
    NodeBin * ini;

    public:
    arvoreBin(std::string texto); /* construtor */
    ~arvoreBin(); /* destrutor */

    int quantosNos(NodeBin * arvore); /* funcao auxiliar pra contar quantos nos a arvore tem */
    void apaga(NodeBin *q);

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave); /* devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
arvoreBin<Chave, Item>::arvoreBin(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux = 0;
    ini = nullptr;

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
arvoreBin<Chave, Item>::~arvoreBin()
{
    apaga(ini);
}

template <class Chave, class Item> 
void arvoreBin<Chave, Item>::apaga(NodeBin *q)
{
    if(q == nullptr) return;
    apaga(q->dir);
    apaga(q->esq);
    delete q;
}

template <class Chave, class Item> 
void arvoreBin<Chave, Item>::insere(Chave chave, Item valor)
{
    NodeBin * no;
    NodeBin * i;
    NodeBin * aux;
    aux = nullptr;
    i = ini;
    while(i != nullptr){
        aux = i;
        if(i->chave > chave){
            i = i->esq;
        }
        else if(i->chave < chave){
            i = i->dir;
        }
        else{
            i->valor = valor;
            return;
        }
    }

    no = new NodeBin;
    no->chave = chave;
    no->valor = valor;
    no->esq = nullptr;
    no->dir = nullptr;

    if(aux == nullptr){
        ini = no;
        return;
    }
    else{
        if(chave > aux->chave){
            aux->dir = no;
        }
        else{
            aux->esq = no;
        }
    }

}

template<class Chave, class Item>
Item arvoreBin<Chave, Item>::devolve(Chave chave)
{
    NodeBin * i;
    i = ini;
    while(i != nullptr){
        if(i->chave == chave){
            return i->valor;
        }
        else if(i->chave < chave){
            i = i->dir;
        }
        else{
            i = i->esq;
        }
    }
    return 0;
}

template<class Chave, class Item>
void arvoreBin<Chave, Item>::remove(Chave chave)
{
    NodeBin *i, *p, *f;
    p = nullptr;
    i = ini;

    while(i != nullptr){
        if(i->chave == chave) break;
        p = i;
        if(chave < i->chave){
            i = i->esq;
        }
        else{
            i = i->dir;
        }
    }

    if(i == nullptr) return;

    f = i->dir;
    if(f == nullptr){
        if(p->esq == i){
            p->esq = i->esq;
        }
        else{
            p->dir = i->esq;
        }
        delete i;
    }
    else{
        p = i;
        while(f->esq != nullptr){
            p = f; 
            f = f->esq;
        }
        i->chave = f->chave;
        i->valor = f->valor;

        /* remove f */
        if(p->esq == f){
            p->esq = f->dir;
        }
        else{
            p->dir = f->dir;
        }
        delete f;
    }
}

template<class Chave, class Item>
int arvoreBin<Chave, Item>::rank(Chave chave)
{
    int r;
    NodeBin *i;
    r = 0;
    i = ini;
    while(i != nullptr && i->chave != chave){
        if(i->chave < chave){
            r += quantosNos(i->esq) + 1;
            i = i->dir;
        }
        else {
            i = i->esq;
        }
    }
    if(i == nullptr) return r;
    return r += quantosNos(i->esq);
}

template<class Chave, class Item>
Chave arvoreBin<Chave, Item>::seleciona(int k)
{
    NodeBin *i;
    int aux;
    i = ini;
    while(i != nullptr){
        aux = rank(i->chave);
        if(aux > k){
            i = i->esq;
        }
        else if(aux <  k){
            i = i->dir;
        }
        else{
            break;
        }
    }
    return i->chave;
}

template<class Chave, class Item>
int arvoreBin<Chave, Item>::quantosNos(NodeBin * arvore)
{
    if(arvore == nullptr) return 0;
    return 1 + quantosNos(arvore->dir) + quantosNos(arvore->esq);
}


/*************************************************************************/


#endif