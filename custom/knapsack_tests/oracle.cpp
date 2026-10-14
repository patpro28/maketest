// Independent algorithms for large cases; small cases are also checked by enumeration.
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;

void tickets() {
    int n,x; scanf("%d%d",&n,&x);
    vector<int> p(n); vector<long long> c(n); int total=0; long long cost=0;
    for(int i=0;i<n;++i) { scanf("%lld%d",&c[i],&p[i]); total+=p[i]; cost+=c[i]; }
    if(total<x) { puts("-1"); return; }
    // Omit activities with at most total-X points, maximizing the saved cost.
    int cap=total-x; vector<long long> saved(cap+1,0);
    for(int i=0;i<n;++i) for(int s=cap;s>=p[i];--s) saved[s]=max(saved[s],saved[s-p[i]]+c[i]);
    printf("%lld\n",cost-saved[cap]);
}

void captain() {
    int n; scanf("%d",&n); map<int,vector<int>> groups; int limit=0;
    for(int i=0;i<n;++i) { int a,b; scanf("%d%d",&a,&b); groups[a].push_back(b); limit=max(limit,a); }
    const int MOD=998244353;
    vector<int> dp(limit+1,0); dp[0]=1; int answer=0;
    for(const auto &g:groups) {
        int before=0,after=0;
        for(int s=0;s<=g.first;++s) { before+=dp[s]; if(before>=MOD) before-=MOD; }
        for(int b:g.second) for(int s=limit;s>=b;--s) { dp[s]+=dp[s-b]; if(dp[s]>=MOD) dp[s]-=MOD; }
        for(int s=0;s<=g.first;++s) { after+=dp[s]; if(after>=MOD) after-=MOD; }
        // Count sets containing at least one member of the current strength group.
        answer=(answer+after-before+static_cast<long long>(MOD))%MOD;
    }
    printf("%d\n",answer);
}

void repaired() {
    int n,cap; scanf("%d%d",&n,&cap); vector<int> w(n); vector<long long> v(n);
    for(int i=0;i<n;++i) scanf("%d%lld",&w[i],&v[i]);
    vector<vector<long long>> prefix(n+1,vector<long long>(cap+1,0)),suffix=prefix;
    for(int i=0;i<n;++i) {
        prefix[i+1]=prefix[i];
        for(int s=w[i];s<=cap;++s) prefix[i+1][s]=max(prefix[i+1][s],prefix[i][s-w[i]]+v[i]);
    }
    for(int i=n-1;i>=0;--i) {
        suffix[i]=suffix[i+1];
        for(int s=w[i];s<=cap;++s) suffix[i][s]=max(suffix[i][s],suffix[i+1][s-w[i]]+v[i]);
    }
    long long answer=-1;
    for(int i=0;i<n;++i) if(w[i]/2<=cap) {
        int remaining=cap-w[i]/2;
        for(int s=0;s<=remaining;++s) answer=max(answer,prefix[i][s]+suffix[i+1][remaining-s]+v[i]);
    }
    printf("%lld\n",answer);
}

void kitchens() {
    int n; scanf("%d",&n); vector<int> t(n); for(int &v:t) scanf("%d",&v);
    // Normalize the three loads: no dimensions correspond to fixed kitchen labels.
    set<array<int,3>> states; states.insert({0,0,0});
    for(int v:t) {
        set<array<int,3>> next;
        for(auto a:states) for(int k=0;k<3;++k) {
            if(k && a[k]==a[k-1]) continue;
            auto b=a; b[k]+=v; sort(b.begin(),b.end()); next.insert(b);
        }
        states.swap(next);
    }
    int answer=1000000; for(auto a:states) answer=min(answer,a[2]); printf("%d\n",answer);
}

void skills() {
    int n,cap; scanf("%d%d",&n,&cap); vector<int> c(n); vector<long long> v(n); vector<vector<int>> children(n);
    for(int i=0;i<n;++i) { int p; scanf("%d%d%lld",&p,&c[i],&v[i]); if(p) children[p-1].push_back(i); }
    vector<int> order,end(n);
    function<void(int)> dfs=[&](int u) { int pos=int(order.size()); order.push_back(u); for(int ch:children[u]) dfs(ch); end[pos]=int(order.size()); };
    dfs(0);
    // In preorder, omitting a skill skips its whole subtree.
    vector<vector<long long>> dp(n+1,vector<long long>(cap+1,0));
    for(int i=n-1;i>=0;--i) for(int budget=0;budget<=cap;++budget) {
        int u=order[i]; dp[i][budget]=dp[end[i]][budget];
        if(c[u]<=budget) dp[i][budget]=max(dp[i][budget],v[u]+dp[i+1][budget-c[u]]);
    }
    printf("%lld\n",dp[0][cap]);
}

int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int id=atoi(argv[1]);
    if(id==13) tickets();
    else if(id==16) captain();
    else if(id==17) repaired();
    else if(id==18) kitchens();
    else if(id==19) skills();
    else return 1;
}
