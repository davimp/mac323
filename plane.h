#include<iostream>
#include<string.h>
using namespace std;
#ifndef PLANE_H
#define PLANE_H

class Plane
{
    private:
        string id;
        string from_to;
        int take_off;
        int type; /* still undefined, it serves to tell if a plane is a emergency plane or a normal one */
        int priority;

    public:
        int fuel;
        Plane(); /* default constructor */
        Plane(string t_id, int t_fuel, string t_from_to, int t_take_off, int t_type, int priority);
        /*~plane();*/

        bool operator<(Plane &p);
        bool operator<=(Plane &p);
        bool operator>(Plane &p);
        bool operator>=(Plane &p);
        void operator=(Plane &p);
};

Plane::Plane()
{
    this->id = "0";
    this->fuel = 0;
    this->from_to = "0";
    this->take_off = 0;
    this->type = 0;
    this->priority = 0;
}

Plane::Plane(string t_id, int t_fuel, string t_from_to, int t_take_off, int t_type, int t_priority)
{
    this->id = t_id;
    this->fuel = t_fuel;
    this->from_to = t_from_to;
    this->take_off = t_take_off;
    this->type = t_type;
    this->priority = t_priority;
}

bool Plane::operator<(Plane &p)
{
    return this->priority < p.priority;
}

bool Plane::operator<=(Plane &p)
{
    return this->priority <= p.priority;
}

bool Plane::operator>(Plane &p)
{
    return this->priority > p.priority;
}

bool Plane::operator>=(Plane &p)
{
    return this->priority >= p.priority;
}


void Plane::operator=(Plane &p)
{
    this->id = p.id;
    this->fuel = p.fuel;
    this->from_to = p.from_to;
    this->take_off = p.take_off;
    this->type = p.type;
    this->priority = p.priority;
    /*return p;*/
}

#endif