#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using Key = uint64_t;
const int M1 = 1000000007, M2 = 1000000009, BASE = 911382323;
struct Hash {
    vector<int> a,b,p,q;
    explicit Hash(const vector<ll>& s):a(s.size()+1),b(s.size()+1),p(s.size()+1,1),q(s.size()+1,1) {
        for (int i=0;i<(int)s.size();++i) {
            ll x=(s[i]%M1+M1)%M1, y=(s[i]%M2+M2)%M2;
            a[i+1]=(a[i]*(ll)BASE+x)%M1; b[i+1]=(b[i]*(ll)BASE+y)%M2;
            p[i+1]=p[i]*(ll)BASE%M1; q[i+1]=q[i]*(ll)BASE%M2;
        }
    }
    explicit Hash(const string& s):Hash(vector<ll>(s.begin(),s.end())) {}
    Key get(int l,int r) const { // Half-open interval [l,r).
        ll x=(a[r]-a[l]*(ll)p[r-l]%M1+M1)%M1;
        ll y=(b[r]-b[l]*(ll)q[r-l]%M2+M2)%M2;
        return (Key(x)<<32)|Key(y);
    }
};
struct KeyHash {
    size_t operator()(Key x) const { // Deterministic mixing; generation remains reproducible.
        x+=0x9e3779b97f4a7c15ULL;x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
        x=(x^(x>>27))*0x94d049bb133111ebULL;return x^(x>>31);
    }
};
struct Node {int len=0;Key f=0,b=0;};
struct Tree {
    int size=1;vector<Node>t;vector<int>p,q;
    Key append(Key a,Key b,int len)const{
        ll x=((a>>32)*p[len]+(b>>32))%M1;
        ll y=((a&0xffffffffULL)*q[len]+(b&0xffffffffULL))%M2;
        return (Key(x)<<32)|Key(y);
    }
    Node join(Node a,Node b)const{return {a.len+b.len,append(a.f,b.f,b.len),append(b.b,a.b,a.len)};}
    explicit Tree(const string&s):p(s.size()+1,1),q(s.size()+1,1){
        while(size<(int)s.size())size*=2;
        t.resize(2*size);
        for(int i=1;i<=(int)s.size();++i){p[i]=p[i-1]*(ll)BASE%M1;q[i]=q[i-1]*(ll)BASE%M2;}
        for(int i=0;i<(int)s.size();++i){Key x=(Key(s[i])<<32)|Key(s[i]);t[size+i]={1,x,x};}
        for(int i=size-1;i;--i)t[i]=join(t[i*2],t[i*2+1]);
    }
    void set(int i,char c){i+=size;Key x=(Key(c)<<32)|Key(c);t[i]={1,x,x};while(i>>=1)t[i]=join(t[i*2],t[i*2+1]);}
    Node get(int l,int r)const{
        Node a,b;for(l+=size,r+=size;l<r;l>>=1,r>>=1){if(l&1)a=join(a,t[l++]);if(r&1)b=join(t[--r],b);}return join(a,b);
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;string s;cin>>n>>q>>s;vector<vector<int>>g(n);
    for(int i=1;i<n;++i){int u,v;cin>>u>>v;--u;--v;g[u].push_back(v);g[v].push_back(u);}
    vector<int>par(n,-1),dep(n),sz(n,1),heavy(n,-1),order{0};
    for(int i=0;i<n;++i){int u=order[i];for(int v:g[u])if(v!=par[u]){par[v]=u;dep[v]=dep[u]+1;order.push_back(v);}}
    for(int i=n-1;i>0;--i){int u=order[i],p=par[u];sz[p]+=sz[u];if(heavy[p]==-1 || sz[u]>sz[heavy[p]])heavy[p]=u;}
    vector<int>head(n),pos(n);int timer=0;string base(n,' ');
    for(int u:order)if(par[u]==-1 || heavy[par[u]]!=u)for(int v=u;v!=-1;v=heavy[v]){head[v]=u;pos[v]=timer;base[timer++]=s[v];}
    Tree tree(base);
    auto path=[&](int u,int v){
        Node a,b;
        while(head[u]!=head[v]){
            if(dep[head[u]]>=dep[head[v]]){Node x=tree.get(pos[head[u]],pos[u]+1);swap(x.f,x.b);a=tree.join(a,x);u=par[head[u]];}
            else{b=tree.join(tree.get(pos[head[v]],pos[v]+1),b);v=par[head[v]];}
        }
        Node x=tree.get(min(pos[u],pos[v]),max(pos[u],pos[v])+1);if(dep[u]>dep[v])swap(x.f,x.b);
        return tree.join(tree.join(a,x),b);
    };
    while(q--){int u,v,x,y;cin>>u>>v>>x>>y;Node a=path(u-1,v-1),b=path(x-1,y-1);cout<<(a.len==b.len && a.f==b.f?"YES":"NO")<<'\n';}
}
