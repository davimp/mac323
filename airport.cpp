#include "queue.h"
using namespace std;
int T; /* unidades de tempo */
int K; /* quantidade de avioes que estão entrando em contato com a torre no dado instante de tempo */
int t; /* auxilar para tempo */
int k; /* auxilar para o 'K' */
int n; /* números de elemento na fila */

int emergencies, available_fuel;
int average_time, average_fuel, average_wait;
/* variáveis que ajudam a controlar as informações pedidas no enunciado do ep */
int takeoffs, landings, delays;

/* auxiliares */
string t_id, t_from_to;
bool t_landing;
int t_fuel, t_estimated_time;

Plane track1, track2, track3;

Queue airport;

int main()
{
    int i;

    cin >> T;

    for(t = 0; t < T; t++)
    {
        cin >> K;
        for(k = 0; k < K; k++)
        {
            /*(string t_id, string t_from_to, bool t_landing, int t_fuel, int t_estimated_time)*/
            /* lê os k aviões e coloca eles na fila*/
            cin >> t_id;
            cin >> t_from_to;

            cin >> t_landing;

            cin >> t_fuel;
            cin >> t_estimated_time;

            Plane aux {t_id, t_from_to, t_landing, t_fuel, t_estimated_time};

            airport.push(aux);
        }
        /* faz ajustes necessários (talvez seja melhor substituir por updateQueue */

        

        /* coleta dados */

        average_time = airport.averageTimeQueue();
        average_wait = airport.averageLandingQueue();
        average_fuel = airport.averageTakeofflQueue();
        /* calcula available_fuel - avioes que ja pousaram*/
        /* calcula emergencies - a */


        /* imprime dados */
        cout << "TEMPO : " << t << endl;
        cout << "*--------------------------------*" << endl;
        cout << "1) avioes em espera " << endl;
        cout << airport.printQueue() << endl;
        cout << "2) tempo medio de espera dos avioes que querem pousar (neste instante de tempo) " << endl;
        cout << " "  << average_time << endl;
        cout << "3) tempo medio de espera dos avioes que querem decolar (neste instante de tempo" << endl;
        cout << " " << average_wait << endl;
        cout << "4) quantidade media de combustivel dos aviões em espera " << endl;
        cout << " " << average_fuel << endl;
        cout << "5) quantidade media de combustivel disponível dos avioes que pousaram" << endl;
        cout << " " << available_fuel << endl;
        cout << "6) quantidade de avioes em condição de emergência (total) " << endl;
        cout << " " << emergencies << endl;
        


        /* atualiza o tempo e os atributos dos avioes (fazer função que acessa a lista e já faz isso ?? */


    }
}