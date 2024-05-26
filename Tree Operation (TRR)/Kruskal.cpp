#include <bits/stdc++.h>
using namespace std;

int parent[1000000];
int ran[1000000];
int n, m;
pair <pair<int, int>, int> Edge[1000000]; // second là value, first (pair) là cạnh

void makeSet(int x){
    parent[x] = x;
    ran[x] = 0;
}

int findSet(int x){
    while (parent[x] != x) x = parent[x];
    return x;
}

void link(int ru, int rv){
    if (ran[ru] > ran[rv]) parent[rv] = ru;
    else{
        parent[ru] = rv;
        if (ran[ru] == ran[rv]) ran[rv]++;
    }
}

int Kurusal(){
    for (int i = 1; i <= n; i++){
        makeSet(i);
    }
    int cnt = 0;
    int res = 0;

    for (int i = 1; i <= m; i++){
        int ru = findSet(Edge[i].first.first);
        int rv = findSet(Edge[i].first.second);
        if (ru != rv) {
            link(ru, rv);
            res += Edge[i].second;
            cnt++;
            if (cnt == n - 1) break;
        }
    }

    if (cnt < n - 1){
        cout << "Khong lien thong" << endl; return 0;
    }
    return res;
}

bool cmp(pair<pair<int,int>, int> x, pair<pair<int, int>, int> y){
    return x.second < y.second;
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> Edge[i].first.first >> Edge[i].first.second >> Edge[i].second;
    }
    sort(Edge + 1, Edge + m + 1, cmp);
    int res = Kurusal();
    cout << res;
}