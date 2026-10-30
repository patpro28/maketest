#include "tree.h"
using namespace std;
using ll=long long;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;vector<int>k(n+1),index(n+1);vector<ll>answer(n+1);
    for(int u=1;u<=n;++u)cin>>k[u];Tree tree(n);tree.read(true);
    vector<vector<int>>coords(1024),bit(1024);
    for(int u=1;u<=n;++u)coords[tree.mask[u]].push_back(tree.depth[u]);
    for(int m=0;m<1024;++m){
        auto& v=coords[m];sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());bit[m].resize(v.size()+1);
    }
    for(int u=1;u<=n;++u)index[u]=int(lower_bound(coords[tree.mask[u]].begin(),coords[tree.mask[u]].end(),tree.depth[u])-coords[tree.mask[u]].begin())+1;
    auto change=[&](int u,int delta){
        int m=tree.mask[u];for(int p=index[u];p<int(bit[m].size());p+=p&-p)bit[m][p]+=delta;
    };
    auto prefix=[&](int mask,int limit)->ll{
        int p=int(upper_bound(coords[mask].begin(),coords[mask].end(),limit)-coords[mask].begin());ll result=0;
        for(;p;p-=p&-p)result+=bit[mask][p];return result;
    };
    auto query=[&](int u,int x)->ll{
        int limit=2*tree.depth[u]+k[u]-tree.depth[x],m=tree.mask[x];ll result=prefix(m,limit);
        for(int b=0;b<10;++b)result+=prefix(m^(1<<b),limit);return result;
    };
    tree.sack([&](int u){
        tree.light(u,[&](int v){
            tree.vertices(v,[&](int x){answer[u]+=query(u,x);});
            tree.vertices(v,[&](int x){change(x,1);});
        });
        answer[u]+=query(u,u);change(u,1);
    },[&](int u){tree.vertices(u,[&](int x){change(x,-1);});});
    for(int u=1;u<=n;++u)cout<<answer[u]<<'\n';
}
