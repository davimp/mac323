#include<iostream>
#include<string.h>
using namespace std;
#ifndef PQUEUE_H
#define PQUEUE_H

template<class Item>
class Priority_queue
{
    private:
        Item * pq;
        int n;
        int tam;
        void resize();
        void sieve(int i, int m);

    public:
        Priority_queue();
        ~Priority_queue();
        bool empty();
        int size();
        int front();
        void push(Item item);
        Item pop();
        void updateQueue();
};

template<class Item>
Priority_queue<Item>:: Priority_queue(): n(0), tam(10), pq(new Item[10]) {};

template<class Item>
Priority_queue<Item>:: ~Priority_queue()
{
    if(pq != NULL)
            delete [] pq;
}

template<class Item>
bool Priority_queue<Item>:: empty()
{
    return (n == 0);
}

template<class Item>
int Priority_queue<Item>:: size()
{
    return n;
}

template<class Item>
int Priority_queue<Item>:: front()
{
    if(n > 0)
    {
        return pq[1];
    }
}

template<class Item>
void Priority_queue<Item>:: push(Item item)
{
    int i;
    if(n >= tam) resize();
    n++;
    pq[n] = item;
    for(i = n; i > 0; i = i/2)
    {
        sieve(i, n);
    }
}

template<class Item>
Item Priority_queue<Item>::pop()
{
    Item x;
    x = pq[1];
    pq[1] = pq[n--];
    sieve(1, n);
    return x;
}

template<class Item>
void Priority_queue<Item>::resize()
{
    int i;
    Item * new_p;

    new_p = new Item[2*tam];

    for(i = 0; i < tam; i++)
        new_p[i] = pq[i];

    delete [] pq;
    pq = new_p;
}

template<class Item>
void Priority_queue<Item>::sieve(int i, int m)
{
    int f;
    Item x;
    f = 2*i;
    x = pq[i];
    while(f <= m)
    {
        if(f < m && pq[f] < pq[f+1]) f++;
        if(x >= pq[f]) break;
        pq[i] = pq[f];
        i = f; f = 2*i;
    }
    pq[i] = x;
}

template<class Item>
void Priority_queue<Item>::updateQueue()
{
    int i;
    for(i = n/2; i >= 1; i--)
        sieve(i, n);
}

#endif