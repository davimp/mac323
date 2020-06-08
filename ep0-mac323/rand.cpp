#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include"plane.h"

using namespace std;


string comp[30] = {"QW","WE","ER","RT","TY","YU","UI","IO","OP","AS","SD","DF","FG","GH","HJ","JK","KL","ZX","XC","CV","VB","BN","NM","QA","WS","ED","RF","TG","YH","UJ"};
string places[30] = {"QAZ","WSX","EDC","RFV","TGB","YHN","UJM","IKO","NYU","CWB","NAT","GRU","CGH","SAT","PLO","ORL","SAO","BSB","AAF","QQQ","IME","PUC","UTI","RHJ","DKL","JDS","JBL","BRA","FRE","LKK",};

Plane randPlane()
{
    string r_id, r_from_to;
    bool r_landing;
    bool r_emergency;
    int r_fuel,r_estimated_time;
    int aux;

    aux = rand();
    aux = aux%30;
    r_id = "";
    r_id += comp[aux];
    for(int i = 0; i < 3; i++)
    {
        aux = rand();
        r_id += '0' + aux%10;
    } 

    aux = rand();
    aux = aux%30;
    r_from_to = places[aux];


    aux = rand();
    r_landing = aux%2;

    aux = rand();
    aux = aux%100;
    if(aux <= 5)
        r_emergency = 1;
    else
        r_emergency = 0;

    
    aux = rand();
    aux = aux%100;
    r_fuel = aux;

    aux = rand();
    aux = aux%100;
    r_estimated_time = aux;

    Plane aviao {r_id, r_from_to, r_landing, r_emergency, r_fuel, r_estimated_time};
    return aviao;
}

int main()
{
    ofstream f_out;
    string arquivo;
    Plane av;
    int seed, T, K, auxiliar;
    cout << "Digite a semente: ";
    cin >> seed;
    srand(seed);

    cout << "Escreva o nome do arquivo onde deseja salvar (não precisa colocar o .txt): ";
    cin >> arquivo;
    f_out.open(arquivo + ".txt");

    auxiliar = rand();
    auxiliar = auxiliar%10;


    T = auxiliar;

    f_out << T << endl;

    for(int i = 0; i < T; i++)
    {
        auxiliar = rand();
        auxiliar = auxiliar%10;
        K = auxiliar;
        f_out << K << endl;
        for(int j = 0; j < K; j++)
        {
            av = randPlane();
            /*av.printPlane();*/
            f_out << av.id << endl;
            f_out << av.from_to << endl;
            f_out << av.landing << endl;
            f_out << av.emergency << endl;
            f_out << av.fuel << endl;
            f_out << av.estimated_time << endl;
        }
    }

    f_out.close();

    if(! f_out.good())
        return -1;
    else cout << "Arquivo criado!" << endl;



}