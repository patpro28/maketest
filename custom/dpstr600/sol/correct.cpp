#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; string s; cin>>n>>q>>s;
    vector<vector<unsigned char>> pal(n,vector<unsigned char>(n));
    for(int l=n-1;l>=0;--l) for(int r=l;r<n;++r)
        pal[l][r]=(s[l]==s[r] && (r-l<2 || pal[l+1][r-1]));
    while(q--) { int l,r;cin>>l>>r;cout<<(pal[l-1][r-1]?"YES":"NO")<<'\n'; }
}
