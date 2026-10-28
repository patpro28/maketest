#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>

using ll = long long;

// These references do not use the binary segment-tree graph of the solutions.
struct Successor {
    std::vector<int> parent;
    explicit Successor(int n) : parent(n + 2) { std::iota(parent.begin(),parent.end(),0); }
    int find(int u) {
        int root=u;
        while (parent[root]!=root) root=parent[root];
        while (parent[u]!=u) { int v=parent[u]; parent[u]=root; u=v; }
        return root;
    }
    void erase(int u) { parent[u]=find(u+1); }
};

struct Rule { int l,r,a,b; ll c; };
void shortest(int kind) {
    int n,q,s,t=0; std::cin>>n>>q>>s;
    if (kind==3) std::cin>>t;
    std::vector<Rule> rules(q);
    std::vector<std::vector<int>> outgoing(n+1);
    for (int i=0;i<q;++i) {
        auto &rule=rules[i];
        if (kind==1) {
            int u; std::cin>>u>>rule.a>>rule.b>>rule.c;
            rule.l=rule.r=u; outgoing[u].push_back(i);
        } else std::cin>>rule.l>>rule.r>>rule.a>>rule.b>>rule.c;
    }
    int block_size=std::max(1,int(std::sqrt(q+1)));
    std::vector<int> order(q), maximum((q+block_size-1)/block_size,0);
    std::iota(order.begin(),order.end(),0);
    std::sort(order.begin(),order.end(),[&](int x,int y) { return rules[x].l<rules[y].l; });
    std::vector<bool> active(q,true);
    if (kind==3) for (int i=0;i<q;++i)
        maximum[i/block_size]=std::max(maximum[i/block_size],rules[order[i]].r);
    using Offer=std::tuple<ll,int,int>;
    std::priority_queue<Offer,std::vector<Offer>,std::greater<Offer>> offers;
    offers.push({0,s,s});
    std::vector<ll> dist(n+1,-1);
    Successor next(n);
    auto activate=[&](int id,ll d) {
        const auto &rule=rules[id];
        active[id]=false; offers.push({d+rule.c,rule.a,rule.b});
    };
    while (!offers.empty()) {
        auto [d,l,r]=offers.top(); offers.pop();
        int u=next.find(l);
        while (u<=r) {
            dist[u]=d; next.erase(u);
            if (kind==1) {
                for (int id:outgoing[u]) activate(id,d);
            } else {
                // Interval stabbing by square-root decomposition, deleting each rule once.
                for (int b=0;b<int(maximum.size());++b) {
                    int begin=b*block_size, end=std::min(q,begin+block_size);
                    if (rules[order[begin]].l>u) break;
                    if (maximum[b]<u) continue;
                    for (int j=begin;j<end && rules[order[j]].l<=u;++j) {
                        int id=order[j];
                        if (active[id] && rules[id].r>=u) activate(id,d);
                    }
                    maximum[b]=0;
                    for (int j=begin;j<end;++j) if (active[order[j]])
                        maximum[b]=std::max(maximum[b],rules[order[j]].r);
                }
            }
            u=next.find(u);
        }
    }
    if (kind==3) std::cout<<dist[t]<<'\n';
    else for (int i=1;i<=n;++i) std::cout<<dist[i]<<(i==n?'\n':' ');
}

void scheduling() {
    int n,q; std::cin>>n>>q;
    std::vector<ll> duration(n+1);
    for (int i=1;i<=n;++i) std::cin>>duration[i];
    std::vector<int> head(n+1,-1),degree(n+1),to,next;
    auto node=[&]() { head.push_back(-1); degree.push_back(0); return int(head.size())-1; };
    auto edge=[&](int u,int v) {
        to.push_back(v); next.push_back(head[u]); head[u]=int(to.size())-1; ++degree[v];
    };
    int levels=1;
    while ((1<<levels)<=n) ++levels;
    std::vector<std::vector<int>> id(levels);
    id[0].resize(n+1);
    std::iota(id[0].begin(),id[0].end(),0);
    // Overlapping power-of-two intervals, as in a sparse table.
    for (int k=1;k<levels;++k) {
        int length=1<<k,half=length/2;
        id[k].resize(n-length+2);
        for (int l=1;l+length-1<=n;++l) {
            id[k][l]=node();
            edge(id[k-1][l],id[k][l]); edge(id[k-1][l+half],id[k][l]);
        }
    }
    for (int i=0;i<q;++i) {
        int l,r,u; std::cin>>l>>r>>u;
        int k=31-__builtin_clz(unsigned(r-l+1));
        edge(id[k][l],u);
        if (r-(1<<k)+1!=l) edge(id[k][r-(1<<k)+1],u);
    }
    std::vector<ll> finish(head.size());
    std::vector<int> queue;
    for (int i=1;i<int(head.size());++i) if (!degree[i]) queue.push_back(i);
    ll answer=0;
    for (size_t at=0;at<queue.size();++at) {
        int u=queue[at];
        if (u<=n) { finish[u]+=duration[u]; answer=std::max(answer,finish[u]); }
        for (int e=head[u];e!=-1;e=next[e]) {
            int v=to[e]; finish[v]=std::max(finish[v],finish[u]);
            if (--degree[v]==0) queue.push_back(v);
        }
    }
    std::cout<<(queue.size()==head.size()-1?answer:-1)<<'\n';
}

int main(int argc,char **argv) {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    if (argc!=2) return 1;
    int kind=std::atoi(argv[1]);
    if (kind==2) scheduling(); else shortest(kind);
}
