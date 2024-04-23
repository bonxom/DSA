#include <bits/stdc++.h>
using namespace std;

int n;
int c[100][100];
int a[100], visited[100], path[100];
int cost = 0, min_cost = INT_MAX;
int cnt = 0;

void NewRes(int a[]){
    for (int i = 1; i <= n; i++){
        path[i] = a[i];
    }
}

void result(){
    cout << "RESULT: ";
    for (int i = 1; i <= n; i++){
        cout << path[i] << " --> ";
    }
    cout << "1" << endl;
    cout << "COST: " << min_cost << endl;
    cout << "SO LOI GOI DE QUY: " << cnt << endl;
}

void Try(int k){
    cnt++;
    for (int y = 1; y <= n; y++){
        if (!visited[y]){
            a[k] = y;
            visited[y] = 1;
            cost += c[a[k-1]][a[k]];
            if (k == n){
                if (min_cost > cost + c[a[n]][a[1]]){
                    NewRes(a);
                    min_cost = cost + c[a[n]][a[1]];
                }
            }
            else Try(k + 1);
            cost -= c[a[k-1]][a[k]];
            visited[y] = 0;
        }
    }
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cin >> c[i][j];
        }
    }
    a[1] = 1;
    visited[1] = 1;
    Try(2);
    result();
}