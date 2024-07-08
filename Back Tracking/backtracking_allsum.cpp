#include <bits/stdc++.h>
using namespace std;

int n, sum;
int current_sum = 0;
int a[1000];

void printsol(){
    for (int i = 1; i <= n; i++){
        cout << a[i];
        if (i != n) cout << " + ";
    }
    cout << " = " << sum;
    cout << endl;
}

void Try(int k){
    for (int y = 1; y <= sum - (n - k) - current_sum; y++){
        a[k] = y;
        current_sum += a[k];
        if (k == n){
            if (current_sum == sum) printsol();
        }
        else Try(k + 1);
        current_sum -= a[k];
    }
}

int main(){
    cin >> n >> sum;
    Try(1);
}