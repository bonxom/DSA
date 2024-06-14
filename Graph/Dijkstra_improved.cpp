#include <bits/stdc++.h>
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
        pair<int, int> edge = {v, w};
        Adj[u].push_back(edge);// danh sách cạnh kề của đỉnh u
    }
    cin >> s >> t;
}

priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q; 
void Relax(int u, int v, int weight){
    if (d[v] > d[u] + weight){
        d[v] = d[u] + weight;
        p[v] = u;
        Q.push({d[v], v});
    }
}

void PrintPath(int x){
    if (p[x] != x) PrintPath(p[x]);
    if (x != t) cout << x << " -> ";
    else cout << t << endl;
}

void Dijkstra() {
    fill(d, d + n + 1, INF);
    d[s] = 0;
    p[s] = s;
    Q.push({d[s], s});

    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        
        if (!found[u]) {
            found[u] = true;
            for (int i = 0; i < Adj[u].size(); i++){
                pair<int, int> e = Adj[u][i];
                if (!found[e.first]) Relax(u, e.first, e.second);
            }
        }
    }

    if (d[t] == INF) {
        cout << "No path from " << s << " to " << t << endl;
    } else {
        cout << "Weight: " << d[t] << endl;
        PrintPath(t);
        cout << endl;
    }
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