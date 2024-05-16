#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[100], last_per[100];

void createfl(){
    for (int i = 1; i <= n; i++){
        a[i] = i;
        last_per[i] = n - i + 1;
    }
}

void in(int a[]){
    for (int i = 1; i <= n; i++){
        cout << a[i];
        if (i != n) cout << ", ";
    }
    cout << endl;
}

bool compare(int a[], int b[]){
    for (int i = 1; i <= n; i++){
        if (a[i] != b[i]) return false;
    }
    return true;
}

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void my_reverse(int begin, int end){
    while (begin < end){
        swap(a[begin], a[end]);
        begin++; end--;
    }
}
void generate(){
    while (1){
        in(a);
        if (compare(a, last_per)) return;
        int i = n - 1;
        while (a[i] >= a[i + 1]) i--;
        int j = n;
        while (a[j] <= a[i]) j--;
        swap(a[i], a[j]);
        my_reverse(i + 1, n);
    }
}

int main(){
    cin >> n;
    createfl();
    generate();
}