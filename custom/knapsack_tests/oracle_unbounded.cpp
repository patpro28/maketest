// Independent references: paths on sums, BFS, and inverse generating polynomial.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

void maximize(bool exact) {
    int n,capacity; scanf("%d%d",&n,&capacity);
    vector<int> weights(n); vector<long long> values(n);
    for(int i=0;i<n;++i) scanf("%d%lld",&weights[i],&values[i]);
    // A path edge adds one object, so every path represents a multiset of objects.
    vector<long long> best(capacity+1,-1); best[0]=0;
    for(int sum=0;sum<=capacity;++sum) if(best[sum]>=0) {
        for(int i=0;i<n;++i) if(sum+weights[i]<=capacity) {
            best[sum+weights[i]]=max(best[sum+weights[i]],best[sum]+values[i]);
        }
    }
    printf("%lld\n",exact ? best[capacity] : *max_element(best.begin(),best.end()));
}

void shortest(bool feasibility) {
    int n,target; scanf("%d%d",&n,&target); vector<int> a(n);
    for(int &v:a) scanf("%d",&v);
    vector<int> distance(target+1,-1); queue<int> pending;
    distance[0]=0; pending.push(0);
    while(!pending.empty()) {
        int s=pending.front(); pending.pop();
        for(int v:a) if(s+v<=target && distance[s+v]<0) {
            distance[s+v]=distance[s]+1; pending.push(s+v);
        }
    }
    if(feasibility) puts(distance[target]>=0 ? "YES" : "NO");
    else printf("%d\n",distance[target]);
}

void combinations() {
    int n,target; scanf("%d%d",&n,&target); vector<int> a(n);
    for(int &v:a) scanf("%d",&v);
    constexpr int MOD=1000000007;
    // Q(z)=product(1-z^a). The answer series F satisfies Q(z)*F(z)=1.
    vector<int> q(target+1,0); q[0]=1;
    for(int v:a) for(int s=target;s>=v;--s) {
        q[s]-=q[s-v]; if(q[s]<0) q[s]+=MOD;
    }
    vector<pair<int,int>> terms;
    for(int k=1;k<=target;++k) if(q[k]) terms.emplace_back(k,q[k]);
    vector<int> f(target+1,0); f[0]=1;
    for(int s=1;s<=target;++s) {
        long long sum=0;
        for(auto term:terms) {
            if(term.first>s) break;
            sum+=1LL*term.second*f[s-term.first]%MOD;
            if(sum>=MOD) sum-=MOD;
        }
        f[s]=sum==0 ? 0 : MOD-sum;
    }
    printf("%d\n",f[target]);
}

int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int problem=atoi(argv[1]);
    if(problem==5 || problem==9) maximize(problem==9);
    else if(problem==6 || problem==7) shortest(problem==6);
    else if(problem==8) combinations();
    else return 1;
}
