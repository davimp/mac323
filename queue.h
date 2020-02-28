#include "plane.h"
#ifndef QUEUE_H
#define QUEUE_H

const int TAM = 1000;

class Queue
{
    private:
        Plane * q;
        int ini;
        int n;

    public:
        Queue();
        ~Queue();
        void push(Plane plane);
        Plane pop();
        bool empty();
        int size();
        Plane front();
        Plane back();
        /* outras funcoes que nao sao proprias da estrutura de dados fila*/

        void updateQueue();

};

Queue::Queue(): ini(0), n(0), q(new Plane[TAM]) {};

Queue::~Queue()
{
    if(q != NULL)
        delete [] q;
}

Plane Queue::pop()
{
    if(n > 0)
    {
        Plane aux;
        aux = q[ini];
        n--;
        ini++; ini %= TAM;
        return aux;
    }
}

bool Queue::empty()
{
    return (n == 0);
}

int Queue::size()
{
    return n;
}

Plane Queue::back()
{
    if(n > 0)
        return q[(ini + n - 1)%TAM];
}

Plane Queue::front()
{
    if(n > 0)
        return q[ini];
}

void Queue::push(Plane plane)
{
    q[(ini + n)%TAM] = plane;
    n++;
}


/* funcoes auxiliares*/

void Queue::updateQueue()
{
    Plane aux;
    int i, j, k;
    j = ini;
    for(i = j+3; i >= j; i--)
    {
          
    }

}

#endif