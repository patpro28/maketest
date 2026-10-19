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
    ll a,b; int q; cin>>a>>b>>q; ll p=a+b;
    while(q--) {
        ll l,r; cin>>l>>r; --l; --r;
        ll left=l/p, right=r/p, answer;
        if(left==right) answer=max(0LL,min(r%p+1,a)-min(l%p,a));
        else answer=(right-left-1)*a + a-min(l%p,a)+min(r%p+1,a);
        cout<<answer<<'\n';
    }
}
