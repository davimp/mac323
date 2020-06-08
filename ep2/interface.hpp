#ifndef GRAFO
#define GRAFO

#include<iostream>
#include<algorithm>
#include<vector>
#include <unordered_map>
#include<iterator>
#include<string>
#include<queue>


/*
    Aluno: Davi de Menezes Pereira
    NUSP: 11221988
    EP2 - MAC323
    Arquivo interface.hpp
*/


//k definido como no enunciado será passado como argumento de linha de comando
class Grafo{
    private:
    int v; // quantos vert tem o grafo
    int a; // quantas arestas
    int k; // tamanho minimo das palavras (descrito no enunciado)
    bool achou_a, achou_b;

    std::unordered_map<std::string, std::string> id; // a qual componente o vertice pertence
    std::unordered_map<std::string, int> sz; // talamanho da componente a qual o vertice pertence
    std::unordered_map<std::string, int> dist; // guarda as distancias
    std::unordered_map<std::string, int> visited; // guarda se já foi visitado ou nao
    std::unordered_map<std::string, std::string> pai; // guarda quem eh o pai
    std::unordered_map<std::string, std::vector<std::string>> adj; // grafo representado com um array de vectors de adjacencia (nesse caso eh um map)
    std::vector<std::string> vert; // vector para guardar os vertices


    public:

    Grafo(int k_){
        /* Inicializa um grafo com parâmetro k  */
        v = 0;
        a = 0;
        k = k_;
        id.clear();
        sz.clear();
        dist.clear();
        visited.clear();
        adj.clear();
        vert.clear();
    }

