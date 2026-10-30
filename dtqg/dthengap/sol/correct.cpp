#include "tree.h"
using namespace std;
using ll=long long;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;vector<int>k(n+1),count(n);vector<ll>answer(n+1);
    for(int u=1;u<=n;++u)cin>>k[u];Tree tree(n);tree.read();
    auto get=[&](int d)->ll{return d<0 || d>=n?0:count[d];};
    auto insert=[&](int u){++count[tree.depth[u]];};
    tree.sack([&](int u){
        tree.light(u,[&](int v){
            tree.vertices(v,[&](int x){answer[u]+=get(2*tree.depth[u]+k[u]-tree.depth[x]);});
            tree.vertices(v,insert);
        });
        answer[u]+=get(tree.depth[u]+k[u]);insert(u);
    },[&](int u){tree.vertices(u,[&](int x){--count[tree.depth[x]];});});
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
