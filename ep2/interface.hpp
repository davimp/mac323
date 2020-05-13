#ifndef GRAFO
#define GRAFO

#include<iostream>
#include<algorithm>
#include<vector>
#include <unordered_map>
#include<iterator>
#include<string>
#include<queue>

//k definido como no enunciado será passado como argumento de linha de comando
class Grafo{
    private:
    /*const int MAX = 100000;*/
    int v; // quantos vertices tem o grafo
    int a; // quantas arestas
    int k; // tamanho minimo das palavras (descrito no enunciado)
    std::unordered_map<std::string, std::string> id; // a qual componente o vertice pertence
    std::unordered_map<std::string, int> sz; // talamanho da componente à qual o vertice pertence
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, vector<std::string>> adj; // grafo representado com um array de vectors de adjacência;
    std::vector<std::string> vertices; //vector para guardar os vertices


    public:

    Grafo(int k_){
        /* Inicializa um grafo com parâmetro k  */
        int i;
        v = 0;
        a = 0;
        k = k_;
        id.clear();
        sz.clear();
        dist.clear();
    }

    int insere(std::string palavra){
        /* Insere a palavra e retorna o número de arestas adicionados ao grafo,
        retorna -1 se a palavra já está no grafo ou tem tamanho menor que k*/
        int i, dif, cnt;
        int p, q, ret, dif1, dif2;
        bool ok = true;
        std::string aux;

        if(palavra.length() < k) return -1;

        /* checa se a palavra já foi inserida antes */
        for(i = 0; i < v; i++){
            if(palavra == vertices[i]) return -1;
        }

        /* caso nã tenha sido */
        id[palavra] = palavra;
        sz[palavra] = 1;
        for(int i = 0; i < v; i++){
            ok = true;
            dif1 = dif2  = -1;
            aux = vertices[i];
            dif = palavra.length() - aux.length();

            if(dif > 1 || dif < -1) continue;

            if(dif == 0){
                /* as palavras tem o mesmo tamanho */
                for(p = 0; p < palavra.length() && ok; p++){
                  if(palavra[p] != aux[p]){
                    if(dif1 == -1){
                        dif1 = p;
                    }
                    else if(dif2 == -1){
                        dif2 = p;
                    }
                    else{
                        ok = false;
                    }
                  }
                }

                if(dif2 != -1){
                    if(palavra[dif1] != aux[dif2] || palavra[dif2] != aux[dif1])[
                        ok = false;
                    ]
                }

                if(ok){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
            else if(dif < 0)[{
                /* palavras diferem de tamanho por um e "palavra" eh menor que "aux"*/
                q = 0;
                for(p = 0; p < aux.length(); p++){
                    if(aux[p] != palavra[q]) continue;
                    q++;
                }
                if(q == palavra.length()){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
            else{
                /* palavras diferem de tamanho por um e "palavra" eh maior que "aux"*/
                for(p = 0; p < palavra.length(); p++){
                    if(aux[q] != palavra[p]) continue;
                    q++;
                }
                if(q == aux.length()){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
        }

        a += ret;
        return ret;
    }

    int vertices(){
        /* Retorna o número de vértices do grafo*/
        return v;
    }

    int arestas(){
        /* Retorna o número de vértices do grafo*/
        return a;
    }
 
    /* acha qual a componente que p faz parte */
    std::string find(std::string p){
        if(id[p] == p) return p;
        return id[p] = find(id[p]);
    }
    
    /* coloca as palavras p e q na mesma componente */
    void uni(std::string p, std::string q){
        std::string aux;
        p = find(p);
        q = find(q);
        if(p == q) return;
        if(sz[p] > sz[q]){
            /*swap(p, q)*/
            aux = p;
            p = q;
            q = aux;
        }
        id[p] = q;
        sz[q] += sz[p];
    }

    int componentes(){
        /* Retorna o número de componentes do grafo */
        int i;
        int cnt;
        cnt = 0;
        for(i = 0; i < v; i++){
            if(id[vertices[i]] == vertices[i]){
                cnt++;
            }
        }
        return cnt;
    }

    bool conexo(){
        /* Retorna se o grafo é ou não conexo */
        if(a < v-1){
            return false;
        }
        if(a > ((v-1)*(v-2))/2){
            return true;
        }

        /* run dfs ??? maybe not */
        if(componentes() > 1)
            return false;
        else
            return true;
    }

    int tamComp(std::string palavra){
        /* Retorna o tamanho da componente conexa onde está a palavra
        ou -1 caso ela não se encontre no grafo */
        if(id[palavra]){
            return sz[palavra];
        }
        else{
            return -1;
        }
    }

    void bfs(std::string fonte){
        dist.clear(); //limpa o map que contem as distancias
        queue<std::string> fila;
        fila.push(fonte); //Insere a fonte na fila
        dist[fonte] = 0; //Iniciando a distancia da fonte como zero	

        std::string aux;
        while(!fila.empty()){
            aux = fila.front(); //Pega o primeiro elemento da fila
            fila.pop(); //Apaga o primeiro elemento da fila
            for(std::string viz:adj[aux]){ // CORRIGIR ISSO
                if(dist[viz] || viz == fonte) // Se foi visitado, não adiciona na fila
                    continue;
                
                dist[viz] = dist[aux]+1;
                fila.insert(viz);
            }
        }
    }

    int dist(std::string a, std::string b){
        /* Retorna a menor distância entre as palavras a e b ou -1
        caso elas estejam desconexas ou não estejam no grafo */
        int dif;

        if(id[a] != id[b]){
            return -1;
        }
        else{
            /* bfs */
            bfs(a);
            return dist[b];
        }

    }

    bool emCiclo(std::string a){
        /* Retorna verdadeiro caso a palavra esteja em algum ciclo,
        falso caso contrário */
    }

    bool emCiclo(std::string a, std::string b){
        /* Retorna verdadeiro casa exista um ciclo que contenha ambas as palavras,
        falso caso contrário */
    }
};

#endif