#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "util.hpp"
#include "vetorDes.hpp"


using namespace std;

int main(int argc, char *argv[]){
    string nome_arquivo = argv[1];
    int n;
    vetorDes<string,int> st(nome_arquivo);

    cout << st.devolve("Mazama") << endl;
    cout << st.rank("este") << endl;
    cout << st.seleciona(10) << endl;
    st.remove("Peter");
    st.remove("Mazama");
    st.remove("os");
    cout << st.devolve("Mazama") << endl;
}
