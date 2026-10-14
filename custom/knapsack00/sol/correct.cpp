#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,c; scanf("%d%d",&n,&c);
    vector<long long> dp(c+1,0);
    for(int i=0;i<n;++i) {
        int w; long long v; scanf("%d%lld",&w,&v);
        for(int capacity=c;capacity>=w;--capacity) dp[capacity]=max(dp[capacity],dp[capacity-w]+v);
    }
    printf("%lld\n",dp[c]);
}
