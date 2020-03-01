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


        bool landing;
        bool emergency;

        int fuel;
        int estimated_time;
        int waiting_time;
        int track_time; /*auxiliar variable to control the time when the flight track will be ocupied*/
        /*on this atribute, everyone begins with 3*/

    public:
        Plane(); /* default constructor */
        Plane(string t_id, string t_from_to, bool t_landing, bool emergency, int t_fuel, int t_estimated_time);
        /*~plane();*/
};

Plane::Plane()
{
    this->id = "0";
    this->from_to = "0";
    this->landing = false;
    this->fuel = 0;
    this->estimated_time = 0;
    this->waiting_time = 0; /*sempre começa com  0*/
    this->track_time = 3; /*sempre começa com 3*/ 
}

Plane::Plane(string t_id, string t_from_to, bool t_landing, bool t_emergency, int t_fuel, int t_estimated_time)
{
    this->id = t_id;
    this->from_to = t_from_to;
    this->landing = t_landing;
    this->emergency = t_emergency;
    this->fuel = t_fuel;
    this->estimated_time = t_estimated_time;
    this->waiting_time = 0; /*sempre comeca com  0*/
    this->track_time = 3; /*sempre comeca com 3*/ 
}

#endif