#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    int k; long long penalty; cin>>n>>m>>k>>penalty>>a>>b;
    long long weights[26]; for(auto &x:weights) cin>>x;
    vector<vector<long long> > dp(k+1,vector<long long>(m+1)); long long answer=0;
    for(int i=0;i<n;++i) for(int t=k;t>=0;--t) {
        for(int j=m;j>=1;--j) {
            if(a[i]==b[j-1]) dp[t][j]=max(0LL,dp[t][j-1]+weights[a[i]-'a']);
            else dp[t][j]=t>0 ? max(0LL,dp[t-1][j-1]-penalty) : 0;
            if(t==k) answer=max(answer,dp[t][j]);
        }
    }
    cout<<answer<<'\n';
}
