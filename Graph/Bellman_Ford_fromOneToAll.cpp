#include <bits/stdc++.h>
using namespace std;

#define MAX 1007
#define INF 1e9+7

int n,m, s;
vector <pair<int, int>> Adj[MAX]; //mỗi phần tử trong mảng là 1 vector kiểu pair, lưu cạnh và trọng số của Adj[i];
int d[MAX], p[MAX];

void input(){
    cin >> n >> m; //n dinh, m canh
    for (int i = 1; i <= m; i++){
        int v, u, w;
        cin >> v >> u >> w;
        Adj[v].push_back({u, w});
    }
    cin >> s;
}

void Initialize(){
    for (int i = 0; i < Adj[s].size(); i++){
        d[Adj[s][i].first] = Adj[s][i].second;
    }
    for (int v = 1; v <= n; v++){
        p[v] = s;
        if (d[v] == 0) d[v] = INF;
    }
    p[s] = s; d[s] = 0;
}

void Relax(int u, int v, int w){
    if (d[v] > d[u] + w){
        d[v] = d[u] + w;
        p[v] = u;
    }
}

void Bellman_Ford(){
    Initialize();
    for (int k = 1; k <= n - 1; k++){
        for (int u = 1; u <= n; u++){
            for (int v = 1; v <= n; v++){
                if (v != s){
                    for (int i = 0; i < Adj[u].size(); i++){
                        if (v == Adj[u][i].first) Relax(u, v, Adj[u][i].second);
                    }
                }
            }
        }
    }
}

void PrintPath(int v){
    if (v != p[v]) PrintPath(p[v]);
    cout << v << " ";
}

void output(){
    for (int v = 1; v <= n; v++){
        if (v != s){
            cout << "Path to " << v << ": ";
            PrintPath(v);
            cout << endl;
            cout << "Weight: " << d[v] << endl;
        }
    }
}

int main(){
    input();
    Bellman_Ford();
    output();
}