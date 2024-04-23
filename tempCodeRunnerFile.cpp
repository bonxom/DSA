
int n;
int c[100][100];
int a[100], visited[100], path[100];
int cost = 0, min_cost = INT_MAX;

void NewRes(int a[]){
    for (int i = 1; i <= n; i++){
        path[i] = a[i];
    }
}
