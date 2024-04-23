#include <bits/stdc++.h>
using namespace std;

int n, m;
pair <int, int> obj[1000];
int value = 0, max_value = INT_MIN;
int a[1000], took[1000], solution[1000];
int cnt = 0, weight = 0, num = 0, res_weight = 0;

void NewRes(int a[]){
    for (int i = 1; i <= num; i++){
        solution[i] = a[i];
    }
}

void Try(int k){
    for (int y = 1; y <= n; y++){
        if (!took[y]){
            a[k] = y;
            took[y] = 1;
            weight += obj[y].first;
            if (weight > m){
                if (max_value < value){
                    memset(solution, 0, sizeof(solution));
                    NewRes(a);
                    max_value = value;
                    res_weight = weight - obj[y].first;
                    k = n;
                }
            }
            else{
                value += obj[y].second;
                num++;
            }
            if (k == n){
                if (max_value < value){
                    memset(solution, 0, sizeof(solution));
                    NewRes(a);
                    max_value = value;
                    res_weight = weight;
                }
            }
            else Try(k + 1);
            if (weight <= m){
                value -= obj[y].second;
                num--;
            }
            weight -= obj[y].first;
            took[y] = 0;
        }
    }
}

void Result(){
    cout << "TAKE OBJECT: ";
    for (int i = 1; i <= 1000; i++){
        if (solution[i] == 0) break;
        cout << solution[i];
        if (solution[i + 1] != 0) cout << ", ";
    }
    cout << endl;
    cout << "WEIGHT: " << res_weight << endl;
    cout << "VALUE: " << max_value << endl;
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> obj[i].first >> obj[i].second;
    }
    Try(1);
    Result();
}