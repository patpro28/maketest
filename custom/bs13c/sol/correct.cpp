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
    int n,q; cin>>n>>q; vector<int>a(n); for(int &x:a) cin>>x;
    sort(a.begin(),a.end());
    while(q--) {
        int x; cin>>x; auto lo=lower_bound(a.begin(),a.end(),x);
        if(lo==a.end()) cout<<"-1 0\n";
        else cout<<*lo-x<<' '<<upper_bound(lo,a.end(),*lo)-lo<<'\n';
    }
}
