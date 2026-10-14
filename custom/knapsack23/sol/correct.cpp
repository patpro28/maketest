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
    int n,k; scanf("%d%d",&n,&k); const int LIMIT=1000;
    vector<int> distance(LIMIT+1,1000000); distance[1]=0;
    for(int u=1;u<=LIMIT;++u) for(int x=1;x<=u;++x) {
        int to=u+u/x; if(to<=LIMIT) distance[to]=min(distance[to],distance[u]+1);
    }
    vector<long long> dp(k+1,0);
    for(int i=0;i<n;++i) {
        int b; long long v; scanf("%d%lld",&b,&v); int cost=1+distance[b];
        for(int s=cost;s<=k;++s) dp[s]=max(dp[s],dp[s-cost]+v);
    }
    printf("%lld\n",dp[k]);
}
