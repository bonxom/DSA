#include <bits/stdc++.h>
using namespace std;
int n;
int a[1000];

void printsol(int a[]){
    for (int i = 1; i <= n; i++){
        cout << a[i];
    }
    cout << endl;
}

void Try(int k){
    for (int y = 0; y <= 1; y++){
        a[k] = y;
        if (k == n) printsol(a);
        else Try(k + 1);
    }
}

int main(){
    cin >> n;
    Try(1);
}