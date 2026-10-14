// Independent full-size references for KNAPSACK20..29 (28 uses Python big integers).
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
constexpr long long INF=1LL<<60;
constexpr long long NEG=-(1LL<<60);
constexpr int MOD=1000000007;

void damage() {
    int n,h; scanf("%d%d",&n,&h); vector<long long> c(n),a(n);
    for(int i=0;i<n;++i) scanf("%lld%lld",&c[i],&a[i]);
    vector<long long> dist(h+1,INF); dist[0]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> heap;
    heap.push({0,0});
    while(!heap.empty()) {
        auto current=heap.top(); heap.pop(); if(current.first!=dist[current.second]) continue;
        if(current.second==h) break;
        for(int i=0;i<n;++i) {
            int to=int(min<long long>(h,current.second+a[i])); long long candidate=current.first+c[i];
            if(candidate<dist[to]) { dist[to]=candidate; heap.push({candidate,to}); }
        }
    }
    printf("%lld\n",dist[h]);
}

void optimal_coins() {
    int n,x; scanf("%d%d",&n,&x); vector<int> a(n); for(int &v:a) scanf("%d",&v);
    vector<int> shortest(x+1,-1); shortest[0]=0; queue<int> q; q.push(0);
    while(!q.empty()) {
        int s=q.front(); q.pop();
        for(int v:a) if(s+v<=x && shortest[s+v]<0) { shortest[s+v]=shortest[s]+1; q.push(s+v); }
    }
    if(shortest[x]<0) { puts("-1 0"); return; }
    // Any submultiset of a globally optimal solution is globally optimal for its sum.
    vector<int> ways(x+1,0); ways[0]=1;
    for(int v:a) for(int s=v;s<=x;++s) if(shortest[s-v]>=0 && shortest[s]==shortest[s-v]+1) {
        ways[s]+=ways[s-v]; if(ways[s]>=MOD) ways[s]-=MOD;
    }
    printf("%d %d\n",shortest[x],ways[x]);
}

void average() {
    int n,k,t; scanf("%d%d%d",&n,&k,&t); int target=k*t;
    vector<vector<int>> dp(k+1,vector<int>(target+1,0)); dp[0][0]=1;
    for(int i=0;i<n;++i) {
        int a; scanf("%d",&a); vector<vector<int>> next(k+1,vector<int>(target+1,0));
        for(int used=0;used<=k;++used) for(int s=0;s<=target;++s) if(dp[used][s]) {
            for(int copies=0;used+copies<=k && s+copies*a<=target;++copies) {
                int &value=next[used+copies][s+copies*a]; value+=dp[used][s]; if(value>=MOD) value-=MOD;
            }
        }
        dp.swap(next);
    }
    printf("%d\n",dp[k][target]);
}

vector<int> robot_distances() {
    vector<int> d(1001,-1); d[1]=0; queue<int> q; q.push(1);
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int x=1;x<=u;++x) { int v=u+u/x; if(v<=1000 && d[v]<0) { d[v]=d[u]+1; q.push(v); } }
    }
    return d;
}

void robots() {
    int n,k; scanf("%d%d",&n,&k); auto d=robot_distances(); vector<int> costs(n); vector<long long> values(n);
    for(int i=0;i<n;++i) { int b; scanf("%d%lld",&b,&values[i]); costs[i]=d[b]+1; }
    vector<long long> exact(k+1,NEG); exact[0]=0;
    for(int s=0;s<=k;++s) if(exact[s]!=NEG) for(int i=0;i<n;++i) if(s+costs[i]<=k) exact[s+costs[i]]=max(exact[s+costs[i]],exact[s]+values[i]);
    printf("%lld\n",*max_element(exact.begin(),exact.end()));
}

void coupon() {
    int n,w; scanf("%d%d",&n,&w); vector<int> costs(n); vector<long long> values(n);
    for(int i=0;i<n;++i) scanf("%d%lld",&costs[i],&values[i]);
    vector<long long> normal(w+1,0);
    for(int s=0;s<=w;++s) for(int i=0;i<n;++i) if(s>=costs[i]) normal[s]=max(normal[s],normal[s-costs[i]]+values[i]);
    long long answer=-1;
    // Fix the discounted product; every other product is paid at the normal price.
    for(int i=0;i<n;++i) if(costs[i]/2<=w) answer=max(answer,values[i]+normal[w-costs[i]/2]);
    printf("%lld\n",answer);
}

