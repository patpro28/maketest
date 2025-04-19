#include<bits/stdc++.h>
#define ll long long

using namespace std;

int k, n, a[200], x[15], dem = 0;
bool d[15];

void sth(ll i, ll last = 0){ //sth: sinh tổ hợp, last: phần tử trước i
    if(i == k){
        for(int u = 0; u < i; u++){
            cout << a[x[u]] << " ";
        }
        dem++;
        cout << "\n";
        return;
    }
    for(int j = last + 1; j <= n; j++){
        x[i] = j;
        sth(i + 1, j);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> k >> n;
    assert(k <= n);
    assert(n <= 10);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a+1, a+1+n);
    sth(0);
    cout << dem;
}