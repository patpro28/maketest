#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,x; scanf("%d%d",&n,&x); int inf=x+1;
    vector<int> dp(x+1,inf); dp[0]=0;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a);
        for(int s=a;s<=x;++s) dp[s]=min(dp[s],dp[s-a]+1);
    }
    printf("%d\n",dp[x]==inf ? -1 : dp[x]);
}
