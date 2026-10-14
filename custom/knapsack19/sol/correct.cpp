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
    int n,w; scanf("%d%d",&n,&w); vector<vector<int>> children(n); vector<int> cost(n); vector<long long> value(n);
    for(int i=0;i<n;++i) { int p; scanf("%d%d%lld",&p,&cost[i],&value[i]); if(p) children[p-1].push_back(i); }
    const long long NEG=-(1LL<<60);
    function<vector<long long>(int)> dfs=[&](int u) {
        vector<long long> dp(w+1,NEG);
        if(cost[u]>w) return dp;
        dp[cost[u]]=value[u];
        for(int v:children[u]) {
            auto child=dfs(v); auto next=dp;
            for(int a=cost[u];a<=w;++a) if(dp[a]!=NEG) {
                for(int b=1;a+b<=w;++b) if(child[b]!=NEG) next[a+b]=max(next[a+b],dp[a]+child[b]);
            }
            dp.swap(next);
        }
        return dp;
    };
    auto dp=dfs(0); printf("%lld\n",max(0LL,*max_element(dp.begin(),dp.end())));
}
