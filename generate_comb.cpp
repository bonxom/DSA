#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[100], last_comb[100];

void createfl(){
    for (int i = 1; i <= m; i++){
        a[i] = i;
        last_comb[i] = n - m + i;
    }
}

void in(int a[]){
    for (int i = 1; i <= m; i++){
        cout << a[i];
        if (i != m) cout << ", ";
    }
    cout << endl;
}

bool compare(int a[], int b[]){
    for (int i = 1; i <= m; i++){
        if (a[i] != b[i]) return false;
    }
    return true;
}

void generate(){
    while (1){
        in(a);
        if (compare(a, last_comb)) return;
        int i = m;
        while (a[i] == n - m + i) i--;
        a[i]++;
        for (int j = i + 1; j <= m; j++){
            a[j] = a[i] + j - i;
        }
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin >> n >> m;  
    createfl();
    generate();
}
