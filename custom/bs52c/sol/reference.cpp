#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q; vector<int>a(n); for(int &x:a) cin>>x; sort(a.begin(),a.end());
    vector<ll>sum(n); ll total=0;
    for(ll i=0;i<n;++i) { total+=i*(n-1-i); sum[i]=total; }
    while(q--) { ll k; cin>>k; cout<<a[lower_bound(sum.begin(),sum.end(),k)-sum.begin()]<<'\n'; }
}
