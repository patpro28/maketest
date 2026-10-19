#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

ll c3(ll x) { return x<3?0:x*(x-1)*(x-2)/6; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q; vector<int>a(n); for(int &x:a) cin>>x; sort(a.begin(),a.end());
    vector<int>values; vector<ll>prefix;
    for(int i=0;i<n;) {
        int j=i+1; while(j<n && a[j]==a[i]) ++j;
        ll c=j; values.push_back(a[i]); prefix.push_back(c3(c)+c*(c-1)/2*(n-c)); i=j;
    }
    while(q--) { ll k; cin>>k; cout<<values[lower_bound(prefix.begin(),prefix.end(),k)-prefix.begin()]<<'\n'; }
}
