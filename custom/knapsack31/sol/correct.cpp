#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n,k,x;
    scanf("%d%d%d",&n,&k,&x);
    vector<long long> cost(n);
    vector<int> damage(n);
    for(int i=0;i<n;++i) {
        scanf("%lld%d",&cost[i],&damage[i]);
        damage[i]=min(damage[i],x);
    }
    const long long INF=1LL<<60;
    vector<long long> dp(x+1,INF),next(x+1,INF);
    dp[0]=0;
    for(int turn=0;turn<k;++turn) {
        fill(next.begin(),next.end(),INF);
        for(int s=0;s<=x;++s) if(dp[s]!=INF) {
            for(int i=0;i<n;++i) {
                int to=min(x,s+damage[i]);
                next[to]=min(next[to],dp[s]+cost[i]);
            }
        }
        dp.swap(next);
    }
    printf("%lld\n",dp[x]==INF ? -1LL : dp[x]);
}
