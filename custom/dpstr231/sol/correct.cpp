#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    int k; cin>>n>>m>>k>>a>>b;
    vector<vector<int> > dp(k+1,vector<int>(m+1)); int answer=0;
    for(int i=0;i<n;++i) for(int t=k;t>=0;--t) {
        for(int j=m;j>=1;--j) {
            if(a[i]==b[j-1]) dp[t][j]=dp[t][j-1]+1;
            else dp[t][j]=t>0 ? dp[t-1][j-1]+1 : 0;
            if(t==k) answer=max(answer,dp[t][j]);
        }
    }
    cout<<answer<<'\n';
}
