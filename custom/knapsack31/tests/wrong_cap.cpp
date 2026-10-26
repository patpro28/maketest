// Intentionally wrong: drop exact damage totals above 2*X, even after clipping D.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,k,x; scanf("%d%d%d",&n,&k,&x);
    vector<long long> c(n); vector<int> d(n);
    for(int i=0;i<n;++i) { scanf("%lld%d",&c[i],&d[i]); d[i]=min(d[i],x); }
    const long long INF=1LL<<60;
    vector<long long> dp(2*x+1,INF),next(2*x+1,INF); dp[0]=0;
    for(int turn=0;turn<k;++turn) {
        fill(next.begin(),next.end(),INF);
        for(int s=0;s<=2*x;++s) if(dp[s]!=INF) for(int i=0;i<n;++i) {
            if(s+d[i]<=2*x) next[s+d[i]]=min(next[s+d[i]],dp[s]+c[i]);
        }
        dp.swap(next);
    }
    long long answer=*min_element(dp.begin()+x,dp.end());
    printf("%lld\n",answer==INF ? -1LL : answer);
}
