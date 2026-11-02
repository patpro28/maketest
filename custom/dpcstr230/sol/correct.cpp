#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; string a,b;
    cin>>n>>m>>a>>b;
    long long weights[26]; for(auto &x:weights) cin>>x;
    vector<long long> dp(m+1,0); long long answer=0;
    for(int i=0;i<n;++i) for(int j=m;j>=1;--j) {
        dp[j]=a[i]==b[j-1] ? max(0LL,dp[j-1]+weights[a[i]-'a']) : 0;
        answer=max(answer,dp[j]);
    }
    cout<<answer<<'\n';
}
