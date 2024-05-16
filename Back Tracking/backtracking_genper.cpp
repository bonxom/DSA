#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000], visited[1000];

void printsol(int a[]){
    for (int i = 1; i <= n; i++){
        cout << a[i];
        if (i != n) cout << ", ";
    }
    cout << endl;
}

void Try(int k){
    for (int y = 1; y <= n; y++){
        if (!visited[y]){
            a[k] = y;
            visited[y] = 1;
            if (k == n) printsol(a);
            else Try(k + 1);
            visited[y] = 0;
        }
    }
}

int main(){
    cin >> n;
    Try(1);
}