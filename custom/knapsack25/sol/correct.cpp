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
    int n,x,y; scanf("%d%d%d",&n,&x,&y); vector<vector<long long>> dp(x+1,vector<long long>(y+1,0));
    for(int i=0;i<n;++i) {
        int a,b; long long v; scanf("%d%d%lld",&a,&b,&v);
        for(int s=a;s<=x;++s) for(int t=b;t<=y;++t) dp[s][t]=max(dp[s][t],dp[s-a][t-b]+v);
    }
    printf("%lld\n",dp[x][y]);
}