void resources() {
    int n,x,y; scanf("%d%d%d",&n,&x,&y); vector<int> a(n),b(n); vector<long long> values(n);
    for(int i=0;i<n;++i) scanf("%d%d%lld",&a[i],&b[i],&values[i]);
    vector<vector<long long>> exact(x+1,vector<long long>(y+1,NEG)); exact[0][0]=0; long long answer=0;
    for(int s=0;s<=x;++s) for(int t=0;t<=y;++t) if(exact[s][t]!=NEG) {
        answer=max(answer,exact[s][t]);
        for(int i=0;i<n;++i) if(s+a[i]<=x && t+b[i]<=y) exact[s+a[i]][t+b[i]]=max(exact[s+a[i]][t+b[i]],exact[s][t]+values[i]);
    }
    printf("%lld\n",answer);
}

void factories() {
    int n,w; scanf("%d%d",&n,&w); vector<long long> dp(w+1,NEG); dp[0]=0;
    for(int i=0;i<n;++i) {
        int fee,c; long long value; scanf("%d%d%lld",&fee,&c,&value); auto previous=dp;
        // Explicit multiplicity optimization using prefix maxima in each residue class.
        for(int r=0;r<c && r<=w;++r) {
            long long best=NEG;
            for(int j=1;fee+r+j*c<=w;++j) {
                int source=r+(j-1)*c;
                if(previous[source]!=NEG) best=max(best,previous[source]-1LL*(j-1)*value);
                if(best!=NEG) dp[fee+r+j*c]=max(dp[fee+r+j*c],best+1LL*j*value);
            }
        }
    }
    printf("%lld\n",*max_element(dp.begin(),dp.end()));
}

void machines() {
    int n; scanf("%d",&n); vector<pair<int,int>> a(n); int limit=0;
    for(auto &p:a) { scanf("%d%d",&p.first,&p.second); limit=max(limit,p.first); }
    sort(a.begin(),a.end()); vector<int> dp(limit+1,0); dp[0]=1; int answer=0;
    // Designate the last USED model in a fixed total order, instead of strength groups.
    for(auto p:a) {
        for(int s=p.second;s<=limit;++s) { dp[s]+=dp[s-p.second]; if(dp[s]>=MOD) dp[s]-=MOD; }
        for(int s=0;s<=p.first-p.second;++s) { answer+=dp[s]; if(answer>=MOD) answer-=MOD; }
    }
    printf("%d\n",answer);
}

void rails() {
    int n,q; scanf("%d%d",&n,&q); vector<int> a(n); for(int &v:a) scanf("%d",&v);
    // Any available length may be the modulus; use a larger one than the main solution.
    int modulus=1; for(int v:a) if(v<=10000) modulus=max(modulus,v);
    vector<long long> dist(modulus,INF); dist[0]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> heap; heap.push({0,0});
    while(!heap.empty()) {
        auto current=heap.top(); heap.pop(); if(current.first!=dist[current.second]) continue;
        for(int v:a) { int to=(current.second+v)%modulus; long long candidate=current.first+v; if(candidate<dist[to]) { dist[to]=candidate; heap.push({candidate,to}); } }
    }
    for(int i=0;i<q;++i) { long long x; scanf("%lld",&x); puts(dist[x%modulus]<=x ? "YES" : "NO"); }
}

int main(int argc,char **argv) {
    if(argc!=2) return 1;
    switch(atoi(argv[1])) {
        case 20: damage(); break;
        case 21: optimal_coins(); break;
        case 22: average(); break;
        case 23: robots(); break;
        case 24: coupon(); break;
        case 25: resources(); break;
        case 26: factories(); break;
        case 27: machines(); break;
        case 29: rails(); break;
        default: return 1;
    }
}
