/*
Author: Kiragaya
Date: 2024/10/02 - 23:02
*/
#include <bits/stdc++.h>

using namespace std;

struct LCA
{
    struct Node
    {
        int depth, parent, jump;
    };

    vector<Node> info;
    vector<int> tin, tout;
    int timer;

    LCA(vector<vector<int>> &adj, int root = 0)
    {
        info.resize(adj.size());
        tin.resize(adj.size());
        tout.resize(adj.size());
        timer = 0;
        dfs(root, root, adj);
    }

    void dfs(int u, int p, vector<vector<int>> &adj)
    {
        tin[u] = timer++;
        int pp = info[p].jump;
        info[u] = {
            info[p].depth + 1,
            p,
            info[p].depth - info[pp].depth == info[pp].depth - info[info[pp].jump].depth ? info[pp].jump : p};
        for (int v : adj[u])
            if (v != p)
                dfs(v, u, adj);
        tout[u] = timer++;
    }

    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int getLCA(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        while (!is_ancestor(u, v))
            if (is_ancestor(info[u].jump, v))
                u = info[u].parent;
            else
                u = info[u].jump;
        return u;
    }

    int dist(int u, int v)
    {
        return info[u].depth + info[v].depth - 2 * info[getLCA(u, v)].depth;
    };
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LCA lca(adj);
    int q, last = 0;
    long long sum = 0;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        sum += lca.dist(last, x - 1);
        last = x - 1;
    }
    cout << sum << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}