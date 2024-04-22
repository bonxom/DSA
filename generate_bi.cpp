#include <bits/stdc++.h>
using namespace std;

int n;
string s = "", last_s = "";

void createfl(){
	for (int i = 0; i < n; i++){
		s += "0";
		last_s += "1";
	}
}

void generate(){
	while(1){
		cout << s << endl;
		if (s == last_s) return;
		else{
			int i = s.size() - 1;
			while (s[i] == '1' && i >= 0){
				s[i] = '0';
				i--;
			}
			s[i] = '1';
		}
	}
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	cin >> n;
	createfl();
	generate();
}
