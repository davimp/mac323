#include<bits/stdc++.h>
using namespace std;
const int MAX = 1000;
int v[MAX];
int n;

int bb(int x){
    int l, r, m;
    l = 0; r = n;
    m = (l+r)/2;
    while(l < r){
        m = (l+r)/2;
        if(x <= v[m]){
            r = m;
        }
        else{
            l = m+1;
        }
    }
    return r;
}

void insert(int x)
{
    int aux;
    int troca;
    int i;
    int l, r, m;
    l = 0; r = n;
    m = (l+r)/2;
    while(l < r){
        m = (l+r)/2;
        if(x <= v[m]){
            r = m;
            if(v[m] == x){
                return;
            }
        }
        else{
            l = m+1;
        }
    }
    aux = v[r];
    v[r] = x;

    for(i = r+1; i <= n; i++){
        troca = aux;
        aux = v[i];
        v[i] = troca;
    }
    n++;
}

int main(int argc, char *argv[]){
    int o;
    int q;
    cout << v[0] << "\n";
    cin >> q;
    for(int i = 0; i < q; i++){
        cin >> o;
        insert(o);
    }
    
    for(int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << "\n";
    cout << bb(7) << endl;
}
