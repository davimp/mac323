#include "pqueue.h"
#include "plane.h"
using namespace std;
int T; /* time */

int main(){    
    Priority_queue<Plane> fila;

    Plane aviao {"ASD", 2, "CTP", 10, 8, 7};
    Plane aviao2 {"AWD", 4, "GTP", 6, 5, 4};

    fila.push(aviao);
    fila.push(aviao2);

    Plane x;
    int y;
    x = fila.front();

    y = x.fuel;

    cout << fila.size() << endl;
}