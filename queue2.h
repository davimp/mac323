#include "plane.h"
#ifndef QUEUE_H
#define QUEUE_H

const int TAM = 1000;

typedef struct node Node;
struct node
{
    Plane plane;
    Node * next;
};

class Queue
{
    private:
        Node * ini;
        int n;

    public:
        Queue();
        ~Queue();
        void push(Plane aviao);
        Plane pop();
        bool empty();
        int size();
        Plane front();
        /* outras funcoes que nao sao proprias da estrutura de dados fila*/

        void updateQueue();
        void printQueue();
        double totalTakeoffQueue();
        double totalLandingQueue();
        double totalFuelQueue();
};

Queue::Queue()
{
    Plane aux;

    ini = new Node;
    ini->plane = aux;
    ini->next = NULL;

    n = 0;
}

Queue::~Queue()
{
    Node * aux;
    aux = ini->next;
    while(aux != NULL)
    {
        ini->next = aux->next;
        delete aux;
        aux = ini->next;
    }
    delete ini;
    n = 0;
}

Plane Queue::pop()
{
    if(n > 0)
    {
        n--;
        Plane aviao;
        Node * aux;

        aux = ini->next;
        ini->next = ini->next->next;

        aviao = aux->plane;
        free(aux);

        return aviao;
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

Plane Queue::front()
{
    if(n > 0)
    {
        Plane aviao;

        aviao = ini->next->plane;

        return aviao;
    }
}

void Queue::push(Plane aviao)
{
    Node * i;

    i = ini;
    while(i->next != NULL) i = i->next;

    i->next = new Node;
    i = i->next;
    i->plane = aviao;
    i->next = NULL;

    n++;
}


/* funcoes auxiliares*/


void Queue::updateQueue()
{   
    Node * i;
    i = ini->next;
    while(i != NULL)
    {
        (i->plane.fuel) -= 1;
        (i->plane.waiting_time) += 1;

        i = i->next;
    }
}

void Queue::printQueue()
{
    Node * i;
    i = ini->next;
    while(i != NULL)
    {
        cout << "   " << i->plane.id << endl;
        i = i->next;
    }
}

double Queue::totalTakeoffQueue()
{
    Node * i;
    double total;
    total = 0;
    i = ini->next;

    while(i != NULL)
    {
        if(!(i->plane.landing))
        { 
            total += i->plane.waiting_time;
        }
        i = i->next;
    }

    return total;
}

double Queue::totalLandingQueue()
{
    Node * i;
    double total;
    total = 0;
    i = ini->next;

    while(i != NULL)
    {
        if((i->plane.landing))
        { 
            total += i->plane.waiting_time;
        }
        i = i->next;
    }

    return total;
}

double Queue::totalFuelQueue()
{
    Node * i;
    double total;
    total = 0;
    i = ini->next;

    while(i != NULL)
    {
        if((i->plane.landing))
        { 
            total += i->plane.fuel;
        }
        i = i->next;
    }

    return total;
}




#endif