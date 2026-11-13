#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; string s; cin>>n>>k>>s;
    vector<vector<int>> f(k+1,vector<int>(n));
    for(int l=n-1;l>=0;--l) {
        vector<int> inside(k+1);
        for(int t=0;t<=k;++t) f[t][l]=1;
        for(int r=l+1;r<n;++r) {
            int oldBelow=0;
            for(int t=0;t<=k;++t) {
                int old=f[t][r];
                int best=max(f[t][r],f[t][r-1]);
                if(s[l]==s[r]) best=max(best,inside[t]+2);
                else if(t) best=max(best,oldBelow+2);
                oldBelow=inside[t];inside[t]=old;
                f[t][r]=best;
            }
        }
    }
    cout<<f[k][n-1]<<'\n';
}
