#include "queue.h"
#include "plane.h"
using namespace std;
int T; /* unidades de tempo */
int K;
int t;
int k;
int n; /* numeros de elemento na fila */

int average_time, average_fuel, available_fuel, average_wait, emergencies;
/* varaiveis que ajudam a controlar as informções pedidas no enunciado do ep */
int takeoffs, landings, delays;

Queue<Plane> airport;

int main()
{
    int i;

    cin >> T;

    for(t = 0; t < T; t++)
    {
        cin >> K;
        for(k = 0; k < K; k++)
        {
            /* lê os k aviões e coloca eles na fila*/
            Plane aux;
            cin >> aux.id;
            cin >> aux.from;
            cin >> aux.to;

            cin >> aux.fuel;
            cin >> aux.estimated_time;
            cin >> aux.emergency;

            aux.waiting_time = 0;
            aux.track_time = 3;

            airport.push(aux);
        }
        /* faz ajustes necessários*/
        for(i = 0; i < 3; i++)
        {
            if(i < airport.size())
            {
                if(airport.q[i].track_time == 0)
                {
                    plane aux;
                    aux = airport.pop();

                    if(aux.from == "CGH")
                        takeoffs++;
                    else
                        landings++;

                    
                    if(aux.emergency)
                        emergencies++;
                    
                    if(aux.waiting_time >= aux.estimated_time*(0.1))
                        delays++;
                }
            }
        }

        /* coleta dados */

        /* talvez seja melhor fazer uma função pra calcular essas informações */
            /* average_time, average_fuel, planes_wating, average_wait, emergencies;*/

        /* imprime dados */
        cout << "TEMPO : " << t << endl;
        cout << "*--------------------------------*" << endl;
        cout << "1) avioes em espera " << endl;
        /* imprime os avioes que estao esperando*/
        cout << "2) tempo medio de espera de pouso " << endl;
        cout << " "  << average_time << endl;
        cout << "3) tempo medio de espera de decolagem " << endl;
        cout << " " << average_wait << endl;
        cout << "4) quantidade media de combustivel dos aviões em espera " << endl;
        cout << " " << average_fuel << endl;
        cout << "5) quantidade media de combustivel disponível dos avioes que pousaram" << endl;
        cout << " " << available_fuel << endl;
        cout << "6) quantidade de avioes em condição de emergência " << endl;
        cout << " " << emergencies << endl;
        


        /* atualiza o tempo e os atributos dos avioes (fazer função que acessa a lista e já faz isso ?? */

        for(i = 0; i < airport.size(); i++)
        {
            if(i < 3)
                airport.q[i].track_time -= 1; /* se ta na pista, diminui o tempo de pista*/
            
            airport.q[i].fuel -= 1;
            airport.q[i].waiting_time += 1;  
        }
    }
}