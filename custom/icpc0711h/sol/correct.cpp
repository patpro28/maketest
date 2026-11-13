#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int &x:a)cin>>x;
    for(int &x:b)cin>>x;
    const int INF=255,S=1<<n;
    vector<array<unsigned char,51>>dp(S);
    for(auto &row:dp)row.fill(INF);
    dp[0][0]=0;
    for(int mask=0; mask<S; mask++) {
        auto &row=dp[mask];
        for(int v=1; v<=50; v++)row[v]=min(row[v],row[v-1]);
        int pos=__builtin_popcount((unsigned)mask);
        for(int i=0; i<n; i++)if(!(mask>>i&1)) {
            int val=((pos-i)&1)?b[i]:a[i];
            if(row[val]==INF)continue;
            int cost=i-__builtin_popcount((unsigned)(mask&((1<<i)-1)));
            auto &dest=dp[mask|(1<<i)][val];
            dest=min<int>(dest,row[val]+cost);
        }
    }
    cout<<(dp[S-1][50]==INF?-1:int(dp[S-1][50]))<<'\n';
}
