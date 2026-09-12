#include <bits/stdc++.h>
#define int long long
using namespace std;
int tcs2(string n){
	long long s = -1e18;
	for(int i = 0; i < (int)n.length(); i++){
        if(s < n[i] - '0'){
            s = n[i] - '0';
        }
	}
	return s;
}
signed main() {
    string n; cin >> n;
    cout << tcs2(n);
}