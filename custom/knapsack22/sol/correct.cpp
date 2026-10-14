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
    int n,k,t; scanf("%d%d%d",&n,&k,&t); int target=k*t; const int MOD=1000000007;
    vector<vector<int>> dp(k+1,vector<int>(target+1,0)); dp[0][0]=1;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a);
        for(int count=1;count<=k;++count) for(int s=a;s<=target;++s) {
            dp[count][s]+=dp[count-1][s-a]; if(dp[count][s]>=MOD) dp[count][s]-=MOD;
        }
    }
    printf("%d\n",dp[k][target]);
}
