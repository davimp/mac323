#include "queue2.h"
using namespace std;

/*string t_id, string t_from_to, bool t_landing, int t_fuel, int t_estimated_time*/

Queue fila;

int main(){    
    Plane aviao {"ASD", "GRU", true, 10, 8};
    Plane aviao2 {"AWD", "GTP", true, 6, 5};
    Plane aux;
    double av;

    fila.push(aviao);
    fila.push(aviao2);

    /*aux = fila.pop();*/

    fila.printQueue();

    av = fila.totalTakeoffQueue();
    
    cout << "hello" << endl;
    cout << av << endl;
}