#include<iostream>

using namespace std;

int n; 

char f(int x){
	if(x < 10) return x + '0';
	return x - 10 + 'A';
}

void out(int x){
	if(x >= 16) out(x / 16);
	cout << f(x % 16);
}

int main(){
	cin >> n;
	if(n < 16) cout << 0;
	out(n);
	return 0;
}