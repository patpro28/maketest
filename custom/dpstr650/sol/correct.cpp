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
    vector<long long> del(n),change(n),f(n);
    for(int i=0;i<n;++i) cin>>del[i]>>change[i];
    for(int l=n-1;l>=0;--l) {
        long long inside=0;
        for(int r=l+1;r<n;++r) {
            long long old=f[r];
            long long pairCost=s[l]==s[r]?0:min(change[l],change[r]);
            f[r]=min({del[l]+f[r],del[r]+f[r-1],inside+pairCost});
            inside=old;
        }
    }
    cout<<f[n-1]<<'\n';
}
