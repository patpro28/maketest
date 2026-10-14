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
    int n; scanf("%d",&n); vector<pair<int,int>> a(n); int limit=0;
    for(auto &p:a) { scanf("%d%d",&p.first,&p.second); limit=max(limit,p.first); }
    sort(a.begin(),a.end()); const int MOD=1000000007; vector<int> dp(limit+1,0); dp[0]=1; int answer=0;
    for(int begin=0;begin<n;) {
        int end=begin; while(end<n && a[end].first==a[begin].first) ++end;
        int strength=a[begin].first,before=0,after=0;
        for(int s=0;s<=strength;++s) { before+=dp[s]; if(before>=MOD) before-=MOD; }
        for(int i=begin;i<end;++i) for(int s=a[i].second;s<=limit;++s) { dp[s]+=dp[s-a[i].second]; if(dp[s]>=MOD) dp[s]-=MOD; }
        for(int s=0;s<=strength;++s) { after+=dp[s]; if(after>=MOD) after-=MOD; }
        answer=int((answer+1LL*after-before+MOD)%MOD); begin=end;
    }
    printf("%d\n",answer);
}
