#include <bits/stdc++.h>
using namespace std;

int n, b;
pair <int, int> obj[1000];
int a[1000];
pair <int, pair<int, int>> solution[1000];
int value = 0, max_value = 0, weight = 0;

void NewRes(int a[]){
    weight = 0;
    for (int i = 1; i <= n; i++){
        solution[i].first = a[i];
        solution[i].second = obj[i];
        weight += solution[i].second.second * solution[i].first;
    }
}

void Try(int k){
    int sk = b / obj[k].second;
    for (int x = 0; x <= sk; x++){
        a[k] = x;
        b -= x * obj[k].second;
        value += x * obj[k].first;
        if (k == n){
            if (max_value < value){
                max_value = value;
                NewRes(a);
            }
        }
        else{
            int g = value + (double)obj[k + 1].first * b / obj[k + 1].second;
            if (g > max_value) Try(k + 1);
        }
        b += x * obj[k].second;
        value -= x * obj[k].first;
    }
}

bool cmp(pair<int, int> a, pair<int, int> b){
    double x1 = (double)a.first / a.second;
    double x2 = (double)b.first / b.second;
    return x1 > x2;
}

void Result(){
    cout << "SOLUTION:\n";
    for (int i = 1; i <= n; i++){
        cout << "(" << solution[i].second.first << ", " << solution[i].second.second << ")"
        << " QUANTITY: " << solution[i].first << endl;
    }
    cout << endl;
    cout << "VALUE: " << max_value << endl;
    cout << "WEIGHT: " << weight <<  endl;
}
int main(){
    cin >> n >> b;
    for (int i = 1; i <= n; i++){
        cin >> obj[i].first >> obj[i].second; //first là value, second là weight
    }
    sort(obj + 1, obj + n + 1, cmp);

    Try(1);
    Result();
}