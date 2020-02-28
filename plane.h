#include<iostream>
#include<string.h>
using namespace std;
#ifndef PLANE_H
#define PLANE_H

class Plane
{
    public:
        string id;
        string from_to;
        bool landing

        int fuel;
        int estimated_time;
        bool emergency; /* maybe there is a better way to do that */

        int waiting_time;
        int track_time; /*auxiliar variable to control the time when the flight track will be ocupied*/
        /*on this atribute, everyone begins with 3*/

    public:
        Plane(); /* default constructor */
        Plane(string t_id, string t_from_to, bool t_landing, int t_fuel, int t_estimated_time, int t_waiting_time, int t_track_time);
        /*~plane();*/

/*
        bool operator<(Plane &p);
        bool operator<=(Plane &p);
        bool operator>(Plane &p);
        bool operator>=(Plane &p);
        void operator=(Plane &p);*/
};

Plane::Plane()
{
    this->id = NULL;
    this->from_to = NULL;
    this->landing = false;
    this->fuel = 0;
    this->estimated_time = 0;
    this->waiting_time = 0; /*sempre comeca com  0*/
    this->track_time = 3; /*sempre comeca com 3*/ 
}

Plane::Plane(string t_id, string t_from_to, bool t_landing, int t_fuel, int t_estimated_time)
{
    this->id = t_id;
    this->from_to = t_from_to;
    this->landing = t_landing;
    this->fuel = t_fuel;
    this->estimated_time = t_estimated_time;
    this->waiting_time = 0; /*sempre comeca com  0*/
    this->track_time = 3; /*sempre comeca com 3*/ 
}

/*
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
*/




#endif