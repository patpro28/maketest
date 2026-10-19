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
    ll a,b; int q; cin>>a>>b>>q;
    auto f=[&](ll x) { return x/(a+b)*a+min(x%(a+b),a); };
    while(q--) { ll l,r; cin>>l>>r; cout<<f(r)-f(l-1)<<'\n'; }
}
