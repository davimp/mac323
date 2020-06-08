#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef VO_H
#define VO_H

/*********************** Vetor Ordenado **************************/
struct parOrd
{
    std::string first;
    int second;
};
typedef struct parOrd ParOrd;

template<class Chave, class Item>
class vetorOrd
{
    private:
    ParOrd * v;
    int n;
    int tam;
    void resize(int tam);

    public:
    vetorOrd(std::string texto); /* construtor */
    ~vetorOrd();/* destrutor */

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);/*devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* ParOrda Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux, i;
    v = new ParOrd[100];
    tam  = 100;
    n = 0;
    arquivo.open(texto);

    if (arquivo.fail()) {
        std::cout << "ERRO: arquivo" << texto << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }
    while(arquivo >> str){
        aux = devolve(str);
        insere(str, aux+1);
    }
    for(i = 0; i < n; i++){
        std:: cout << v[i].first << " ";
    }
    std::cout << "\n";
    arquivo.close();
}

template<class Chave, class Item>
vetorOrd<Chave, Item>::~vetorOrd()
{
    if(v != nullptr)
        delete [] v;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize(int t)
{
  ParOrd * novoV = new ParOrd[t];
  for(int i = 0; i < n; i++)
    novoV[i] = v[i];
  delete [] v;
  v = novoV;
  tam = t;
}

template<class Chave, class Item> 
void vetorOrd<Chave, Item>::insere(Chave chave, Item valor)
{
    ParOrd aux;
    std::string troca1;
    int troca2;
    int i;
    int l, r, m;
    if(n == 0){
        /* insere o primeiro elemento */
        v[0].first = chave;
        v[0].second = valor;
        n++;
        return;
    }
    if(n+2 >= tam) resize(2*tam);
    l = 0; r = n;
    m = (l+r)/2;
    while(l < r){
        m = (l+r)/2;
        if(chave <= v[m].first){
            r = m;
            if(v[m].first == chave){
                v[m].second = valor;
                return;
            }
        }
        else{
            l = m+1;
        }
    }
    aux.first = v[r].first;
    aux.second = v[r].second;
    v[r].first = chave;
    v[r].second = valor;

    for(i = r+1; i <= n; i++){
        troca1 = aux.first;
        aux.first = v[i].first;
        v[i].first = troca1;
    
        troca2 = aux.second;
        aux.second = v[i].second;
        v[i].second = troca2;
    }
    n++;
}

template<class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave)
{
    int l, r, m;
    l = 0; r = n;
    m = (l+r)/2;
    while(l < r){
        m = (l+r)/2;
        if(chave <= v[m].first){
            if(v[m].first == chave){
                return v[m].second;
            }
            r = m;
        }
        else{
            l = m+1;
        }
    }
    return 0;
}

template<class Chave, class Item>
void vetorOrd<Chave, Item>::remove(Chave chave)
{
    int i;
    std::string troca1;
    int troca2;
    int l, r, m;
    l = 0; r = n-1;
    m = (l+r)/2;
    while(l < r){
        m = (l+r)/2;
        if(chave <= v[m].first){
            r = m;
        }
        else{
            l = m+1;
        }
    }
    for(i = r; i < n-1; i++){
        troca1 = v[i].first;
        v[i].first = v[i+1].first;
        v[i+1].first = troca1;

        troca2 = v[i].second;
        v[i].second = v[i+1].second;
        v[i+1].second = troca2;
    }
    n--;
}

template<class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave)
{
    int l, r, m;
    l = 0; r = n-1;
    while(l < r){
        m = (l+r)/2;
        if(chave <= v[m].first){
            r = m;
        }
        else{
            l = m+1;
        }
    }
    return m;
}

template<class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k)
{
    if(k < n) return v[k].first; 
    else return "";
}
/*************************************************************************/

#endif