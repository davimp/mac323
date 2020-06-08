#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef T_H
#define T_H

/***************** Treap **************************/
struct node
{
    std::string chave;
    int valor;
    int prioridade;
    struct node * esq;
    struct node * dir;
    struct node * pai;
};
typedef struct node Node;

template<class Chave, class Item>
class treap
{
    private:
    Node * ini;

    public:
    treap(std::string texto); /* construtor */
    ~treap(); /* destrutor */

    int quantosNos(Node * arvore); /* funcao auxiliar pra contar quantos nos a arvore tem */
    void rotacionaEsq(Node * q);
    void rotacionaDir(Node * q);
    void apaga(Node *q);

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave); /* devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
treap<Chave, Item>::treap(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux = 0;
    ini = new Node;
    ini->chave = "";
    ini->valor = 0;
    ini->pai = nullptr;
    ini->dir = nullptr;
    ini->esq = nullptr;
    ini->prioridade = INT32_MAX;
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
treap<Chave, Item>::~treap()
{
    apaga(ini);
}

template<class Chave, class Item>
void treap<Chave, Item>::apaga(Node *q)
{
    if(q == nullptr) return;
    apaga(q->esq);
    apaga(q->dir);
    delete q;
}

template<class Chave, class Item>
void treap<Chave, Item>::rotacionaDir(Node *q)
{
    Node *p = q->pai;
    Node *avo;
    avo = p->pai;

    p->esq = q->dir;
    if(q->dir != nullptr) q->dir->pai = p;
    q->dir = p;
    p->pai = q;
    q->pai = avo;

    if(q->pai == nullptr) ini = q;
    else{
        q->pai = avo;
        if(avo->esq == p){
            avo->esq = q;
        }
        else{
            avo->dir = q;
        }
    }
}

template<class Chave, class Item>
void treap<Chave, Item>::rotacionaEsq(Node *q)
{
    Node *p = q->pai;
    Node *avo;
    avo = p->pai;

    p->dir = q->esq;
    if(q->esq != nullptr) q->esq->pai = p;
    q->esq = p;
    p->pai = q;
    q->pai = avo;

    if(q->pai == nullptr) ini = q;
    else{
        q->pai = avo;
        if(avo->esq == p){
            avo->esq = q;
        }
        else{
            avo->dir = q;
        }
    }
}



template <class Chave, class Item> 
void treap<Chave, Item>::insere(Chave chave, Item valor)
{
    Node * no;
    Node * i;
    Node * aux;
    aux = ini;
    i = ini->dir;
    while(i != nullptr){
        if(i->chave > chave){
            aux = i;
            i = i->esq;
        }
        else if(i->chave < chave){
            aux = i;
            i = i->dir;
        }
        else{
            i->valor = valor;
            return;
        }
    }

    /* precisa inserir um nó novo*/
    if(i == nullptr){
        no = new Node;
        no->chave = chave;
        no->valor = valor;
        no->esq = nullptr;
        no->dir = nullptr;
        no->pai = aux;
        no->prioridade = random();
        if(aux->chave > chave){
            aux->esq = no;
        }
        else{
            aux->dir = no;
        }
        while(aux->prioridade < no->prioridade){
            if(aux->esq == no) rotacionaDir(no);
            else rotacionaEsq(no);
            aux = no->pai;
            /*std::cout << "debug: " << no->chave << " " << no->prioridade << " pai: " << aux->chave << " " << aux->prioridade << "\n";*/
        }
    }
}

template<class Chave, class Item>
Item treap<Chave, Item>::devolve(Chave chave)
{
    Node * i;
    i = ini;
    i = i->dir;
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
void treap<Chave, Item>::remove(Chave chave)
{
    Node *i, *p, *q;
    i = ini->dir;
    
    while(i != nullptr){
        if(i->chave == chave){
            break;
        }
        else if(i->chave < chave){
            i = i->dir;
        }
        else{
            i = i->esq;
        }
    }

    if(i == nullptr) return;

    q = i->dir;
    if(q == nullptr){
        /* i já é uma "folha" */
        p = i->pai;
        if(p->esq == i){
            p->esq = i->dir;
            if(i->dir != nullptr) i->dir->pai = p;
        }
        else{
            p->dir = i->dir;
            if(i->dir != nullptr) i->dir->pai = p;
        }
        delete i;
        i = nullptr;
    }
    else{
        while(q->esq != nullptr){
            q = q->esq;
        }
        i->chave = q->chave;
        i->valor = q->valor;

        p = q->pai;
        if(p->esq == q){
            p->esq = q->dir;
            if(q->dir != nullptr) q->dir->pai = p;
        }
        else{
            p->dir = q->dir;
            if(q->dir != nullptr) q->dir->pai = p;
        }
        delete q;
        q = nullptr;
    }
}

template<class Chave, class Item>
int treap<Chave, Item>::rank(Chave chave)
{
    int r;
    Node *i;
    r = 0;
    i = ini->dir;
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
Chave treap<Chave, Item>::seleciona(int k)
{
    Node *i;
    int aux;
    i = ini->dir;
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
    if(i!= nullptr) return i->chave;
    else return "";
}

template<class Chave, class Item>
int treap<Chave, Item>::quantosNos(Node * arvore)
{
    if(arvore == nullptr) return 0;
    return 1 + quantosNos(arvore->dir) + quantosNos(arvore->esq);
}

/*************************************************************************/


#endif