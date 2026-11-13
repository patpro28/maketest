#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; string s; cin>>n>>s;
    vector<unsigned char> pal(n);
    int best=1,start=1;
    for(int l=n-1;l>=0;--l) {
        unsigned char inside=1;
        for(int r=l;r<n;++r) {
            unsigned char old=pal[r];
            pal[r]=(s[l]==s[r] && (r-l<2 || inside));
            if(pal[r] && (r-l+1>best || (r-l+1==best && l+1<start))) { best=r-l+1;start=l+1; }
            inside=old;
        }
    }
    cout<<best<<' '<<start<<'\n';
}
