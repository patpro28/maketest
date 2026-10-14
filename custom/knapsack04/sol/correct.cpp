#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,c; scanf("%d%d",&n,&c); const long long NEG=-(1LL<<60);
    vector<long long> dp(c+1,NEG); dp[0]=0;
    for(int i=0;i<n;++i) {
        int w; long long v; scanf("%d%lld",&w,&v);
        for(int s=c;s>=w;--s) if(dp[s-w]!=NEG) dp[s]=max(dp[s],dp[s-w]+v);
    }
    printf("%lld\n",dp[c]==NEG ? -1LL : dp[c]);
}
