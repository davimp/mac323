#ifndef FILA_H
#define FILA_H

template<class Item>
class Fila
{
    private:


    public:

}

/*
tem que adaptar para usar o template da classe Item
void peneira(int i, int m, int v[])
{
    int f = 2*i, x = v[i];
    while(f <= m)
    {
        if(f < m && v[f] < v[f+1]) f++;
        if(x >= v[f]) break;
        v[i] = v[f];
        i = f;
        f = 2*i;
    }
    v[i] = x;
}


contrução:
for(int i = n/2; i >= 1; i--)
    peneira(i, n, v);


inserção:
void insere(int x, int v[])
{  
}

*/


#endif FILA_H