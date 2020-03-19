#include "queue.h"
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
Queue landed;
Queue departed;
Queue fail;

int main()
{
    int i;
    track3.track_time = 0; track3.estimated_time = -1;
    track2.track_time = 0; track2.estimated_time = -1;
    track1.track_time = 0; track1.estimated_time = -1;

    cin >> T;

    for(t = 0; t < T; t++)
    {
        cin >> K;
        for(k = 0; k < K; k++)
        {
            /* lê os k aviões e coloca eles na fila*/
            cin >> t_id;
            cin >> t_from_to;

            cin >> t_landing;
            cin >> t_emergency;

            cin >> t_fuel;
            cin >> t_estimated_time;

            Plane aux {t_id, t_from_to, t_landing, t_emergency, t_fuel, t_estimated_time};
            
            if(t_emergency) emergencies.push(aux);
            else normal.push(aux);
        }


        /* -------------------- controle das pistas ---------------------- */

        /* pista 3 - para casos normais, só pode ser usada para decolagem*/
        if(track3.track_time <= 0)
        {
            if(track3.estimated_time > 0)
            {
                if(track3.landing)
                {
                    landed.push(track3);
                }
                else
                {
                    departed.push(track3);
                }
                track3.estimated_time = -1;
            }

            /* put on landings or departures queue*/
            if(!emergencies.empty())
            {
                track3 = emergencies.pop();
            }
            else if(!normal.empty())
            {
                track3 = normal.specialPop();
            }
        }

        /* pista 1 */
        if(track1.track_time <= 0)
        {
            if(track1.estimated_time > 0)
            {
                if(track2.landing)
                {
                    landed.push(track1);
                }
                else
                {
                    departed.push(track1);
                }
                track1.estimated_time = -1;
            }

            /* put on landings or departures queue*/
            if(!emergencies.empty())
            {
                track1 = emergencies.pop();
            }
            else if(!normal.empty())
            {
                track1 = normal.pop();
            }
        }

        /* pista 2 */
        if(track2.track_time <= 0)
        {
            /* put on landings or departures queue*/

            if(track2.estimated_time > 0)
            {
                if(track2.landing)
                {
                    landed.push(track2);
                }
                else
                {
                    departed.push(track2);
                }
                track2.estimated_time = -1;
            }

            if(!emergencies.empty())
            {
                track2 = emergencies.pop();
            }
            else if(!normal.empty())
            {
                track2 = normal.pop();
            }
        }

        /* ----------------- fim: controle das pistas ---------------------- */

        /* vê se tem algum avião que tem que ser mandado embora, isto é, aqueles que ainda estão na fila de emergencia */
        while(!emergencies.empty())
        {
            Plane aux;
            aux = emergencies.pop();
            fail.push(aux);
        }

        /*atualiza*/
        normal.updateQueue();
        track1.track_time--;
        track2.track_time--;
        track3.track_time--;


        /* coleta dados */

        average_time = normal.totalLandingQueue() + emergencies.totalLandingQueue(); /*average_time /= n;*/
        average_wait = normal.totalTakeoffQueue() + emergencies.totalTakeoffQueue(); /*average_wait /= n;*/
        average_fuel = normal.totalFuelQueue() + emergencies.totalFuelQueue(); /*available_fuel /= n;*/
        available_fuel = landed.totalFuelQueue();
        /* calcula available_fuel - avioes que ja pousaram*/
        /* calcula emergencies - a */


        /* imprime dados */
        cout << "*--------------------------------------------------------------------------------------*" << endl;
        cout << "TEMPO : " << t << " de " << T-1 << endl;
        cout << K << " aviões entraram em contato" << endl;

        cout << "1) Aviões: " << endl;
        cout << "   1.1) fila geral" << endl;
        normal.printQueue();
        cout << "   1.2) fila de emergencia " << endl;
        emergencies.printQueue();
        cout << "   1.3) aviões que pousaram " << endl;
        landed.printQueue();
        cout << "   1.4) aviões que decolaram " << endl;
        departed.printQueue();
        cout << "   1.5) aviões que deram erro " << endl;
        fail.printQueue();
        cout << "2) Tempo de espera dos avioes que querem pousar (neste instante de tempo): ";
        cout << " "  << average_time << endl;
        cout << "3) Tempo de espera dos avioes que querem decolar (neste instante de tempo): ";
        cout << " " << average_wait << endl;
        cout << "4) Quantidade de combustivel dos aviões em espera para pousar: ";
        cout << " " << average_fuel << endl;
        cout << "5) Quantidade de combustivel disponível dos avioes que pousaram: ";
        cout << " " << available_fuel << endl;
        cout << "6) Quantidade de avioes em condição de emergência (total): ";
        cout << " " << emergencies.size() << endl;
        cout << "7) Pistas :" << endl;

        if(track1.estimated_time > 0) cout << "   Pista 1 : " << track1.id << endl;
        else cout << "   Pista 1 : livre" << endl;

        if(track2.estimated_time > 0) cout << "   Pista 2 : " << track2.id << endl;
        else cout << "   Pista 2 : livre" << endl;

        if(track3.estimated_time > 0) cout << "   Pista 3 : " << track3.id << endl;
        else cout << "   Pista 3 : livre" << endl;

        /* checa na fila normal se tem algum aviao que deve ser mandado para a fila de emergencia */

        Plane aux;

        aux = normal.toEmergencyPop();
        while(aux.emergency)
        {
            emergencies.push(aux);
            aux = normal.toEmergencyPop();
        }

    }
    cout << "*--------------------------------------------------------------------------------------*" << endl;

}