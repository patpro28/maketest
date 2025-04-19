#include<iostream>
#include<vector>

using namespace std;

const int N = 2e5 + 10;
int n, q, l, x, y;
vector<int> v[N];

int main(){
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> l;
		while(l--){
			cin >> x;
			v[i].push_back(x);
		}
	}
	while(q--){
		cin >> x >> y;
		cout << v[x][y-1] << '\n';
	}
	return 0;
}