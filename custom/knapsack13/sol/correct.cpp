#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n,x; scanf("%d%d",&n,&x); const long long INF=1LL<<60;
    vector<long long> dp(x+1,INF); dp[0]=0;
    for(int i=0;i<n;++i) {
        long long c; int p; scanf("%lld%d",&c,&p);
        for(int s=x;s>=0;--s) if(dp[s]!=INF) dp[min(x,s+p)]=min(dp[min(x,s+p)],dp[s]+c);
    }
    printf("%lld\n",dp[x]==INF ? -1LL : dp[x]);
}
