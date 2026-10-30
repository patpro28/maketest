#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
const ll BAD=numeric_limits<ll>::lowest()/3;
using Table=vector<vector<ll>>;
Table join(const Table& a,const Table& b) {
    int n=int(a.size());Table c(n,vector<ll>(n,BAD));
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) for(int k=0;k<n;++k)
        if(a[i][k]!=BAD && b[k][j]!=BAD) c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
    return c;
}
vector<ll> advance(const vector<ll>& f,const Table& a) {
    int n=int(f.size());vector<ll> g(n,BAD);
    for(int j=0;j<n;++j) for(int i=0;i<n;++i)
        if(f[i]!=BAD && a[i][j]!=BAD) g[j]=max(g[j],f[i]+a[i][j]);
    return g;
}
void walk() {
    int n,m,s,t;ll k;cin>>n>>m>>s>>t>>k;--s;--t;
    Table a(n,vector<ll>(n,BAD));
    struct Edge {int u,v;ll w;};vector<Edge> edges;
    for(int i=0;i<m;++i) {int u,v;ll w;cin>>u>>v>>w;--u;--v;a[u][v]=max(a[u][v],w);edges.push_back({u,v,w});}
    vector<ll> f(n,BAD);f[s]=0;ll steps=k;
    while(steps) {if(steps%2)f=advance(f,a);steps/=2;if(steps)a=join(a,a);}
    if(k<=1000) {
        vector<ll> slow(n,BAD);slow[s]=0;
        for(ll d=0;d<k;++d) {
            vector<ll> next(n,BAD);
            for(auto e:edges) if(slow[e.u]!=BAD) next[e.v]=max(next[e.v],slow[e.u]+e.w);
            slow=next;
        }
        assert(slow==f);
    }
    if(f[t]==BAD)cout<<"IMPOSSIBLE\n";else cout<<f[t]<<'\n';
}
void schedule() {
    int p;ll d;cin>>p>>d;vector<array<ll,3>> score(p);
    for(auto& row:score)for(ll& x:row)cin>>x;
    auto one_day=[&](const Table& input,const array<ll,3>& w) {
        Table out(16,vector<ll>(16,BAD));
        for(int start=0;start<16;++start) for(int state=0;state<16;++state) if(input[start][state]!=BAD) {
            int older=state/4,last=state%4;
            for(int job=0;job<=3;++job) {
                if(job && (job==last || (older && last)))continue;
                int to=last*4+job;ll gain=job?w[job-1]:0;
                out[start][to]=max(out[start][to],input[start][state]+gain);
            }
        }
        return out;
    };
    Table cycle(16,vector<ll>(16,BAD)),prefix;
    for(int i=0;i<16;++i)cycle[i][i]=0;
    prefix=cycle;int remainder=int(d%p);
    for(int i=0;i<p;++i) {cycle=one_day(cycle,score[i]);if(i<remainder)prefix=one_day(prefix,score[i]);}
    vector<ll> f(16,BAD);f[0]=0;ll times=d/p;
    while(times) {if(times%2)f=advance(f,cycle);times/=2;if(times)cycle=join(cycle,cycle);}
    f=advance(f,prefix);ll answer=*max_element(f.begin(),f.end());
    if(d<=2000) {
        Table current(16,vector<ll>(16,BAD));current[0][0]=0;
        for(ll day=0;day<d;++day)current=one_day(current,score[day%p]);
        assert(answer==*max_element(current[0].begin(),current[0].end()));
    }
    cout<<answer<<'\n';
}
struct RangeLnds {
    ll best[5][5]{};
};
int alphabet;
RangeLnds concatenate(const RangeLnds& a,const RangeLnds& b) {
    RangeLnds c;
    for(int l=0;l<alphabet;++l)for(int r=l;r<alphabet;++r)for(int split=l;split<=r;++split)
        c.best[l][r]=max(c.best[l][r],a.best[l][split]+b.best[split][r]);
    return c;
}
void compressed() {
    int n;cin>>n>>alphabet;
    vector<RangeLnds> dp(n+1);vector<ll> length(n+1);
    vector<vector<int>> expanded(n+1);ll stored=0;
    for(int i=1;i<=n;++i) {
        int type,u=0,v=0,x=0;ll copies=0;cin>>type;
        if(type==1) {
            cin>>x;--x;length[i]=1;
            for(int l=0;l<alphabet;++l)for(int r=l;r<alphabet;++r)dp[i].best[l][r]=(l<=x && x<=r);
        } else if(type==2) {
            cin>>u>>v;length[i]=length[u]+length[v];dp[i]=concatenate(dp[u],dp[v]);
        } else {
            cin>>u>>copies;length[i]=length[u]*copies;
            RangeLnds base=dp[u];ll k=copies;
            while(k) {if(k%2)dp[i]=concatenate(dp[i],base);k/=2;if(k)base=concatenate(base,base);}
        }
        bool can_expand=length[i]<=1000 && stored+length[i]<=3000000;
        if(type==2)can_expand &= ll(expanded[u].size())==length[u] && ll(expanded[v].size())==length[v];
        if(type==3 && copies)can_expand &= ll(expanded[u].size())==length[u];
        if(can_expand) {
            if(type==1)expanded[i]={x};
            else if(type==2) {expanded[i]=expanded[u];expanded[i].insert(expanded[i].end(),expanded[v].begin(),expanded[v].end());}
            else if(length[u])for(ll j=0;j<copies;++j)expanded[i].insert(expanded[i].end(),expanded[u].begin(),expanded[u].end());
            stored+=length[i];vector<int> tails;
            for(int value:expanded[i]) {
                auto it=upper_bound(tails.begin(),tails.end(),value);
                if(it==tails.end())tails.push_back(value);else *it=value;
            }
            assert(ll(tails.size())==dp[i].best[0][alphabet-1]);
        }
        cout<<dp[i].best[0][alphabet-1]<<'\n';
    }
}
struct Transfer3 {ll value[3][3];};
void positions() {
    int n,q;cin>>n>>q;vector<ll>a(n);for(ll& x:a)cin>>x;
    const int width=320;int blocks=(n+width-1)/width;vector<Transfer3> cache(blocks);
    auto rebuild=[&](int block) {
        for(int basis=0;basis<3;++basis) {
            array<ll,3> f{BAD,BAD,BAD};f[basis]=0;
            for(int i=block*width;i<min(n,(block+1)*width);++i)
                f={f[1],f[2],max(f[2],f[0]==BAD?BAD:f[0]+a[i])};
            for(int j=0;j<3;++j)cache[block].value[j][basis]=f[j];
        }
    };
    for(int b=0;b<blocks;++b)rebuild(b);
    for(int op=0;op<q;++op) {
        int type,l;ll r;cin>>type>>l>>r;--l;
        if(type==1) {a[l]=r;rebuild(l/width);continue;}
        array<ll,3> f{0,0,0};int i=l;
        while(i<int(r)) {
            if(i%width==0 && i+width<=int(r)) {
                array<ll,3> g{BAD,BAD,BAD};
                for(int to=0;to<3;++to)for(int from=0;from<3;++from)
                    if(cache[i/width].value[to][from]!=BAD)g[to]=max(g[to],cache[i/width].value[to][from]+f[from]);
                f=g;i+=width;
            } else {f={f[1],f[2],max(f[2],f[0]+a[i])};++i;}
        }
        if(r-l<=12) {
            ll best=0;int len=int(r)-l;
            for(int mask=0;mask<(1<<len);++mask) {
                if((mask&(mask<<1)) || (mask&(mask<<2)))continue;
                ll sum=0;for(int j=0;j<len;++j)if(mask>>j&1)sum+=a[l+j];best=max(best,sum);
            }
            assert(best==f[2]);
        }
        cout<<f[2]<<'\n';
    }
}
struct Transfer2 {ll value[2][2];};
void independent_tree() {
    int n,q;cin>>n>>q;vector<ll>w(n+1),f0(n+1),f1(n+1),g0(n+1),g1(n+1);
    for(int i=1;i<=n;++i)cin>>w[i];vector<vector<int>>adj(n+1);
    for(int i=1;i<n;++i){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    int root=n;
    vector<int>parent(n+1),order{root},size(n+1,1),heavy(n+1),chain_id(n+1),offset(n+1);
    for(int i=0;i<n;++i){int u=order[i];for(int v:adj[u])if(v!=parent[u]){parent[v]=u;order.push_back(v);}}
    for(int i=n-1;i>=0;--i) {
        int u=order[i];f1[u]=w[u];
        for(int v:adj[u])if(parent[v]==u){size[u]+=size[v];f0[u]+=max(f0[v],f1[v]);f1[u]+=f0[v];if(!heavy[u] || size[v]>size[heavy[u]])heavy[u]=v;}
        g0[u]=f0[u]-max(f0[heavy[u]],f1[heavy[u]]);g1[u]=f1[u]-f0[heavy[u]];
    }
    vector<vector<int>>paths;
    for(int u:order)if(!parent[u] || heavy[parent[u]]!=u) {
        paths.push_back({});int id=int(paths.size())-1;
        for(int v=u;v;v=heavy[v]){chain_id[v]=id;offset[v]=int(paths[id].size());paths[id].push_back(v);}
    }
    const int width=256;vector<vector<Transfer2>>cache(paths.size());
    for(int id=0;id<int(paths.size());++id)cache[id].resize((paths[id].size()+width-1)/width);
    auto rebuild=[&](int id,int block) {
        const auto& path=paths[id];
        for(int basis=0;basis<2;++basis) {
            array<ll,2>f{BAD,BAD};f[basis]=0;
            for(int i=min(int(path.size()),(block+1)*width)-1;i>=block*width;--i) {
                int u=path[i];f={g0[u]+max(f[0],f[1]),f[0]==BAD?BAD:g1[u]+f[0]};
            }
            for(int j=0;j<2;++j)cache[id][block].value[j][basis]=f[j];
        }
    };
    auto evaluate=[&](int id) {
        array<ll,2>f{0,0};
        for(int block=int(cache[id].size())-1;block>=0;--block) {
            array<ll,2>next{BAD,BAD};
            for(int to=0;to<2;++to)for(int from=0;from<2;++from)
                if(cache[id][block].value[to][from]!=BAD)next[to]=max(next[to],cache[id][block].value[to][from]+f[from]);
            f=next;
        }
        return f;
    };
    for(int id=0;id<int(paths.size());++id)for(int b=0;b<int(cache[id].size());++b)rebuild(id,b);
    for(int op=0;op<q;++op) {
        int u;ll x;cin>>u>>x;g1[u]+=x-w[u];w[u]=x;
        while(u) {
            int id=chain_id[u],head=paths[id][0];ll old0=f0[head],old1=f1[head];
            rebuild(id,offset[u]/width);auto now=evaluate(id);f0[head]=now[0];f1[head]=now[1];
            int p=parent[head];if(!p || (old0==now[0] && old1==now[1]))break;
            g0[p]+=max(now[0],now[1])-max(old0,old1);g1[p]+=now[0]-old0;u=p;
        }
        ll answer=max(f0[root],f1[root]);
        if(n<=12) {
            ll best=0;
            for(int mask=0;mask<(1<<n);++mask) {
                bool valid=true;ll value=0;
                for(int v=1;v<=n;++v)if(mask>>(v-1)&1){value+=w[v];if(parent[v] && (mask>>(parent[v]-1)&1)){valid=false;break;}}
                if(valid)best=max(best,value);
            }
            assert(best==answer);
        }
        cout<<answer<<'\n';
    }
}
int main(int argc,char** argv) {
    ios::sync_with_stdio(false);cin.tie(nullptr);
    assert(argc==2);int kind=stoi(argv[1]);
    if(kind==1)walk();if(kind==2)schedule();if(kind==3)compressed();if(kind==4)positions();if(kind==5)independent_tree();
}
