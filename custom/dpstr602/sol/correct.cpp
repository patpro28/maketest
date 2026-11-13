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
    long long answer=0;
    for(int l=n-1;l>=0;--l) {
        unsigned char inside=1;
        for(int r=l;r<n;++r) {
            unsigned char old=pal[r];
            pal[r]=(s[l]==s[r] && (r-l<2 || inside));
            answer+=pal[r];inside=old;
        }
    }
    cout<<answer<<'\n';
}
