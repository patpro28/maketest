#include <bits/stdc++.h>
using namespace std;
struct Node {
    int first=-1,last=-1,a=-1,b=-1;
    long long path=0,diam=0;
};
int n,sz;
vector<int>tin,tout,depth,first,lg;
vector<long long>dep;
vector<vector<int>>rmq;
vector<Node>seg;
long long dist(int a,int b) {
    int l=first[a],r=first[b];
    if(l>r)swap(l,r);
    int k=lg[r-l+1];
    int u=rmq[k][l],v=rmq[k][r-(1<<k)+1];
    int w=depth[u]<depth[v]?u:v;
    return dep[a]+dep[b]-2*dep[w];
}
Node join(const Node &x,const Node &y) {
    if(x.first<0)return y;
    if(y.first<0)return x;
    Node z;
    z.first=x.first;
    z.last=y.last;
    z.path=x.path+y.path+dist(x.last,y.first);
    if(x.diam>=y.diam) {
        z.a=x.a;
        z.b=x.b;
        z.diam=x.diam;
    }
    else {
        z.a=y.a;
        z.b=y.b;
        z.diam=y.diam;
    }
    for(int u: {x.a,x.b})for(int v: {y.a,y.b}) {
        long long d=dist(u,v);
        if(d>z.diam) {
            z.diam=d;
            z.a=u;
            z.b=v;
        }
    }
    return z;
}
Node leaf(int u) {
    Node z;
    z.first=z.last=z.a=z.b=u;
    return z;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    string color;
    cin>>color;
    vector<vector<pair<int,int>>>g(n);
    for(int i=1; i<n; i++) {
        int u,v,c;
        cin>>u>>v>>c;
        --u;
        --v;
        g[u].push_back( {v,c});
        g[v].push_back( {u,c});
    }
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    dep.resize(n);
    first.resize(n);
    vector<int>par(n,-1),next(n),stack= {
        0
    },order,euler;
    tin[0]=0;
    order.push_back(0);
    first[0]=0;
    euler.push_back(0);
    while(!stack.empty()) {
        int u=stack.back();
        if(next[u]==(int)g[u].size()) {
            tout[u]=order.size();
            stack.pop_back();
            if(!stack.empty())euler.push_back(stack.back());
            continue;
        }
        auto [v,w]=g[u][next[u]++];
        if(v==par[u])continue;
        par[v]=u;
        depth[v]=depth[u]+1;
        dep[v]=dep[u]+w;
        tin[v]=order.size();
        order.push_back(v);
        first[v]=euler.size();
        euler.push_back(v);
        stack.push_back(v);
    }
    int m=euler.size();
    lg.resize(m+1);
    for(int i=2; i<=m; i++)lg[i]=lg[i/2]+1;
    rmq.push_back(euler);
    for(int k=1; (1<<k)<=m; k++) {
        rmq.push_back(vector<int>(m-(1<<k)+1));
        for(int i=0; i+(1<<k)<=m; i++) {
            int u=rmq[k-1][i],v=rmq[k-1][i+(1<<(k-1))];
            rmq[k][i]=depth[u]<depth[v]?u:v;
        }
    }
    sz=1;
    while(sz<n)sz*=2;
    seg.resize(2*sz);
    for(int u=0; u<n; u++)if(color[u]=='1')seg[sz+tin[u]]=leaf(u);
    for(int i=sz-1; i; i--)seg[i]=join(seg[i*2],seg[i*2+1]);
    int q;
    cin>>q;
    while(q--) {
        int t,u;
        cin>>t>>u;
        --u;
        if(t==1) {
            color[u]^=1;
            int p=sz+tin[u];
            seg[p]=color[u]=='1'?leaf(u):Node();
            while((p/=2))seg[p]=join(seg[p*2],seg[p*2+1]);
        }
        else {
            Node left,right;
            int l=sz+tin[u],r=sz+tout[u];
            while(l<r) {
                if(l&1)left=join(left,seg[l++]);
                if(r&1)right=join(seg[--r],right);
                l/=2;
                r/=2;
            }
            Node z=join(left,right);
            long long cycle=z.path+dist(z.first,z.last);
            cout<<cycle-(t==3?z.diam:0)<<'\n';
        }
    }
}
