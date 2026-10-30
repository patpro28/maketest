#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using ll=long long;
struct RootedTree{
    int n;vector<vector<pair<int,int>>>adj;
    vector<int>parent,depth,mask,order,euler,tin,size;
    explicit RootedTree(int n,bool labels=false):n(n),adj(n+1),parent(n+1),depth(n+1),mask(n+1),tin(n+1),size(n+1,1){
        for(int i=1;i<n;++i){int u,v,b=0;cin>>u>>v;if(labels){char c;cin>>c;b=1<<(c-'a');}adj[u].push_back({v,b});adj[v].push_back({u,b});}
        order={1};
        for(int i=0;i<n;++i){int u=order[i];for(auto [v,b]:adj[u])if(v!=parent[u]){parent[v]=u;depth[v]=depth[u]+1;mask[v]=mask[u]^b;order.push_back(v);}}
        for(int i=n-1;i>0;--i)size[parent[order[i]]]+=size[order[i]];
        vector<int>pending{1};while(!pending.empty()){int u=pending.back();pending.pop_back();tin[u]=int(euler.size());euler.push_back(u);for(auto [v,b]:adj[u])if(parent[v]==u){(void)b;pending.push_back(v);}}
    }
};
struct ColorBag{
    map<int,int>count;ll total=0,pairs=0,triples=0;
    void add(int c,int copies){
        ll x=count[c];triples+=copies*(pairs-x*(total-x));pairs+=copies*(total-x);total+=copies;count[c]+=copies;
    }
};
void colors(){
    int n;cin>>n;vector<int>color(n+1);for(int u=1;u<=n;++u)cin>>color[u];RootedTree t(n);
    vector<unique_ptr<ColorBag>>bag(n+1);vector<ll>answer(n+1);
    for(int i=n-1;i>=0;--i){
        int u=t.order[i],big=0;
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u){(void)b;if(!big || bag[v]->count.size()>bag[big]->count.size())big=v;}
        if(big)bag[u]=std::move(bag[big]);else bag[u]=make_unique<ColorBag>();
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u && v!=big){(void)b;for(auto [c,f]:bag[v]->count)bag[u]->add(c,f);bag[v].reset();}
        bag[u]->add(color[u],1);answer[u]=bag[u]->triples;
    }
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
void top_colors(){
    int n,q;cin>>n>>q;vector<int>color(n+1),values;
    for(int u=1;u<=n;++u){cin>>color[u];values.push_back(color[u]);}
    sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());
    for(int u=1;u<=n;++u)color[u]=int(lower_bound(values.begin(),values.end(),color[u])-values.begin());
    RootedTree t(n);struct Query{int l,r,k,id;};vector<Query>queries;
    for(int i=0;i<q;++i){int u,k;cin>>u>>k;queries.push_back({t.tin[u],t.tin[u]+t.size[u],k,i});}
    const int width=450;
    sort(queries.begin(),queries.end(),[&](const Query&a,const Query&b){int x=a.l/width,y=b.l/width;return x!=y?x<y:(x%2?a.r>b.r:a.r<b.r);});
    vector<int>count(values.size()),freq(n+1),bucket_count(n/width+2);vector<ll>bucket_mass(n/width+2),answer(q);
    int distinct=0,maximum=0,left=0,right=0;
    auto change=[&](int position,int delta){
        int c=color[t.euler[position]],old=count[c];
        if(old){--freq[old];--bucket_count[old/width];bucket_mass[old/width]-=old;--distinct;}
        int now=(count[c]+=delta);
        if(now){++freq[now];++bucket_count[now/width];bucket_mass[now/width]+=now;++distinct;}
        maximum=max(maximum,now);while(maximum && !freq[maximum])--maximum;
    };
    for(auto query:queries){
        while(left>query.l)change(--left,1);while(right<query.r)change(right++,1);
        while(left<query.l)change(left++,-1);while(right>query.r)change(--right,-1);
        int remain=min(query.k,distinct);ll result=0;
        if(remain==distinct){answer[query.id]=right-left;continue;}
        for(int b=maximum/width;b>=0 && remain;--b){
            if(bucket_count[b]<=remain){remain-=bucket_count[b];result+=bucket_mass[b];}
            else for(int f=min(maximum,(b+1)*width-1);f>=max(1,b*width) && remain;--f){int take=min(remain,freq[f]);remain-=take;result+=ll(take)*f;}
        }
        answer[query.id]=result;
    }
    for(ll x:answer)cout<<x<<'\n';
}
void distances(){
    int n;cin>>n;vector<int>k(n+1);for(int u=1;u<=n;++u)cin>>k[u];RootedTree t(n);
    vector<unique_ptr<map<int,int>>>bag(n+1);vector<ll>answer(n+1);
    for(int i=n-1;i>=0;--i){
        int u=t.order[i],big=0;
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u){(void)b;if(!big || bag[v]->size()>bag[big]->size())big=v;}
        if(big)bag[u]=std::move(bag[big]);else bag[u]=make_unique<map<int,int>>();
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u && v!=big){
            (void)b;
            for(auto [d,count]:*bag[v]){auto it=bag[u]->find(2*t.depth[u]+k[u]-d);if(it!=bag[u]->end())answer[u]+=ll(count)*it->second;}
            for(auto [d,count]:*bag[v])(*bag[u])[d]+=count;bag[v].reset();
        }
        auto it=bag[u]->find(t.depth[u]+k[u]);if(it!=bag[u]->end())answer[u]+=it->second;
        ++(*bag[u])[t.depth[u]];
    }
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
struct Persistent{
    struct Node{int l=0,r=0;ll weight=0,sum=0;};
    vector<Node>pool{{}};
    int add(int old,int l,int r,int p,ll w,ll value){
        int id=int(pool.size());pool.push_back(pool[old]);pool[id].weight+=w;pool[id].sum+=w*value;
        if(l<r){int mid=(l+r)/2;if(p<=mid)pool[id].l=add(pool[old].l,l,mid,p,w,value);else pool[id].r=add(pool[old].r,mid+1,r,p,w,value);}
        return id;
    }
    int kth(int a,int b,int l,int r,ll k)const{
        if(l==r)return l;int mid=(l+r)/2;ll left=pool[pool[b].l].weight-pool[pool[a].l].weight;
        return k<=left?kth(pool[a].l,pool[b].l,l,mid,k):kth(pool[a].r,pool[b].r,mid+1,r,k-left);
    }
    pair<ll,ll>prefix(int a,int b,int l,int r,int p)const{
        if(r<=p)return {pool[b].weight-pool[a].weight,pool[b].sum-pool[a].sum};
        if(l>p)return {0,0};int mid=(l+r)/2;
        auto x=prefix(pool[a].l,pool[b].l,l,mid,p),y=prefix(pool[a].r,pool[b].r,mid+1,r,p);
        return {x.first+y.first,x.second+y.second};
    }
};
void balancing(){
    int n;cin>>n;vector<ll>a(n+1),w(n+1),values;
    for(int u=1;u<=n;++u){cin>>a[u]>>w[u];values.push_back(a[u]);}RootedTree t(n);
    sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());
    Persistent pst;pst.pool.reserve(22*n+1);vector<int>root(n+1);int m=int(values.size());
    for(int i=0;i<n;++i){int u=t.euler[i],p=int(lower_bound(values.begin(),values.end(),a[u])-values.begin());root[i+1]=pst.add(root[i],0,m-1,p,w[u],a[u]);}
    for(int u=1;u<=n;++u){
        int l=root[t.tin[u]],r=root[t.tin[u]+t.size[u]];ll total=pst.pool[r].weight-pst.pool[l].weight,sum=pst.pool[r].sum-pst.pool[l].sum;
        int p=pst.kth(l,r,0,m-1,(total+1)/2);ll median=values[p];auto [wl,sl]=pst.prefix(l,r,0,m-1,p);
        cout<<median*wl-sl+(sum-sl)-median*(total-wl)<<'\n';
    }
}
struct Treap{
    struct Node{int l=0,r=0,size=1,depth=0;uint64_t priority=0;};vector<Node>node;
    explicit Treap(int n):node(n+1){node[0].size=0;for(int u=1;u<=n;++u){uint64_t z=uint64_t(u)+0x9e3779b97f4a7c15ULL;z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;z=(z^(z>>27))*0x94d049bb133111ebULL;node[u].priority=z^(z>>31);}}
    void pull(int u){node[u].size=1+node[node[u].l].size+node[node[u].r].size;}
    bool less(int u,int v)const{return pair<int,int>{node[u].depth,u}<pair<int,int>{node[v].depth,v};}
    int rotate_right(int u){int v=node[u].l;node[u].l=node[v].r;node[v].r=u;pull(u);pull(v);return v;}
    int rotate_left(int u){int v=node[u].r;node[u].r=node[v].l;node[v].l=u;pull(u);pull(v);return v;}
    int insert(int root,int u){
        if(!root)return u;
        if(less(u,root)){node[root].l=insert(node[root].l,u);if(node[node[root].l].priority>node[root].priority)root=rotate_right(root);}
        else{node[root].r=insert(node[root].r,u);if(node[node[root].r].priority>node[root].priority)root=rotate_left(root);}
        pull(root);return root;
    }
    ll count(int root,int limit)const{
        ll answer=0;while(root){if(node[root].depth<=limit){answer+=node[node[root].l].size+1;root=node[root].r;}else root=node[root].l;}return answer;
    }
};
struct MaskBag{map<int,int>roots;vector<int>vertices;};
void passwords(){
    int n;cin>>n;vector<int>k(n+1);for(int u=1;u<=n;++u)cin>>k[u];RootedTree t(n,true);Treap tr(n);
    vector<unique_ptr<MaskBag>>bag(n+1);vector<ll>answer(n+1);
    auto insert=[&](MaskBag& b,int u){tr.node[u].l=tr.node[u].r=0;tr.node[u].size=1;tr.node[u].depth=t.depth[u];int& root=b.roots[t.mask[u]];root=tr.insert(root,u);b.vertices.push_back(u);};
    auto query=[&](const MaskBag& b,int ancestor,int u){
        int limit=2*t.depth[ancestor]+k[ancestor]-t.depth[u];ll result=0;
        for(int bit=-1;bit<10;++bit){int mask=t.mask[u]^(bit<0?0:1<<bit);auto it=b.roots.find(mask);if(it!=b.roots.end())result+=tr.count(it->second,limit);}
        return result;
    };
    for(int i=n-1;i>=0;--i){
        int u=t.order[i],big=0;
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u){(void)b;if(!big || bag[v]->vertices.size()>bag[big]->vertices.size())big=v;}
        if(big)bag[u]=std::move(bag[big]);else bag[u]=make_unique<MaskBag>();
        for(auto [v,b]:t.adj[u])if(t.parent[v]==u && v!=big){
            (void)b;for(int x:bag[v]->vertices)answer[u]+=query(*bag[u],u,x);
            for(int x:bag[v]->vertices)insert(*bag[u],x);bag[v].reset();
        }
        answer[u]+=query(*bag[u],u,u);insert(*bag[u],u);
    }
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
int main(int argc,char** argv){
    ios::sync_with_stdio(false);cin.tie(nullptr);assert(argc==2);int kind=atoi(argv[1]);
    if(kind==1)colors();if(kind==2)top_colors();if(kind==3)distances();if(kind==4)balancing();if(kind==5)passwords();
}
