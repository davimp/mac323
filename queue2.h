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
        /* outras funcoes que nao sao proprias da estrutura de dados fila */

        void updateQueue();
        void printQueue();
        double totalTakeoffQueue();
        double totalLandingQueue();
        double totalFuelQueue();

        Plane specialPop();
        Plane toEmergencyPop();
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
        delete aux;

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
    string emergencia, pouso;
    Node * i;
    i = ini->next;
    cout << endl;
    if(n > 0)
    { 
        cout << "    |    ID    | DESTINO/ORIGEM | EMERGENCIA | TEMPO DE ESPERA | COMBUSTIVEL | POUSO/DECOLAGEM |" << endl;
        cout << "    +----------+----------------+------------+-----------------+-------------+-----------------+" << endl;
    }
    else cout << "     Essa fila não possui aviões" << endl;
    while(i != NULL)
    {
        if(i->plane.emergency)
            emergencia = "SIM";
        else
            emergencia = "NÃO";

        if(i->plane.landing)
            pouso = "POUSO";
        else
            pouso = "DECOLAGEM";
        
        cout << "    |  " << i->plane.id << " |      " << i->plane.from_to << "       |    " << emergencia << "     |        " << i->plane.waiting_time << "        |     ";
        if(i->plane.fuel >= 10) cout << i->plane.fuel << "      | " << pouso << endl;
        else cout << i->plane.fuel << "       | " << pouso << endl;
        i = i->next;
    }
    cout << endl;
}

double Queue::totalTakeoffQueue()
{
    if(n == 0) return 0;
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
    if(n == 0) return 0;
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
    if(n == 0) return 0;
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

Plane Queue::specialPop()
{
    /* só irá ser chamada caso a lista não esteja vazia e se for a pista 3 com a fila de emergência vazia */
    Plane aviao;
    Node * aux, * p;
    p = ini;

    while(p->next != nullptr && (p->next->plane.landing))
        p = p->next;
    
    if(p->next != nullptr)
    {
        aux = p->next;
        p->next = aux->next;
        aviao = aux->plane;
        delete aux;
        n--;
    }

    return aviao;
}

Plane Queue::toEmergencyPop()
{
    /* só irá ser chamada caso a lista não esteja vazia e se for a pista 3 com a fila de emergência vazia */
    Plane aviao;
    Node * aux, * p;
    p = ini;

    aviao.emergency = 0;

    while(p->next != nullptr && (p->next->plane.fuel) > 0)
        p = p->next;
    
    if(p->next != nullptr)
    {
        aux = p->next;
        p->next = aux->next;
        aviao = aux->plane;
        aviao.emergency = 1;
        delete aux;
        n--;
    }

    return aviao;
}

#endif