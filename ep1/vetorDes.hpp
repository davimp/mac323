#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef VD_H
#define VD_H

/******************** Vetor Desordenado **************************/
struct par
{
    std::string first;
    int second;
};
typedef struct par Par;

template<class Chave, class Item>
class vetorDes
{
    private:
    Par * v;
    int n;
    int tam;
    void resize(int tam);

    public:
    vetorDes(std::string texto); /* construtor */
    ~vetorDes();/* destrutor */

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);/*devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
vetorDes<Chave, Item>::vetorDes(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux;
    v = new Par[100];
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

    arquivo.close();
}

template<class Chave, class Item>
vetorDes<Chave, Item>::~vetorDes()
{
    if(v != nullptr)
        delete [] v;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::resize(int t)
{
  Par * novoV = new Par[t];
  for(int i = 0; i < n; i++)
    novoV[i] = v[i];
  delete [] v;
  v = novoV;
  tam = t;
}

template <class Chave, class Item> 
void vetorDes<Chave, Item>::insere(Chave chave, Item valor)
{
    int i;
    if(n == tam)
        resize(2*tam);

    for(i = 0; i < n; i++){
        if(v[i].first == chave) break;
    }
    v[i].first = chave;
    v[i].second = valor;
    if(i == n) n++;
}

template<class Chave, class Item>
Item vetorDes<Chave, Item>::devolve(Chave chave)
{
    int i;
    for(i = 0; i < n; i++)
        if(v[i].first == chave) break;
    
    if(i == n) return 0;
    else return v[i].second;
}

template<class Chave, class Item>
void vetorDes<Chave, Item>::remove(Chave chave)
{
    int i, j;
    std::string aux;
    for(i = 0; i < n-1; i++){
        if(v[i].first == chave){
            /*swap(v[i].first, v[i+1].first);*/
            aux = v[i].first;
            v[i].first = v[i+1].first;
            v[i+1].first = aux;

            /*swap(v[i].second, v[i+1].second);*/
            j = v[i].second;
            v[i].second = v[i+1].second;
            v[i+1].second = j;
        }
    }
    n--;
}

template<class Chave, class Item>
int vetorDes<Chave, Item>::rank(Chave chave)
{
    int i, k;
    k = 0;
    for(i = 0; i < n; i++){
        if(v[i].first < chave) k++;
    }
    return k;
}

template<class Chave, class Item>
Chave vetorDes<Chave, Item>::seleciona(int k)
{
    int i;
    for(i = 0; i < n; i++){
        if(rank(v[i].first) == k) break;
    }

    return v[i].first;
}


/*************************************************************************/


#endif