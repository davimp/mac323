#include<iostream>
#include<algorithm>
#include <vector>
#include<string>
#include<fstream>
#include"interface.hpp"
using namespace std;

/*
    Aluno: Davi de Menezes Pereira
    NUSP: 11221988
    EP2 - MAC323
    Arquivo ep2.cpp
*/

Grafo g(3);
string aux;
string a, b;
int n;


int main(){
    fstream arq;
    cout << "Digite o nome do arquivo texto a ser lido (com o .txt se tiver):\n ";
    cin >> aux;
    arq.open(aux);

    /* Faz o tratamento de strings */
    string op, especial;
    size_t pos;
    especial = ".\"!-:,_'’—?)(;*#1234567890$@%&*[]+/ ";
    while(arq >> op){
        if(op != ""){
            for(char x: especial)
                while ((pos  = op.find(x))!= std::string::npos)
                    op.erase(pos, 1);
            for(char & x : op){
                if(!isascii(x)){
                    while ((pos  = op.find(x))!= std::string::npos)
                        op.erase(pos, 1);
                }
                else x = tolower(x);
            }
            g.insere(op);
        }
    }
    arq.close();

    /* Informações gerais sobre o grafo */
    g.imprime();

    /*cout << g.distancia("ave", "vea") << endl;*/
    /* Teste com ciclos */
    cout << "Digite quantos testes você deseja realizar:\n ";
    cin >> n;
    while(n--){
        cout << "Digite as duas palavras:\n ";
        cin >> a >> b;

        if(g.emCiclo(a)){
            cout << a << " esta num cliclo.\n";
        }
        else{
            cout << a << " não esta num cliclo.\n";
        }
        
        if(g.emCiclo(b)){
            cout << b << " esta num cliclo.\n";
        }
        else{
            cout << b << " não esta num cliclo.\n";
        }

        if(g.emCiclo(a, b)){
            cout << a << " e " << b << " estao num mesmo cliclo.\n";
        }
        else{
            cout << a << " e " << b << " não estao num mesmo cliclo.\n";
        }
    }

}
