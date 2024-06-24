#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int Intro(){
    cout << "Sorting Type: \n";
    cout << "1. Selection Sort\n" << "2. Selection Sort ver2\n" << "3. Bubble Sort\n"
    << "4. Bubble Sort ver2\n" << "5. Insertion Sort\n" << "6. Couting Sort\n";
    int i; cin >> i;
    return i;
}

//////////
void SelectionSort(int n, int a[]){ //O(N^2)
    int cnt = 0;
    int max_val = 0;
    int pos = 0;
    for (int i = n - 1; i > 1; i--){
        max_val = 0;
        for (int  j = 0; j < i; j++){
            if (max_val < a[j]){
                max_val = a[j];
                pos = j;
            }
            cnt++;
        }
        if (max_val > a[i]) swap(a[pos], a[i]);
    }

    cout << "----------------------\n";
    cout << "SELECTION SORT\n";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "COMPLEXITY: " << cnt << endl;
}

//////////
void SelectionSort_v2(int n, int a[]){
    int cnt = 0;
    int max_val = 0;
    int pos = 0;
    int check_end = 0;
    for (int i = n - 1; i > 1; i--){
        max_val = 0;
        for (int  j = 0; j < i; j++){
            if (max_val < a[j]){
                max_val = a[j];
                pos = j;
            }
            if (a[j] > a[j + 1]) check_end++;
            cnt++;
        }
        if (check_end == 0) break;
        if (max_val > a[i]) swap(a[pos], a[i]);
    }

    cout << "----------------------\n";
    cout << "SELECTION SORT version 2\n";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "COMPLEXITY: " << cnt << endl;
}

//////////
void BubbleSort(int n, int a[]){ //O(N^2)
    int cnt = 0;
    for (int i = n; i > 1; i--){
        for (int j = 1; j < i; j++){
            cnt++;
            if (a[j] < a[j - 1]) swap(a[j], a[j - 1]);
        }
    }

    cout << "----------------------\n";
    cout << "BUBBLE SORT\n";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "COMPLEXITY: " << cnt << endl;
}

//////////
void BubbleSort_v2(int n, int a[]){
    int cnt = 0, swap_cnt = 0;
    for (int i = n; i > 1; i--){
        swap_cnt = 0;
        for (int j = 1; j < i; j++){
            cnt++;
            if (a[j] < a[j - 1]) {
                swap_cnt++;
                swap(a[j], a[j - 1]);
            }
        }
        if (swap_cnt == 0) break;
    }

    cout << "----------------------\n";
    cout << "BUBBLE SORT version 2\n";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "COMPLEXITY: " << cnt << endl;
}

////////////
void InsertionSort(int n, int a[]){ //O(N^2), best O(N)
    int cnt = 0;
    for (int i = 1; i < n; i++){
        cnt++;
        if (a[i] < a[i - 1]){
            int tmp = a[i];
            int j = i - 1;
            while (j >= 0 && tmp < a[j]){
                cnt++;
                a[j + 1] = a[j]; 
                j--;       
            }
            j++;
            a[j] = tmp;
        }
    }

    cout << "----------------------\n";
    cout << "INSERTION SORT\n";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "COMPLEXITY: " << cnt << endl;
}

///////////
void CoutingSort(int n, int a[]){ //O(n + k)  k: max element, a[]: positive interger array
    int k = 0;
    int dem = 0;
    for (int i = 0; i < n; i++){
        k = max(k, a[i]);
    }
    int cnt[k + 1] = {0};
    for (int i = 0; i < n; i++){
        cnt[a[i]]++;
    }
    cout << "----------------------\n";
    cout << "COUTING SORT\n";   
    for (int i = 0; i < k + 1; i++){
        for (int j = 0; j < cnt[i]; j++){
            cout << i << " ";
            dem++;
        }
        dem++;
    }
    cout << endl;
    cout << "COMPLEXITY: " << dem << endl;
}

int main(){
    int require = Intro(); 
    cout << "Size: ";
    int n; cin >> n;
    cout << "Array: ";
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    switch (require)
    {
    case 1: SelectionSort(n, a); break;
    case 2: SelectionSort_v2(n, a); break;
    case 3: BubbleSort(n, a); break;
    case 4: BubbleSort_v2(n, a); break;
    case 5: InsertionSort(n, a); break;
    case 6: CoutingSort(n, a); break;
    default:
        cout << "ERROR\n";
        break;
    }
}