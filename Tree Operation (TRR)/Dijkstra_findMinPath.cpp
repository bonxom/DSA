#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 100007
#define INF 1e9+7


vector <pair<int, int>> Adj[MAX]; // 1 mảng có kiểu vector<pair>, first lưu v, second lưu weight
int n, m, s, t;
int d[MAX], p[MAX];
bool found[MAX];

void input(){
    cin >> n >> m;
    for (int k = 1; k <= m; k++){
        int u, v, w;
        cin >> u >> v >> w;
        pair<int, int> edge = pair{v, w};
        Adj[u].push_back(edge);// danh sách cạnh kề của đỉnh u
    }
    cin >> s >> t;
}

void Relax(int u, int v, int weight){
    if (d[v] > d[u] + weight){
        d[v] = d[u] + weight;
        p[v] = u;
    }
}

void PrintPath(int x){
    if (p[x] != x) PrintPath(p[x]);
    if (x != t) cout << x << " -> ";
    else cout << t << endl;
}

void Dijkstra(){
    for (int i = 0; i < Adj[s].size(); i++){//initialize các đỉnh có cạnh từ s tới (danh sách kề)
        pair<int, int> e = Adj[s][i];
        d[e.first] = e.second;
    }
    
    // for (int i = 1; i <= n; i++){
    //     cout << d[i] << " ";
    // }// check 1
    // cout << endl;
    
    for (int v = 1; v <= n; v++){//initialize các đỉnh ko có cạnh từ s đến là vô cùng
        if (d[v] == 0) d[v] = INF; 
        p[v] = s;
        found[v] = false;
    }
    d[s] = 0; found[s] = true;
    
    // for (int i = 1; i <= n; i++){
    //     cout << d[i] << " ";
    // }//check 2
    // cout << endl;

    for (int k = 1; k < n; k++){
        int du = INF, u;// tìm u là đỉnh có d[u] nhỏ nhất trong số đỉnh còn lại
        for (int v = 1; v <= n; v++){
            if (!found[v] && du > d[v]){
                du = d[v];
                u = v;
            }
        }
        found[u] = true;// đã tìm ra đường đi min từ s đến u
        
        // cout << "min: " << u << endl;
        
        if (u == t) break; // đã tìm ra đường đi min từ s đến t
        
        for (int i = 0; i < Adj[u].size(); i++){
            pair<int, int> e = Adj[u][i];
            if (!found[e.first]) Relax(u, e.first, e.second);
        }
    }
    
    cout << "Weight: " << d[t] << endl;
    PrintPath(t);
}

int main(){
    input();
    Dijkstra();

    // cout << "\n------------------" << endl;
    // for (int i = 1; i <= n; i++){
    //     for (int j = 0; j < Adj[i].size(); j++){
    //         pair<int, int> e = Adj[i][j];
    //         cout << "(" << e.first << " ," << e.second << ") ->";
    //     }
    //     cout << endl;
    // }
}