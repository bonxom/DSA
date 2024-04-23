#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[1000], visited[1000];

void printsol(int a[]){
    for (int i = 1; i <= m; i++){
        cout << a[i];
        if (i != m) cout << ", ";
    }
    cout << endl;
}

void Try(int k){
    for (int y = a[k-1] + 1; y <= n - m + k; y++){
        a[k] = y;
        if (k == m) printsol(a);
        else Try(k + 1);
    }
}

int main(){
    cin >> n >> m;
    Try(1);
}