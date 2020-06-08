#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef HT_H
#define HT_H
const int MAX = 524287;

/********************  Hash Table **************************/
struct cel
{
    std::string chave;
    int valor;
    struct cel * prox;
};
typedef struct cel Cel;

template<class Chave, class Item>
class hashTable
{
    private:
    Cel ** v;

    public:
    hashTable(std::string texto); /* construtor */
    ~hashTable();/* destrutor */

    int hash(Chave x);/*formula de hashing*/

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);/*devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
hashTable<Chave, Item>::hashTable(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux, i;

    v = new Cel*[MAX];

    for(i = 0; i < MAX; i++)
        v[i] = nullptr;

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
hashTable<Chave, Item>::~hashTable()
{
    Cel *p, *q;
    int i;
    for(i = 0; i < MAX; i++){
        if(v[i] != nullptr){
            p = v[i];
            while(p->prox != nullptr){
                q = p->prox;
                p->prox = q->prox;
                delete q;
            }
            delete p;
        }
    }
    delete [] v;
}

template <class Chave, class Item>
int hashTable<Chave, Item>::hash(Chave x)
{
    int ans, p, i;
    p = 256;
    ans = 0;
    for(i = 0; x[i] != '\0'; i++)
    {
        ans = (ans*p + x[i])%MAX;
        if(ans < 0) ans += MAX;
    }
    
    return ans;
}


template <class Chave, class Item> 
void hashTable<Chave, Item>::insere(Chave chave, Item valor)
{
    Cel *i, *q;
    int h;
    h = hash(chave);
    i = v[h];

    if(i == nullptr){
        q = new Cel;
        q->chave = chave;
        q->valor = valor;
        q->prox = nullptr;
        v[h] = q;
        return;
    }

    while(i->prox != nullptr){
        if(i->chave == chave){
            i->valor = valor;
            return;
        }
        i = i->prox;
    }
    if(i != nullptr && i->chave == chave){
        i->valor = valor;
        return;
    }

    q = new Cel;
    q->chave = chave;
    q->valor = valor;
    q->prox = nullptr;
    i->prox = q;
}

template<class Chave, class Item>
Item hashTable<Chave, Item>::devolve(Chave chave)
{
    Cel *i;
    int h;
    h = hash(chave);
    i = v[h];
    while(i != nullptr && i->chave != chave){
        i = i->prox;
    }

    if(i == nullptr) return 0;
    else return i->valor;
}

template<class Chave, class Item>
void hashTable<Chave, Item>::remove(Chave chave)
{
    Cel *i, *p;
    int h;
    h = hash(chave);
    i = v[h];
    
    if(i == nullptr) return;

    if(i->chave == chave){
        v[h] = i->prox;
        delete i;
    }
    else{
        p = i;
        i = i->prox;
        while(i != nullptr && i->chave != chave){
            p = i;
            i = i->prox;
        }
        if(i == nullptr) return;
        p->prox = i->prox;
        delete i;
    }
}

template<class Chave, class Item>
int hashTable<Chave, Item>::rank(Chave chave)
{
    Cel *i;
    int k, cnt;
    cnt = 0;
    for(k = 0; k < MAX; k++){
        i = v[k];
        while(i != nullptr){
            if(i->chave < chave) cnt++;
            i = i->prox;
        }
    }
    return cnt;
}

template<class Chave, class Item>
Chave hashTable<Chave, Item>::seleciona(int k)
{
    Cel *i;
    int j;
    for(j = 0; j < MAX; j++){
        if(v[j] == nullptr) continue;
        i = v[j];
        while(i != nullptr){
            if(rank(i->chave) == k){
                return i->chave;
            }
            i = i->prox;
        }
    }
    return "";
}


/*************************************************************************/


#endif