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
    int n,q; cin>>n>>q; map<int,int> count;
    for(int i=0,x;i<n;++i) { cin>>x; ++count[x]; }
    while(q--) {
        int x; cin>>x; auto it=count.lower_bound(x);
        if(it==count.end()) cout<<"-1 0\n";
        else cout<<it->first-x<<' '<<it->second<<'\n';
    }
}
