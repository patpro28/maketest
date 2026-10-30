#include "tree.h"
using namespace std;
using ll=long long;
struct Fenwick {
    int n;vector<ll>bit;
    explicit Fenwick(int n):n(n),bit(n+1){}
    void add(int p,ll x){for(;p<=n;p+=p&-p)bit[p]+=x;}
    ll prefix(int p)const{ll r=0;for(;p;p-=p&-p)r+=bit[p];return r;}
    int kth(ll k)const{
        int p=0,step=1;while(step<=n/2)step*=2;
        for(;step;step/=2)if(p+step<=n && bit[p+step]<k){k-=bit[p+step];p+=step;}
        return p+1;
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int>color(n+1),values;
    for(int i=1;i<=n;++i){cin>>color[i];values.push_back(color[i]);}
    sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());
    for(int i=1;i<=n;++i)color[i]=int(lower_bound(values.begin(),values.end(),color[i])-values.begin());
    Tree tree(n);tree.read();vector<vector<pair<int,int>>>queries(n+1);
    for(int i=0;i<q;++i){int u,k;cin>>u>>k;queries[u].push_back({k,i});}
    Fenwick frequency(n),mass(n);vector<int>count(values.size());vector<ll>answer(q);int total=0,distinct=0;
    auto change=[&](int u,int delta){
        int& f=count[color[u]];
        if(f){frequency.add(f,-1);mass.add(f,-f);--distinct;}
        f+=delta;total+=delta;
        if(f){frequency.add(f,1);mass.add(f,f);++distinct;}
    };
    tree.sack([&](int u){
        tree.light(u,[&](int v){tree.vertices(v,[&](int x){change(x,1);});});change(u,1);
        for(auto [k,id]:queries[u]){
            int remove=distinct-min(k,distinct);
            if(!remove){answer[id]=total;continue;}
            int f=frequency.kth(remove);
            ll smallest=mass.prefix(f-1)+(remove-frequency.prefix(f-1))*f;
            answer[id]=total-smallest;
        }
    },[&](int u){tree.vertices(u,[&](int x){change(x,-1);});});
    for(ll x:answer)cout<<x<<'\n';
}
