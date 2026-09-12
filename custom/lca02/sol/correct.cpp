/*

O(n+k) using Tarjan's offline LCA. 

*/

#include "bits/stdc++.h"
using namespace std;
#define rep(i,a,b) for(int i=(a); i<(b); ++i)
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct DSU{
    vi par, len;
    int components;
    DSU(int n) : par(n,-1), len(n,1), components(n) {}
    int find(int at){
        return par[at]<0?at:(par[at]=find(par[at]));
    }
    bool unite(int a, int b){
        a = find(a), b = find(b);
        if (a==b) return 0;
        if (len[a]<len[b]) swap(a,b);
        len[a]+=len[b];
        par[b] = a;
        components--;
        return 1;
    }
    bool connected(int a, int b){
        return find(a)==find(b);
    }
};


int main(){
    cin.tie(NULL),cin.sync_with_stdio(false);
    
    int n,k; cin >> n >> k;
    vi vis(n+1), anc(n+1), pref(n+1), post(n+1), done(k);
    vvi adj(n+1);
    vector<vector<array<int,2>>> queries(n+1);
    rep(i,0,n-1){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    rep(i,0,k){
        int u,v; cin >> u >> v;
        pref[u]++, pref[v]++;
        queries[u].push_back({v,i});
        queries[v].push_back({u,i});
    }

    DSU dsu(n+1);

    auto dfs = [&](int at, auto&& dfs) -> void {
        vis[at] = 1;
        anc[at] = at;
        for(auto to : adj[at]) if (!vis[to]){
            dfs(to,dfs);
            dsu.unite(at,to);
            anc[dsu.find(at)] = at;
        }
        for(auto [to,i] : queries[at]) if (vis[to] and !done[i]){
            done[i] = 1;
            int lca = anc[dsu.find(to)];
            post[lca]--;
            pref[lca]--;
        }
    };

    dfs(1,dfs);

    int ans = 0;

    fill(all(vis),0);

    auto pull = [&](int at, auto && pull) -> int {
        vis[at] = 1;
        int sm = pref[at];
        for(auto to : adj[at]) if (!vis[to]) sm += pull(to, pull);
        ans = max(ans,sm);
        return sm + post[at];
    };
    
    pull(1,pull);

    cout << ans << '\n';
}