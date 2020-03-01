#include "queue2.h"
using namespace std;
int T; /* unidades de tempo */
int K; /* quantidade de avioes que estão entrando em contato com a torre no dado instante de tempo */
int t; /* auxilar para tempo */
int k; /* auxilar para o 'K' */
double n; /* números de elemento na fila */

int available_fuel;
int average_time, average_fuel, average_wait;
/* variáveis que ajudam a controlar as informações pedidas no enunciado do ep */
int takeoffs, landings, delays;

/* auxiliares */
string t_id, t_from_to;
bool t_landing, t_emergency;
int t_fuel, t_estimated_time;

Plane track1, track2, track3;

Queue normal;
Queue emergencies;

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
            cin >> t_emergency;

            cin >> t_fuel;
            cin >> t_estimated_time;

            Plane aux {t_id, t_from_to, t_landing, t_emergency, t_fuel, t_estimated_time};
            
            if(aux.emergency) emergencies.push(aux);
            else normal.push(aux);
        }
        /* faz ajustes necessários (talvez seja melhor substituir por updateQueue) */
        normal.updateQueue();
        emergencies.updateQueue();


        

        /* coleta dados */
        n = normal.size() + emergencies.size();
        average_time = normal.totalLandingQueue() + emergencies.totalLandingQueue(); /*average_time /= n;*/
        average_wait = normal.totalTakeoffQueue() + emergencies.totalTakeoffQueue(); /*average_wait /= n;*/
        average_fuel = normal.totalFuelQueue() + emergencies.totalFuelQueue(); /*available_fuel /= n;*/
        /* calcula available_fuel - avioes que ja pousaram*/
        /* calcula emergencies - a */


        /* imprime dados */
        cout << "*----------------------------------------------------------*" << endl;
        cout << "TEMPO : " << t << endl;
        cout << "1) Aviões em espera " << endl;
        cout << "   1.1) fila geral" << endl;
        normal.printQueue();
        cout << "   1.2) fila de emergencia " << endl;
        emergencies.printQueue();
        cout << "2) Tempo medio de espera dos avioes que querem pousar (neste instante de tempo): ";
        cout << " "  << average_time/n << endl;
        cout << "3) Tempo medio de espera dos avioes que querem decolar (neste instante de tempo): ";
        cout << " " << average_wait/n << endl;
        cout << "4) Quantidade media de combustivel dos aviões em espera: ";
        cout << " " << average_fuel/n << endl;
        cout << "5) Quantidade media de combustivel disponível dos avioes que pousaram: ";
        cout << " " << available_fuel << endl;
        cout << "6) Quantidade de avioes em condição de emergência (total): ";
        cout << " " << emergencies.size() << endl;
        


        /* atualiza o tempo e os atributos dos avioes (fazer função que acessa a lista e já faz isso ?? */


    }
    cout << "*----------------------------------------------------------*" << endl;

}