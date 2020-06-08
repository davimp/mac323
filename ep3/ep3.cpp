#include<bits/stdc++.h>
using namespace std;

class NFA
{
    private:
    int n;
    vector<int> adj[1000];
    string rgx;

    public:
    NFA(string re){
        rgx = re;
        stack<int> op;
        int i;
        int lp;
        n = re.length();
        for(i = 0; i < n; i++){
            adj[i].clear();
        }
        for(i = 0; i < n; i++){
            lp = i;
            if(re[i] == '(' || re[i] == '|'){
                op.push(i);
            }
            else if(re[i] == ')'){
                int ou;
                ou = op.top();
                op.pop();
                if(re[ou] == '|'){
                    lp = op.top();
                    op.pop();
                    adj[lp].push_back(ou+1);
                    adj[ou].push_back(i);
                }
                else{
                    lp = ou;
                }
            }

            if(i < n-1 && re[i+1] == '*'){
                adj[lp].push_back(i+1);
                adj[i+1].push_back(lp);
            }
            if(re[i] == '(' || re[i] == '*' || re[i] == ')'){
                adj[i].push_back(i+1);
            }
        }
    }

    void dfs(int fonte, unordered_map<int, int> &visited, vector<int> &fila){
        visited[fonte] = 1;
        fila.push_back(fonte);
        for(int viz : adj[fonte]){
            if(visited[viz]) continue;
            dfs(viz, visited, fila);
        }
        return;
    }

    bool match(string txt){
        bool ok = false;
        int i, m;
        vector<int> fila, achou;
        unordered_map<int, int> visited;
        m = txt.length();
        fila.clear();
        visited.clear();
        dfs(0, visited, fila);
        if(visited[n]) ok = true;
        for(i = 0; i < m; i++){
            achou.clear();
            for(int j : fila){
                if(rgx[j] == txt[i] || rgx[j] == '.'){
                    achou.push_back(j+1);
                }
                else if(rgx[j] == txt[i] || rgx[j] == '.'){
                    achou.push_back(j+1);
                }
            }
            fila.clear();
            visited.clear();
            for(int j : achou){
                dfs(j, visited, fila);
            }
            if(visited[n]) ok = true;
        }
    
        if(ok) return true;
        else return false;
    }

    void print(){
        int i, j, n;
        n = rgx.length();
        rgx = rgx + "  ";
        cout << "digraph G {\n";
        for(i = 0; i < n; i++){
            for(j = 0; j < adj[i].size(); j++){
                cout << "\"(" << i << ") " << rgx[i] << "\" -> \"(" << adj[i][j] << ") " << rgx[adj[i][j]] << "\"\n";
            }
        }
        cout << "}";
    }
};

int main()
{
    int tc;
    bool res;
    string reg, teste;
    cout << "Digite a regex: ";
    cin >> reg;
    NFA g(reg);
    cout << "Digite a quantidade de testes que serão feitos: ";
    cin >> tc;
    while(tc--){
        cin >> teste;
        res = g.match(teste);
        if(res){
            cout << teste << " é reconhecida pela regex\n";
        }
        else{
            cout << teste << " NÃO é reconhecida pela regex\n";
        }
    }
    return 0;
}