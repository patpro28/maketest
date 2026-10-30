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
    int n;cin>>n;vector<ll>a(n+1),w(n+1),values,answer(n+1);vector<int>index(n+1);
    for(int u=1;u<=n;++u){cin>>a[u]>>w[u];values.push_back(a[u]);}
    sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());
    for(int u=1;u<=n;++u)index[u]=int(lower_bound(values.begin(),values.end(),a[u])-values.begin())+1;
    Tree tree(n);tree.read();Fenwick weight(int(values.size())),moment(int(values.size()));ll total=0,sum=0;
    auto change=[&](int u,int delta){
        weight.add(index[u],delta*w[u]);moment.add(index[u],delta*w[u]*a[u]);
        total+=delta*w[u];sum+=delta*w[u]*a[u];
    };
    tree.sack([&](int u){
        tree.light(u,[&](int v){tree.vertices(v,[&](int x){change(x,1);});});change(u,1);
        int p=weight.kth((total+1)/2);ll median=values[p-1],left_w=weight.prefix(p),left_s=moment.prefix(p);
        answer[u]=median*left_w-left_s+(sum-left_s)-median*(total-left_w);
    },[&](int u){tree.vertices(u,[&](int x){change(x,-1);});});
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
