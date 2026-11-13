#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,k; string a,b,marked; cin>>n>>m>>k>>a>>b>>marked;
    vector<vector<int>> f(k+1,vector<int>(m+1)); f[0][0]=1;
    for(int i=0;i<n;++i) {
        int mark=marked[i]-'0';
        for(int j=min(m,i+1);j>=1;--j) if(a[i]==b[j-1])
            for(int t=mark;t<=k;++t) {
                f[t][j]+=f[t-mark][j-1]; if(f[t][j]>=MOD) f[t][j]-=MOD;
            }
    }
    cout<<f[k][m]<<'\n';
}
