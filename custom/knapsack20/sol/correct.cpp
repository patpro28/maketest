#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n,h; scanf("%d%d",&n,&h); const long long INF=1LL<<60;
    vector<long long> dp(h+1,INF); dp[0]=0;
    for(int i=0;i<n;++i) {
        long long c,d; scanf("%lld%lld",&c,&d);
        for(int s=0;s<h;++s) if(dp[s]!=INF) {
            int to=int(min<long long>(h,s+d)); dp[to]=min(dp[to],dp[s]+c);
        }
    }
    printf("%lld\n",dp[h]);
}
