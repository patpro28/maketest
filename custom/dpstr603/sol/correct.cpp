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
    vector<int> f(n);
    for(int l=n-1;l>=0;--l) {
        int inside=0;f[l]=1;
        for(int r=l+1;r<n;++r) {
            int old=f[r];
            f[r]=s[l]==s[r]?inside+2:max(f[r],f[r-1]);
            inside=old;
        }
    }
    cout<<f[n-1]<<'\n';
}
