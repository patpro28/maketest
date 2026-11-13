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
    const int MOD=1000000007;
    vector<int> f(n);
    for(int l=n-1;l>=0;--l) {
        int inside=0;f[l]=1;
        for(int r=l+1;r<n;++r) {
            int old=f[r];
            long long value=1LL*f[r]+f[r-1]+(s[l]==s[r]?1:-inside);
            f[r]=int((value+MOD)%MOD);inside=old;
        }
    }
    cout<<f[n-1]<<'\n';
}
