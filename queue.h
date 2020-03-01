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
        void printQueue();
        double averageTakeoffQueue();
        double averageLandingQueue();
        double averageFuelQueue();
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
    int i;
    for(i = ini; i < ini + n; i++)
    {
       /* aprende a codar */   
    }
}

void Queue::printQueue()
{
    int i;
    for(i = ini; i < ini + n; i++)
        cout << q[i].id << endl;
}

double Queue::averageTakeoffQueue()
{
    int i, cnt;
    double average;
    average = 0;
    cnt = 0;
    for(i = ini; i < ini + n; i++)
        if(!q[i].landing)
        {
            cnt++;
            average += q[i].waiting_time;
        }
    
    if(cnt != 0) average /= cnt;

    return average;
}

double Queue::averageLandingQueue()
{
    int i, cnt;
    double average;
    average = 0;
    cnt = 0;
    for(i = ini; i < ini + n; i++)
        if(q[i].landing)
        {
            cnt++;
            average += q[i].waiting_time;
        }
    
    if(cnt != 0) average /= cnt;

    return average;
}

double Queue::averageFuelQueue()
{
    int i, cnt;
    double average;
    average = 0;
    cnt = 0;
    for(i = ini; i < ini + n; i++)
        if(q[i].landing)
        {
            cnt++;
            average += q[i].fuel;
        }


    if(cnt != 0) average /= cnt;

    return average;
}




#endif