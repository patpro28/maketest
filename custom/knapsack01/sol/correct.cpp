#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int n,x; scanf("%d%d",&n,&x); vector<char> dp(x+1,false); dp[0]=true;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a);
        for(int s=x;s>=a;--s) dp[s]=dp[s] || dp[s-a];
    }
    puts(dp[x] ? "YES" : "NO");
}
