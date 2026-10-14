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
    int n,k; long long initial,x; scanf("%d%lld%d%lld", &n,&initial,&k,&x);
    vector<int> d(n); long long base=initial; int sum=0;
    for(int i=0;i<n;++i) { long long a,b; scanf("%lld%lld",&a,&b); base+=a; d[i]=int(b-a); sum+=d[i]; }
    long long delta=x-base;
    if(delta<0 || delta>sum) { puts("NO"); return 0; }
    int target=int(delta); vector<int> dp(target+1,n+1); dp[0]=0;
    for(int v:d) for(int s=target;s>=v;--s) dp[s]=min(dp[s],dp[s-v]+1);
    puts(dp[target]<=k ? "YES" : "NO");
}
