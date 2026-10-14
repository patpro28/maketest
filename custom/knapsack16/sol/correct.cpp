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
    int n; scanf("%d",&n); vector<pair<int,int>> a(n); int bound=0;
    for(auto &p:a) { scanf("%d%d",&p.first,&p.second); bound=max(bound,p.first); }
    sort(a.begin(),a.end()); const int MOD=998244353;
    vector<int> dp(bound+1,0); dp[0]=1; int answer=0;
    for(auto [strength,weight]:a) {
        for(int s=0;s<=strength-weight;++s) { answer+=dp[s]; if(answer>=MOD) answer-=MOD; }
        for(int s=bound;s>=weight;--s) { dp[s]+=dp[s-weight]; if(dp[s]>=MOD) dp[s]-=MOD; }
    }
    printf("%d\n",answer);
}
