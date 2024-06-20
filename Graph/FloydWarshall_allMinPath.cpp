#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int W[10004][10004], D[10004][10004];
int n, m;
int u, v, w;

void Initialize(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j) W[i][j] = 0;
            else W[i][j] = 10000007;
        }
    }
}

void FloydWarshall(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            D[i][j] = W[i][j];
        }
    }

    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}

void output(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    cin >> n >> m;
    Initialize();
    for (int i = 0; i < m; i++){
        cin >> u >> v >> w;
        W[u][v] = w;
    }
    FloydWarshall();
    output();
}