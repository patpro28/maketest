#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,x; scanf("%d%d",&n,&x); const int MOD=1000000007;
    vector<int> dp(x+1,0); dp[0]=1;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a);
        for(int s=a;s<=x;++s) { dp[s]+=dp[s-a]; if(dp[s]>=MOD) dp[s]-=MOD; }
    }
    printf("%d\n",dp[x]);
}
