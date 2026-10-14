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
    int n; scanf("%d",&n); vector<int> a(n); int sum=0;
    for(int &v:a) { scanf("%d",&v); sum+=v; }
    int need=n/2; vector<vector<char>> dp(need+1,vector<char>(sum+1,false)); dp[0][0]=true;
    int seen=0;
    for(int v:a) {
        ++seen;
        for(int k=min(need,seen);k>=1;--k) for(int s=sum;s>=v;--s) dp[k][s]=dp[k][s] || dp[k-1][s-v];
    }
    int answer=sum;
    for(int s=0;s<=sum;++s) if(dp[need][s]) answer=min(answer,abs(sum-2*s));
    printf("%d\n",answer);
}