    int insere(std::string palavra){
        /* Insere a palavra e retorna o número de arestas adicionados ao grafo,
        retorna -1 se a palavra já está no grafo ou tem tamanho menor que k*/
        int i, dif;
        int p, q, ret, dif1, dif2;
        bool ok = true;
        std::string aux;
        ret = 0;

        /* se  a palvra for menor do que o permitido */
        if((int)palavra.length() < k) return -1;

        /* checa se a palavra já foi inserida antes */
        for(i = 0; i < v; i++){
            if(palavra == vert[i]) return -1;
        }

        /* caso não tenha sido */
        id[palavra] = palavra;
        sz[palavra] = 1;

        for(int i = 0; i < v; i++){
            ok = true;
            dif1 = dif2  = -1;
            aux = vert[i];
            dif = palavra.length() - aux.length();

            if(dif > 1 || dif < -1) continue;

            if(dif == 0){
                /* as palavras tem o mesmo tamanho */
                for(p = 0; p < (int)palavra.length() && ok; p++){
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
                    if(palavra[dif1] != aux[dif2] || palavra[dif2] != aux[dif1]){
                        ok = false;
                    }
                }

                if(ok){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
            else if(dif < 0){
                /* palavras diferem de tamanho por um e "palavra" eh menor que "aux"*/
                q = 0;
                for(p = 0; p < (int)aux.length(); p++){
                    if(aux[p] != palavra[q]) continue;
                    q++;
                }
                if(q == (int)palavra.length()){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
            else{
                /* palavras diferem de tamanho por um e "palavra" eh maior que "aux"*/
                q = 0;
                for(p = 0; p < (int)palavra.length(); p++){
                    if(aux[q] != palavra[p]) continue;
                    q++;
                }
                if(q == (int)aux.length()){
                    /* cria aresta */
                    adj[aux].push_back(palavra);
                    adj[palavra].push_back(aux);
                    uni(aux, palavra);
                    ret++;
                }
            }
        }
        vert.push_back(palavra);
        v++;
        a += ret;
        return ret; /* devolve a quantidade de arestas criadas */
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
            if(id[vert[i]] == vert[i]){
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

        /* se tiver mais de uma componente então não eh conexo */
        if(componentes() > 1)
            return false;
        else
            return true;
    }

    int tamComp(std::string palavra){
        /* Retorna o tamanho da componente conexa onde está a palavra
        ou -1 caso ela não se encontre no grafo */
        if(sz[palavra]){
            return sz[find(palavra)];
        }
        else{
            return -1;
        }
    }

    void bfs(std::string fonte){
        dist.clear(); // limpa o map que contem as distancias
        std::queue<std::string> fila;
        fila.push(fonte); // Insere a fonte na fila
        dist[fonte] = 0; // Iniciando a distancia da fonte como zero	

        std::string aux;
        while(!fila.empty()){
            aux = fila.front(); // Pega o primeiro elemento da fila
            fila.pop(); // Apaga o primeiro elemento da fila
            for(std::string viz:adj[aux]){
                if(dist[viz] || viz == fonte) // Se foi visitado, não adiciona na fila
                    continue;
                
                dist[viz] = dist[aux]+1;
                fila.push(viz);
            }
        }
    }

    int distancia(std::string a, std::string b){
        /* Retorna a menor distância entre as palavras a e b ou -1
        caso elas estejam desconexas ou não estejam no grafo */

        if(find(a) != find(b)){
            return -1;
        }
        else{
            /* bfs */
            bfs(a);
            return dist[b];
        }
    }

    void dfs1(std::string fonte, std::string a){
        visited[fonte] = 1;
        for(std::string viz:adj[fonte]){
            pai[viz] = fonte;
            if(visited[viz]){
                if(viz == a && pai[fonte] != a){
                    achou_a = true;
                }
                continue;
            }
            dfs1(viz, a);
        }
    }

    void dfs2(std::string fonte, std::string a, std::string b){
        visited[fonte] = 1;
        if(fonte == b) achou_b = true;

        for(std::string viz:adj[fonte]){
            pai[viz] = fonte;
            if(visited[viz]){
                if(achou_b && viz == a && pai[fonte] != a){
                    achou_a = true;
                }
                continue;
            }
            dfs2(viz, a, b);
        }
        if(fonte == b) achou_b = false;
    }

    bool emCiclo(std::string a){
        /* Retorna verdadeiro caso a palavra esteja em algum ciclo,
        falso caso contrário */
        pai.clear();
        visited.clear();
        achou_a = false;
        dfs1(a, a);

        return achou_a;
    }

    bool emCiclo(std::string a, std::string b){
        /* Retorna verdadeiro casa exista um ciclo que contenha ambas as palavras,
        falso caso contrário */
        if(find(a) != find(b)){
            return false;
        }
        pai.clear();
        visited.clear();
        achou_a = false;
        achou_b = false;
        dfs2(a, a, b);

        return achou_a;
    }

    double distanciaMedia(){
        std::string a, b;
        double ret;
        int i, j, cnt;
        ret = 0;
        cnt = 0;
        for(i = 0; i < v; i++){
            a = vert[i];
            bfs(a);
            for(j = i+1; j < v; j++){
                b = vert[j];
                if(dist[b]){
                    ret += dist[b];
                    cnt++;
                }
            }
        }
        /*std::cout << ret << " odadosjaodj " << cnt << "\n";*/
        ret /= cnt;
        dist.clear();
        return ret;
    }

    /* retorna o grau medio dos vertices */
    double grauMedio(){
        int i;
        double ret;
        ret = 0;
        for(i = 0; i < v; i++){
            ret += (double)adj[vert[i]].size();
        }
        ret /= v;
        return ret;
    }

    /* retorna se o grafo eh denso ou nao a partir da escolhida */
    bool denso(){
        if(a > v*v/100) return true;
        else return false;
    }

    double tamMedio(){
        /* Retorna o número de componentes do grafo */
        int cnt;
        double ret;
        cnt = componentes();

        if(v){ /* a soma dos tamanhos das componentes de um grafo eh o numero de vertices */
            ret = (double)v/(double)cnt;
            return ret;
        }
        else{
            return 0;
        }
    }


    /* retorna o tamanho da maior componente*/
    int maiorComponente(){
        int i, maior;
        maior = 0;
        for(i = 0; i < v; i++){
            if(id[vert[i]] == vert[i]){
                if(maior < sz[vert[i]]){
                    maior = sz[vert[i]];
                }
            }
        }
        return maior;
    }

    /* retorna o tamanho da menor componente */
    int menorComponente(){
        int i, menor;
        menor = (1e9+9);
        for(i = 0; i < v; i++){
            if(id[vert[i]] == vert[i]){
                if(menor > sz[vert[i]]){
                    menor = sz[vert[i]];
                }
            }
        }
        if(menor == (1e9+9)) menor = 0;
        return menor;
    }

    /* imprime as informações gerais do grafo */
    void imprime(){
        std::cout<< "\nInformações gerais:\n";
        std::cout<< "Imprimindo informações sobre o grafo...\n";
        std::cout<< "Quantidade de vertices: " << vertices() << "\n";
        std::cout<< "Quantidade de arestas: " << arestas() << "\n";
        std::cout<< "Grau medio dos vertices: " << grauMedio() << "\n";
        if(denso()){
            std::cout<< "O grafo eh considerado denso.\n";
        }
        else{
            std::cout<< "O grafo não eh considerado denso.\n";
        }
        if(conexo()){
            std::cout<< "O grafo eh conexo\n";
        }
        else{
            std::cout<< "O grafo não eh conexo\n";
        }
        std::cout << "Quantidade de componentes: " << componentes() << "\n";
        std::cout << "Tamanho medio das componentes do grafo: " << tamMedio() << "\n";
        std::cout << "Tamanho da menor componente: " << menorComponente() << "\n";
        std::cout << "Tamanho da maior componente: " << maiorComponente() << "\n";
        std::cout<< "Distancia media entre duas palavras: " << distanciaMedia() << "\n\n";
    }
};

#endif