#include<iostream>
#include<stdlib.h>
#include<string.h>
#include"plane.h"

using namespace std;


string comp[30] = {"QWE", "WER", "ERT", "RTY", "TYU", "YUI", "UIO", "IOP", "ASD", "SDF", "DFG", "FGH", "GHJ", "HJK", "JKL", "ZXC", "XCV", "CVB", "VBN", "BNM", "DKW", "ODL", "RKS", "AAA", "SSS", "CCC", "DDD", "WWW", "EEE", "YYY"};
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
    for(int i = 0; i < 4; i++)
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
    Plane av;
    int seed, T, K, auxiliar;
    cout << "Digite a semente: ";
    cin >> seed;
    srand(seed);

    auxiliar = rand();
    auxiliar = auxiliar%10;

    T = auxiliar;

    cout << T << endl;

    for(int i = 0; i < T; i++)
    {
        auxiliar = rand();
        auxiliar = auxiliar%10;
        K = auxiliar;
        cout << K << endl;
        for(int j = 0; j < K; j++)
        {
            av = randPlane();
            av.printPlane();
        }
    }
}