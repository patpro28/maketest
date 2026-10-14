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
    int n; scanf("%d",&n); array<int,10> c; for(int &v:c) scanf("%d",&v);
    vector<int> dp(n+1,-1); dp[0]=0;
    for(int s=1;s<=n;++s) for(int d=0;d<10;++d) if(s>=c[d] && dp[s-c[d]]>=0) dp[s]=max(dp[s],dp[s-c[d]]+1);
    int length=-1;
    for(int d=1;d<=9;++d) if(n>=c[d] && dp[n-c[d]]>=0) length=max(length,1+dp[n-c[d]]);
    if(length<0) { puts(n==c[0] ? "0" : "-1"); return 0; }
    string answer; int rest=n;
    for(int pos=0;pos<length;++pos) {
        for(int d=9;d>=(pos==0 ? 1 : 0);--d) if(rest>=c[d] && dp[rest-c[d]]==length-pos-1) {
            answer.push_back(char('0'+d)); rest-=c[d]; break;
        }
    }
    puts(answer.c_str());
}
