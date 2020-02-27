#include<iostream>
#include<string.h>
#ifndef QUEUE_H
#define QUEUE_H


template<class Item>
class Queue
{
    private:
        /*Item * q;*/
        int n;
        int tam;
        void resize();

    public:
        Item * q;
        Queue();
        ~Queue();
        void push(Item item);
        Item pop();
        bool empty();
        int size();
        Item front();
        Item back();
};

template<class Item>
Queue<Item>::Queue(): n(0), tam(10), q(new Item[10]) {};

template<class Item>
Queue<Item>::~Queue()
{
    if(q != NULL)
        delete [] q;
}

template<class Item>
Item Queue<Item>::pop()
{
    if(n > 0)
    {
        Item aux;
        aux = q[n-1];
        n--;
        return aux;
    }
}

template<class Item>
bool Queue<Item>::empty()
{
    return (n == 0);
}

template<class Item>
int Queue<Item>::size()
{
    return n;
}

template<class Item>
Item Queue<Item>::back()
{
    if(n > 0)
        return q[0];
}

template<class Item>
Item Queue<Item>::front()
{
    if(n > 0)
        return q[n-1];
}

template<class Item>
void Queue<Item>::resize()
{
    Item * novoVetor = new Item[2*tam];
    for (int i = 0; i < n; i++)
        novoVetor[i] = q[i];
    delete[] q;
    q = novoVetor; 
    tam = tam * 2;
}

template<class Item>
void Queue<Item>::push(Item item)
{
    if(n > tam) resize();

    for(int i = n; i >= 1; i--)
        q[i] = q[i-1];
    n++;

    q[0] = item;
}

#endif